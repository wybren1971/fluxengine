#include "globals.h"
#include "fluxmap.h"
#include "decoders/fluxmapreader.h"
#include "flags.h"
#include "protocol.h"
#include "proto.h"
#include "fmt/format.h"
#include <numeric>
#include <math.h>
#include <strings.h>

FluxmapReader::FluxmapReader(const Fluxmap& fluxmap):
        _fluxmap(fluxmap),
        _bytes(fluxmap.ptr()),
        _size(fluxmap.bytes()),
		_config(config.decoder())
{
	rewind();
}

uint8_t FluxmapReader::getNextEvent(unsigned& ticks)
{
    ticks = 0;

    while (!eof())
    {
        uint8_t b = _bytes[_pos.bytes++];
		ticks += b & 0x3f;
		if (b & (F_BIT_PULSE|F_BIT_INDEX))
        {
            _pos.ticks += ticks;
            return b;
        }
    }

    _pos.ticks += ticks;
    return 0;
}

unsigned FluxmapReader::findEvent(uint8_t target)
{
    unsigned ticks = 0;

    for (;;)
    {
        unsigned thisTicks;
        uint8_t bits = getNextEvent(thisTicks);
        ticks += thisTicks;
        if (eof())
            return 0;
        if (bits & target)
            return ticks;
    }
}

unsigned FluxmapReader::readInterval(nanoseconds_t clock)
{
    unsigned thresholdTicks = (clock * _config.pulse_debounce_threshold()) / NS_PER_TICK;
    unsigned ticks = 0;

    while (ticks < thresholdTicks)
    {
        unsigned thisTicks = findEvent(F_BIT_PULSE);
        if (!thisTicks)
            break;
        ticks += thisTicks;
    }
    return ticks;
}

static int findLowestSetBit(uint64_t value)
{
    if (!value)
        return 0;
    int bit = 1;
    while (!(value & 1))
    {
        value >>= 1;
        bit++;
    }
    return bit;
}

FluxPattern::FluxPattern(unsigned bits, uint64_t pattern):
    _bits(bits)
{
    const uint64_t TOPBIT = 1ULL << 63;

    assert(pattern != 0);

    unsigned lowbit = findLowestSetBit(pattern)-1;

    pattern <<= 64 - bits;
    _highzeroes = 0;
    while (!(pattern & TOPBIT))
    {
        pattern <<= 1;
        _highzeroes++;
    }

    _length = 0;
    while (pattern != TOPBIT)
    {
        unsigned interval = 0;
        do
        {
            pattern <<= 1;
            interval++;
        }
        while (!(pattern & TOPBIT));
        _intervals.push_back(interval);
        _length += interval;
    }

    if (lowbit)
    {
        _lowzero = true;
        /* Note that length does *not* include this interval. */
        _intervals.push_back(lowbit + 1);
    }
}

bool FluxPattern::matches(const unsigned* end, FluxMatch& match) const
{
	const double clockDecodeThreshold = config.decoder().bit_error_threshold();
    const unsigned* start = end - _intervals.size();
    unsigned candidatelength = std::accumulate(start, end - _lowzero, 0);
    if (!candidatelength)
        return false;
    match.clock = (double)candidatelength / (double)_length;

    unsigned exactIntervals = _intervals.size() - _lowzero;
    for (unsigned i=0; i<exactIntervals; i++)
    {
        double ii = match.clock * (double)_intervals[i];
        double ci = (double)start[i];
        double error = fabs((ii - ci) / match.clock);
        if (error > clockDecodeThreshold)
            return false;
    }

    if (_lowzero)
    {
        double ii = match.clock * (double)_intervals[exactIntervals];
        double ci = (double)start[exactIntervals];
        double error = (ii - ci) / match.clock;
        if (error > clockDecodeThreshold)
            return false;
    }

    match.matcher = this;
    match.intervals = _intervals.size();
    match.zeroes = _highzeroes;
    return true;
}

FluxMatchers::FluxMatchers(const std::initializer_list<const FluxMatcher*> matchers):
    _matchers(matchers)
{
    _intervals = 0;
    for (const auto* matcher : matchers)
        _intervals = std::max(_intervals, matcher->intervals());
}

bool FluxMatchers::matches(const unsigned* intervals, FluxMatch& match) const
{
    for (const auto* matcher : _matchers)
    {
        if (matcher->matches(intervals, match))
            return true;
    }
    return false;
}

void FluxmapReader::seek(nanoseconds_t ns)
{
    unsigned ticks = ns / NS_PER_TICK;
    if (ticks < _pos.ticks)
    {
        _pos.ticks = 0;
        _pos.bytes = 0;
    }

    while (!eof() && (_pos.ticks < ticks))
    {
        unsigned t;
        getNextEvent(t);
    }
    _pos.zeroes = 0;
}

nanoseconds_t FluxmapReader::seekToPattern(const FluxMatcher& pattern)
{
    const FluxMatcher* unused;
    return seekToPattern(pattern, unused);
}

nanoseconds_t FluxmapReader::seekToPattern(const FluxMatcher& pattern, const FluxMatcher*& matching)
{
    unsigned intervalCount = pattern.intervals();
    unsigned candidates[intervalCount+1];
    Fluxmap::Position positions[intervalCount+1];

    for (unsigned i=0; i<=intervalCount; i++)
    {
        positions[i] = tell();
        candidates[i] = 0;
    }

    while (!eof())
    {
        FluxMatch match;
        if (pattern.matches(&candidates[intervalCount+1], match))
        {
            seek(positions[intervalCount-match.intervals]);
            _pos.zeroes = match.zeroes;
            matching = match.matcher;
            nanoseconds_t detectedClock = match.clock * NS_PER_TICK;
            if (detectedClock > (_config.minimum_clock_us()*1000))
                return match.clock * NS_PER_TICK;
        }

        for (unsigned i=0; i<intervalCount; i++)
        {
            positions[i] = positions[i+1];
            candidates[i] = candidates[i+1];
        }
        candidates[intervalCount] = findEvent(F_BIT_PULSE);
        positions[intervalCount] = tell();

    }

    matching = NULL;
    return 0;
}

void FluxmapReader::seekToIndexMark()
{
    findEvent(F_BIT_INDEX);
    _pos.zeroes = 0;
}

bool FluxmapReader::readRawBit(nanoseconds_t clockPeriod)
{
    assert(clockPeriod != 0);

    if (_pos.zeroes)
    {
        _pos.zeroes--;
        return false;
    }

    nanoseconds_t interval = readInterval(clockPeriod)*NS_PER_TICK;
    double clocks = (double)interval / clockPeriod + _config.clock_interval_bias();

    if (clocks < 1.0)
        clocks = 1.0;
    _pos.zeroes = (int)round(clocks) - 1;
    return true;
}

std::vector<bool> FluxmapReader::readRawBits(unsigned count, nanoseconds_t clockPeriod)
{
    std::vector<bool> result;
    while (!eof() && count--)
    {
        bool b = readRawBit(clockPeriod);
        result.push_back(b);
    }
    return result;
}

std::vector<bool> FluxmapReader::readRawBits(const Fluxmap::Position& until, nanoseconds_t clockPeriod)
{
    std::vector<bool> result;
    while (!eof() && (_pos.bytes < until.bytes))
        result.push_back(readRawBit(clockPeriod));
    return result;
}

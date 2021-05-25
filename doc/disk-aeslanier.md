Disk: AES Lanier word processor
===============================

Back in 1980 Lanier released a series of very early integrated word processor
appliances, the No Problem. These were actually [rebranded AES Data Superplus
machines](http://vintagecomputers.site90.net/aes/). They were gigantic,
weighed 40kg, and one example I've found cost £13,000 in 1981 (the equivalent
of nearly £50,000 in 2018!).

8080 machines with 32kB of RAM, they ran their own proprietary word
processing software off twin 5.25" drive units, but apparently other software
was available.

The disk format is exceptionally weird. They used 77 track, 32 sector, single
sided _hard_ sectored disks, where there were multiple index holes,
indicating to the hardware where the sectors start. The encoding scheme
itself is [MMFM (aka
M2FM)](http://www.retrotechnology.com/herbs_stuff/m2fm.html), an early
attempt at double-density disk encoding which rapidly got obsoleted by the
simpler MFM --- and the bytes are stored on disk _backwards_. Even aside from
the encoding, the format on disk was strange; unified sector header/data
records, so that the sector header (containing the sector and track number)
is actually inside the user data.

FluxEngine can read these, but I only have a single, fairly poor example of a
disk image, and I've had to make a lot of guesses as to the sector format
based on what looks right. If anyone knows _anything_ about these disks,
[please get in touch](https://github.com/davidgiven/fluxengine/issues/new).

Reading discs
-------------

Just do:

```
fluxengine read aeslanier
```

You'll end up with an `aeslanier.img` file.

Useful references
-----------------

  * [SA800 Diskette Storage Drive - Theory Of Operations](http://www.hartetechnologies.com/manuals/Shugart/50664-1_SA800_TheorOp_May78.pdf): talks about MMFM a lot, but the Lanier machines didn't use this disk format.

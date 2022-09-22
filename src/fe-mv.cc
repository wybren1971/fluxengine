#include "globals.h"
#include "flags.h"
#include "proto.h"
#include "fmt/format.h"
#include "fluxengine.h"
#include "lib/vfs/vfs.h"
#include "lib/utils.h"
#include "src/fileutils.h"
#include <google/protobuf/text_format.h>
#include <fstream>

static FlagGroup flags({&fileFlags});

static StringFlag oldFilename({"--path1"}, "old filename", "");
static StringFlag newFilename({"--path2"}, "new filename", "");

int mainMv(int argc, const char* argv[])
{
    if (argc == 1)
        showProfiles("mv", formats);
    flags.parseFlagsWithConfigFiles(argc, argv, formats);

    try
    {
        auto filesystem = Filesystem::createFilesystemFromConfig();

        Path oldPath(oldFilename);
        if (oldPath.size() == 0)
            Error() << "old filename missing";

        Path newPath(newFilename);
        if (newPath.size() == 0)
            Error() << "new filename missing";

        filesystem->moveFile(oldPath, newPath);
        filesystem->flushChanges();
    }
    catch (const FilesystemException& e)
    {
        Error() << e.message;
    }

    return 0;
}

FATFS_SRCS = \
	dep/fatfs/source/ff.c \
	dep/fatfs/source/ffsystem.c \
	dep/fatfs/source/ffunicode.c \
	
FATFS_OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(FATFS_SRCS))
$(FATFS_OBJS): CFLAGS += -Idep/fatfs/source
FATFS_LIB = $(OBJDIR)/libfatfs.a
$(FATFS_LIB): $(FATFS_OBJS)
FATFS_CFLAGS = -Idep/fatfs/source
FATFS_LDFLAGS = $(FATFS_LIB)
OBJS += $(FATFS_OBJS)


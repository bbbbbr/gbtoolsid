
DEL = rm -f

BIN = gbtoolsid
BIN_WIN = $(BIN).exe
TESTOPT =

SRCDIR      = src
OBJDIR      = obj
BINS        = $(OBJDIR)/$(PROJECTNAME).gb
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c)))
OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o)



all: linux

cleanobj:
	$(DEL) $(OBJS)

clean:
	$(DEL) $(OBJS) $(BIN_WIN) $(BIN)


# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:  $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@


# Linux build
linux: CC = gcc
linux: LDFLAGS = -s
linux: $(OBJS)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

# Linux MinGW build for Windows
# (static linking to avoid DLL dependencies)
wincross: TARGET=i686-w64-mingw32
wincross: CC = $(TARGET)-g++
wincross: LDFLAGS = -s -static
wincross: $(OBJS)
	$(CC) -o $(BIN_WIN) $^ $(LDFLAGS)

linuxzip: linux
	mkdir -p bin
	zip $(BIN)_linux.zip $(BIN)
	mv $(BIN)_linux.zip bin

wincrosszip: wincross
	mkdir -p bin
	zip $(BIN)_windows.zip $(BIN_WIN)
	mv $(BIN)_windows.zip bin


package:
	${MAKE} clean
	${MAKE} wincrosszip
	${MAKE} clean
	${MAKE} linuxzip

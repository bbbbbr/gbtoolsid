
DEL = rm -f

BIN = gbtoolsid
BIN_WIN = $(BIN).exe
TESTOPT =

SRCDIR      = src
OBJDIR      = obj
MKDIRS = $(OBJDIR) $(BINDIR) $(PACKDIR)
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

# MacOS uses linux target
macos: linux

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

macoszip: macos
	mkdir -p bin
	# -j discards (junks) path to file
	zip -j $(BIN)_macos.zip $(BIN) Changelog.md README.md
	mv $(BIN)_macos.zip bin


linuxzip: linux
	mkdir -p bin
	# -j discards (junks) path to file
	zip -j $(BIN)_linux.zip $(BIN) Changelog.md README.md
	mv $(BIN)_linux.zip bin

wincrosszip: wincross
	mkdir -p bin
	# -j discards (junks) path to file
	zip -j $(BIN)_windows.zip $(BIN_WIN) Changelog.md README.md
	mv $(BIN)_windows.zip bin


package:
	${MAKE} clean
	${MAKE} wincrosszip
	${MAKE} clean
	${MAKE} linuxzip

.PHONY: test

test:
	mkdir -p test/output
	find test/* -iname "*.gb*" -type f | xargs -I {} $(BIN) -pF -oC "{}" > test/output/test_run.csv
	diff --brief test/test_ref.csv test/output/test_run.csv

updatetest:
	mkdir -p test/output
	find test/* -iname "*.gb*" -type f | xargs -I {} $(BIN) -pF -oC "{}" > test/test_ref.csv

runtest-norepo:
	mkdir -p test_norepo/output
	find test_norepo/* -iname "*.gb*" -type f | xargs -I {} $(BIN) -pF -oC "{}" > test_norepo/output/test_run.csv
	diff --brief test_norepo/test_ref.csv test_norepo/output/test_run.csv

updatetest-norepo:
	mkdir -p test_norepo/output
	find test_norepo/* -iname "*.gb*" -type f | xargs -I {} $(BIN) -pF -oC "{}" > test_norepo/test_ref.csv


# create necessary directories after Makefile is parsed but before build
# info prevents the command from being pasted into the makefile
$(info $(shell mkdir -p $(MKDIRS)))


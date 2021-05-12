
DEL = rm -f

# Add all c source files
CFILES = $(wildcard *.c)
# Remove some files that won't/can't be used
COBJ = $(CFILES:.c=.o)
BIN = gbtoolsid
BIN_WIN = $(BIN).exe
TESTOPT =


all: linux

cleanobj:
	$(DEL) $(COBJ)

clean:
	$(DEL) $(COBJ) $(BIN_WIN) $(BIN)

test:
	./$(BIN) $(TESTOPT) ~/git/gbdev/plutos_corner/pluto/bin/PLUTOS_CORNER.gb
	./$(BIN) $(TESTOPT) ~/git/gbdev/petris/petris_jsemu/rom/game.gb.longpet_improved
	./$(BIN) $(TESTOPT) ~/git/gbdev/petris/petris_jsemu/rom/Petris_gbdk-2020-someversion.gbc
	./$(BIN) $(TESTOPT) ~/git/gbdev/gbdk2020/gbdk-2020-git/build/gbdk/examples/gb/ram_function/ram_fn.gb
	./$(BIN) $(TESTOPT) ~/"Desktop/incoming/Gameboy Homebrew ROMs/Dragonborne-demo.gb"
	./$(BIN) $(TESTOPT) ~/"Desktop/incoming/Gameboy Homebrew ROMs/Deadeus - rom/deadeus.gb"
	./$(BIN) $(TESTOPT) ~/"Desktop/incoming/Gameboy Homebrew ROMs/2bityou.itch.io-aliens-game.gb"
	./$(BIN) $(TESTOPT) ~/"Desktop/incoming/Gameboy Homebrew ROMs/discord-mel-lumpytouch.itch.io-super-impostor-bros.gb"
	./$(BIN) $(TESTOPT) ~/"Desktop/incoming/Gameboy Homebrew ROMs/discord-tortussa-darionquest.gb"


# Linux build
linux: CC = gcc
linux: LDFLAGS = -s
linux: $(COBJ)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

linuxzip: linux
	mkdir -p bin
	zip $(BIN)_linux.zip $(BIN)
	mv $(BIN)_linux.zip bin


# Linux MinGW build for Windows
# (static linking to avoid DLL dependencies)
wincross: TARGET=i686-w64-mingw32
wincross: CC = $(TARGET)-g++
wincross: LDFLAGS = -s -static
wincross: $(COBJ)
	$(CC) -o $(BIN_WIN) $^ $(LDFLAGS)

wincrosszip: wincross
	mkdir -p bin
	zip $(BIN)_windows.zip $(BIN).exe 
	mv $(BIN)_windows.zip bin


package:
	${MAKE} clean
	${MAKE} wincrosszip
	${MAKE} clean
	${MAKE} linuxzip

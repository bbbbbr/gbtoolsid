DEL = rm -f

# Add all c source files
CFILES = $(wildcard *.c)
# Remove some files that won't/can't be used
COBJ = $(CFILES:.c=.o)
BIN = gbtoolsid

# Linux build
CC = gcc
LDFLAGS = -s


all: $(COBJ)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

cleanobj:
	$(DEL) $(COBJ)

clean:
	$(DEL) $(COBJ) $(BIN).exe $(BIN)

test:
	./$(BIN) ~/git/gbdev/plutos_corner/pluto/bin/PLUTOS_CORNER.gb 
	./$(BIN) ~/git/gbdev/petris/petris_jsemu/rom/game.gb.longpet_improved 
	./$(BIN) ~/git/gbdev/petris/petris_jsemu/rom/Petris_gbdk-2020-someversion.gbc
	./$(BIN) ~/git/gbdev/gbdk2020/gbdk-2020-git/build/gbdk/examples/gb/ram_function/ram_fn.gb
	./$(BIN) ~/"Desktop/incoming/Gameboy Homebrew ROMs/Dragonborne-demo.gb"
	./$(BIN) ~/"Desktop/incoming/Gameboy Homebrew ROMs/Deadeus - rom/deadeus.gb"
	./$(BIN) ~/"Desktop/incoming/Gameboy Homebrew ROMs/2bityou.itch.io-aliens-game.gb"
	./$(BIN) ~/"Desktop/incoming/Gameboy Homebrew ROMs/discord-mel-lumpytouch.itch.io-super-impostor-bros.gb"
	./$(BIN) ~/"Desktop/incoming/Gameboy Homebrew ROMs/discord-tortussa-darionquest.gb"



# Linux MinGW build for Windows
# (static linking to avoid DLL dependencies)
wincross: TARGET=i686-w64-mingw32
wincross: CC = $(TARGET)-g++
wincross: LDFLAGS = -s -static
wincross: $(COBJ)
	$(CC) -o $(BIN).exe $^ $(LDFLAGS)

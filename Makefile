CC=
CFLAGS=-O3 -pipe
LIBS=
OUT=kaizo-game
STRIP=

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Windows)
	CFLAGS += -D WIN32
	CC+=gcc
	LIBS += -lgdi32 -lwinmm
endif
ifeq ($(detected_OS),Darwin)
	CFLAGS += -D OSX
	CC+=clang
	LIBS += -framework Cocoa -framework AudioToolbox
endif
ifeq ($(detected_OS),Linux)
	CFLAGS += -D LINUX
	CC+=gcc
	LIBS += -lX11 -lasound
	STRIP += strip $(OUT)
endif

COMP=$(CC) $(CFLAGS) -c 

all: main.o
	$(CC) *.o $(LIBS) -o $(OUT)
	$(STRIP)

main.o: src/main.c
	$(COMP) src/main.c


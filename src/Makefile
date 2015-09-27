VERSION  = $(shell git describe --always --dirty)

SDL_CFLAGS := $(shell sdl2-config --cflags)

SDL_LDFLAGS := $(shell sdl2-config --libs)

CXXFLAGS =	-O1 -g -Wall -Wextra -Wcast-align -pedantic -fmessage-length=0 -std=c++11 -DGIT_REV=\"$(VERSION)\" $(SDL_CFLAGS)

OBJS =		miNES.o mem/mem.o cpu/cpu.o ppu/ppu.o

LIBS = $(SDL_LDFLAGS)

TARGET =	miNES

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

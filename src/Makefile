VERSION  = $(shell git describe --always --dirty)

CXXFLAGS =	-O1 -g -Wall -Wextra -Wcast-align -pedantic -fmessage-length=0 -std=c++11 -DGIT_REV=\"$(VERSION)\"

OBJS =		miNES.o mem/mem.o cpu/cpu.o

LIBS =

TARGET =	miNES

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

CXXFLAGS =	-O0 -g -Wall -Wextra -Wcast-align -pedantic -fmessage-length=0 -std=c++0x


OBJS =		miNES.o mem/mem.o cpu/cpu.o

LIBS =

TARGET =	miNES

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

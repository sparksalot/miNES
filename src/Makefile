CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		miNES.o mem/mem.o cpu/cpu.o

LIBS =

TARGET =	miNES

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

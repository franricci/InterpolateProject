CXXFLAGS =	 -O0 -g -Wall -std=c++11 -lblas -llapacke -llapack -fmessage-length=0

OBJS =		Interpolate.o CsvReader.o CellDiv.o InterpolateMLS.o

LIBS =

TARGET =	Interpolate

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -lblas -llapacke -llapack -lm

all:	$(TARGET)
	rm -rf *.o

clean:
	rm -f $(OBJS) $(TARGET)

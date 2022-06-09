CC=g++
CCFLAGS=-std=c++2a
SOURCES=Frame.cpp extractor.cpp
OBJECTS=Frame.o extractor.o 


extractor: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o extractor 

.cpp .o:
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o



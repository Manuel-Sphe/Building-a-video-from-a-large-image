CC=g++
CCFLAGS=-std=c++2a
SOURCES=FrameSequence.cpp extractor.cpp
OBJECTS=FrameSequence.o extractor.o 


extractor: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o extractor 

.cpp .o:
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o

run: 
	./extractor sloan_image.pgm



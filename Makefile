CC=g++			# g++ compiler
CFLAGS=-std=c++2a -lm	# using c++20 and math library

 
extractor: extractor.cpp FrameSequence.cpp header.h
	$(CC) -o extractor extractor.cpp FrameSequence.cpp $(CFLAGS)


FrameSequence.o: FrameSequence.cpp header.h
	$(CC) -c FrameSequence.cpp

# compile extractor.cpp
extractor.o: extractor.cpp
	$(CC) -c extractor.cpp

# delete all the object code files and output files
clean:
	@rm -f *.o
	@rm -f extractor
	@rm -rf ./output
	@rm -rf GENERATED_VIDEOS 

# Remove all output data files
clean-data:
	@rm -rf ./output

run1:
	make clean-data
	mkdir -p output
	./extractor sloan_image.pgm -t 0 10 200 200 -s 640 480 -w reverse revseq

run2:
	make clean-data
	mkdir -p output
	./extractor sloan_image.pgm -t 0 10 1000 1000 -s 640 480 -w invert invseq

run3:
	make clean-data
	mkdir -p output
	./extractor sloan_image.pgm -t 0 10 50 50 -s 640 640 -w none noneseq -w reverse revseq

run4:
	make clean-data
	mkdir -p output
	./extractor sloan_image.pgm -t 5 10 1000 1000 -s 640 640 -w reinvert revinveq

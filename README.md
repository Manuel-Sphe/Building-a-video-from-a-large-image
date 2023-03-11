# Building-a-video-from-a-large-image
Building a ‘video’ from a large image
# Files

## FrameSequence.h

Defines a FrameSequence class which contains all processed frames. The class provides 
functions for processing/extracting frames and outputting frames based on selected operation command. 

## FrameSequence.cpp

Implements the attributes defined by the [header](https://github.com/Manuel-Sphe/Building-a-video-from-a-large-image/blob/sphe/header.h) file

## extractor.cpp

The driver to run file to run the application

### Build

```unix
$ make
```
### clean
Removes object files, executables and output files
```
$ make clean
```
### clean-data
Removes all ouput files
```unix
$ make clean-data
```
### run
```unix
$ ./extractor -t <int> <int> <int> <int> -s <int> <int> -w <string> <string>

-t <int> <int> <int> <int> # x1 y1 x2 y2 (begin & end origin pixel coords,for frame trajectory)
-s <int> <int> # <width> <height> (size of small frame in
pixels)
-w <string> <string> # write frames with <operation> <name>
```

or simply
```unix
$ make run<int>

<int> 1 - 4 => preset input parameters which can be found on the make file 
e.g $ make
then $make run1
```

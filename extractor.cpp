#include <iostream>
#include "header.h"

int main(int argc, char* argv[]){
    std::cout<<"Happy Coding" <<std::endl;

    FrameSequence img;

    img.readImage(argv[1]);

    img.ExtractImage(2,3,7,9,100,100);

    

    return 0;
}


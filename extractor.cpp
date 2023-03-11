/**
 * @file extractor.cpp
 * @author Sphesihle Madonsela
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstdlib>
#include "header.h"

/**
 * @brief This is the driver file 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[]){

    // checking for bounds
    if ( argc < 13 || (argc-13) % 3 != 0  ){
        std::cout << "Invalid input params" << std::endl;
        return 0;
    }
    
    // Frame Sequence Object instantiation -calling the non arguement constructor
    FrameSequence sequence;

    // get the filename 
    sequence.readImage(argv[1]);

    int x1 = std::stoi(argv[3]);
    int y1 = std::stoi(argv[4]);
    int x2 = std::stoi(argv[5]);
    int y2 = std::stoi(argv[6]);

    int width = std::stoi(argv[8]);
    int height = std::stoi(argv[9]);

    sequence.ExtractImage(x1, y1, x2, y2, width, height);

    int len_ops = argc - 10;
    int op_count = int(len_ops / 3);

    for (int i = 0; i < op_count; i++){
        std::string op = argv[11 + i*3];
        std::string name_base = argv[12 + i*3];

        sequence.writeFrames(op, name_base);
    }

    return 0;
}
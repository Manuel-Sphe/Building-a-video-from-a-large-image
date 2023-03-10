#include "header.h"
#include <iostream>
#include <sstream>
#include <math.h>


FrameSequence frameSeq;
FrameSequence::FrameSequence(){
    FrameSequence::row = 0;
    FrameSequence::col = 0; 
}

void FrameSequence::readImage(const std::string & file){
    std::cout<<"Read method"<<std::endl;

    std::stringstream ss;
    unsigned char * binary_data; // this is a 1D array

    int size , rows , cols ,intensity,chars; // size, rows and cols

    std::ifstream input_File;
    input_File.open(file, std::ios::in | std::ios::binary); // for reading the file only 

    if(!input_File){
        std::cerr<<file<<" Not Found!!"<<std::endl;
        return;
    }

   else{

    std::string line ;
        std::getline(input_File,line); // get the P5



        while(std::getline(input_File,line)){
            if (line.front() != '#')
                break; 
        }


        ss<<line.substr(0,line.find(' '));

        ss>>rows;
        std::cout<<rows<<std::endl;
     
        ss.clear();
        ss<<line.substr(line.find(' '));
        ss>>cols;

  

        std::cout<<cols<<std::endl;
        ss.clear();

    
        std::getline(input_File,line);// get the 255 
        input_File>>std::ws;
        ss<<line;
        ss>>intensity;
        ss.clear();
    
        std::cout<<intensity<<std::endl;
        size = rows*cols ;
        std::cout<<size<<std::endl;;

        FrameSequence::row=rows;
        FrameSequence::col =cols;


        // read takes a char not char * 
        binary_data = new unsigned char[size];
        input_File.read(reinterpret_cast<char *> (binary_data), size);

        FrameSequence::Picture = new unsigned char*[rows];

       for(int i = 0;i<rows;++i){
            FrameSequence::Picture[i] = new unsigned char[cols];
            for(int j = 0 ;j<cols;++j){
                FrameSequence::Picture[i][j] = binary_data[i*cols + j];
            }
        }
        if (binary_data != nullptr)
            delete [] binary_data;
       
    }
    input_File.close();


    

}
void FrameSequence::ExtractImage(int x1,int y1 ,int x2,int y2, int w, int h){
    FrameSequence::height = h;
    FrameSequence::width = w;
    float m = (y2 - y1)/static_cast<float>(x2 - x1);

    
    std::ofstream file;

}

FrameSequence::~FrameSequence(){
    std::cout<<"Destructor"<<std::endl;

    int size = FrameSequence::imageSequence.size();

    std::cout<<"The size is "<<size<<std::endl;

    for(int i = 0 ;i<size;++i){
        for(int k = 0;k<frameSeq.height;k++){
            delete [] FrameSequence::imageSequence[i][k];
        }
        delete [] FrameSequence::imageSequence[i];

    }
    FrameSequence::imageSequence.clear();
    std::cout<<"Frames destroyed "<<std::endl;  
}


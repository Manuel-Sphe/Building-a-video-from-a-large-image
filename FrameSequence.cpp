#include "header.h"


FrameSequence frameSeq;
FrameSequence::FrameSequence(){
    FrameSequence::row = 0;
    FrameSequence::col = 0; 
}

void FrameSequence::readImage(const std::string & file){
    std::cout<<"Read method"<<std::endl;

    std::stringstream ss;
    char * binary_data; // this is a 1D array

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
        std::cout<<"row : "<<rows<<std::endl;
     
        ss.clear();
        ss<<line.substr(line.find(' '));
        ss>>cols;

  

        std::cout<<"col : "<<cols<<std::endl;
        ss.clear();

    
        std::getline(input_File,line);// get the 255 
        input_File>>std::ws;
        ss<<line;
        ss>>intensity;
        ss.clear();
    
        std::cout<<intensity<<std::endl;
        size = rows*cols ;
        std::cout<<"size : "<<size<<std::endl;;

        FrameSequence::row=rows;
        FrameSequence::col =cols;


        // read takes a char not char * 
        binary_data = new char[size]; 
        
        input_File.read(binary_data, size);

        unsigned char *  image = reinterpret_cast<unsigned char *>(binary_data);

        // The 2D array [][] Frame
        FrameSequence::actualFrame = new unsigned char*[rows];
        // Will have to deallocate this memory after loading into the imageSequence

        for(int i = 0;i<rows;++i){
            FrameSequence::actualFrame[i] = new unsigned char[cols];
            for(int j = 0 ;j<cols;++j){
                FrameSequence::actualFrame[i][j] = image[i*cols + j]; // 1D to 2D 
            }
        }
        
        
        if (binary_data != nullptr)
            delete [] binary_data;
       
    }

    input_File.close();
}

void FrameSequence::ExtractImage(int  x1,int  y1 ,int x2,int y2, int  w, int  h){
    FrameSequence::height = h;
    FrameSequence::width = w;

    for (int i = y1; i <= y2 - height + 1; ++i) {
    for (int j = x1; j <= x2 - width + 1; ++j) {
        unsigned char ** frame = new unsigned char*[height];
        for (int k = 0; k < height; ++k) {
            frame[k] = new unsigned char[width];
            for (int l = 0; l < width; ++l) {
                frame[k][l] = FrameSequence::actualFrame[i + k][j + l];
            }
        }
        // Add frame to the vector of frames
        FrameSequence::imageSequence.push_back(frame);
    }

    // Deallocate the actual frame's memory , after storing it in imagesequence vector

    for(int i = 0 ;i<FrameSequence::row; ++i){
        delete [] FrameSequence::actualFrame[i];
    }
    delete FrameSequence::actualFrame;

    
    }


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

/**
 * @brief outputs a .pgm files
 * 
 * @param op 
 * @param name 
 */


void FrameSequence::writeFrames(std::string op, std::string name){

    int size = FrameSequence::imageSequence.size();

    for (int i = 0; i < size; ++i){
        char buff [100];
        const char * c_name_base = name.c_str();
        snprintf(buff,sizeof(buff), "%s%s%04d.pgm", "./output/",c_name_base, i);

        std::string name = buff;

        std::ofstream ofs(name, std::ios::out | std::ios::binary);

        ofs << "P5" << std::endl;
        ofs << FrameSequence::width << " " <<FrameSequence::height << std::endl;
        ofs << 255 << std::endl;
        ofs << std::endl;

        switch(op[0]) {
            case 'r':
                if (op == "reverse"){
                    for (int j = 0; j < FrameSequence::height; ++j ){
                        ofs.write( reinterpret_cast<char *>(FrameSequence::imageSequence[size - i - 1][j]), FrameSequence::width);
                    }
                } else if (op == "reinvert") {
                    for (int j = 0; j < FrameSequence::height; ++j ){
                        for (int k = 0; k < FrameSequence::width; ++k){
                            ofs << (unsigned char)( 255 - static_cast<int>(FrameSequence::imageSequence[size - i - 1][j][k] )) ;
                        }
                    }
                }
                break;
            case 'i':
                if (op == "invert"){
                    for (int j = 0; j < FrameSequence::height; ++j ){
                        for (int k = 0; k < FrameSequence::width; ++k){
                            ofs << (unsigned char)( 255 - static_cast<int>(FrameSequence::imageSequence[i][j][k]) ) ;
                        }
                    }
                }
                break;
            default:
                for (int j = 0; j < FrameSequence::height; ++j ){
                    ofs.write( reinterpret_cast<char *>(FrameSequence::imageSequence[i][j]),FrameSequence::width);
                }
        }
    }
}
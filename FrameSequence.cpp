#include "header.h"

FrameSequence::FrameSequence(){
    FrameSequence::row = 0;
    FrameSequence::col = 0; 
    FrameSequence::width = 0;
    FrameSequence::height = 0;
    FrameSequence::imageSequence.clear();
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
        size = rows * cols ;
        std::cout<<"size : "<<rows<<" by "<<cols<<std::endl;;

        FrameSequence::row = rows;
        FrameSequence::col = cols;

        // read takes a char not char * 
        binary_data = new char[size]; 
        
        input_File.read(binary_data, size);

        unsigned char *  image = reinterpret_cast<unsigned char *>(binary_data);

        // The 2D array [][] Frame
        FrameSequence::actualFrame = new unsigned char*[rows];
        // Will have to deallocate this memory after loading into the imageSequence

        for(int i = 0; i < rows; ++i) {
            FrameSequence::actualFrame[i] = new unsigned char[cols];
            for(int j = 0 ; j <cols; ++j) {
                FrameSequence::actualFrame[i][j] = image[i*cols + j]; // 1D to 2D 
            }
        }
        
       delete [] image;
    }

    input_File.close();
}

void FrameSequence::ExtractImage(const int & x1,const int &  y1 ,const int & x2,
                                 const int & y2, const int &  w, const int &  h){
   // Set the height and width of the image frames.
    FrameSequence::height = h;
    FrameSequence::width = w;

    // Define a lambda function to calculate the absolute value of a float.
    auto absValue = [](const float  & x) -> float {
        return x > 0 ? x : -x;
    };
    // Define a lambda function to calculate the max value
    auto max = [](const int & x,const int &  y )->int {
        return x>y ? x : y;
    };

    // Calculate the slope of the line between the two given points.
    float slope = static_cast<float>(y2 - y1) / (x2 - x1);
    // Calculate the number of frames required to cover the entire line.
    int numFrames = max(absValue(x2 - x1), absValue(y2 - y1));

    // If the slope of the line is less than 1, loop over all x-values from x1+1
    if (absValue(slope) < 1.0) {
        float y = y1;
        for (int i = 0; i < numFrames; ++i) {
            // Increment the y-value based on the slope of the line.
            y += slope;
            // Round the y-value and convert to an integer.
            int y_val = static_cast<int>(std::round(y));
            // Allocate memory for the frame.
            unsigned char ** frame = new unsigned char*[height];
            for (int j = 0; j < height; ++j) {
                frame[j] = new unsigned char[width];
                // Extract the pixel values for each row of the frame from the actualFrame array.
                for (int k = 0; k < width; ++k) {
                    frame[j][k] = FrameSequence::actualFrame[y_val + j][x1 + i + k];
                }
            }
            // Add the frame to the imageSequence vector.
            FrameSequence::imageSequence.push_back(frame);

            for (int j = 0; j < height ; ++j ) {
                delete frame[j];
            }
            delete [] frame;
        }
    }
    // If the slope of the line is greater than or equal to 1, loop over all y-values from y1+1
    else {
        // Recalculate the slope of the line.
        slope = static_cast<float>(x2 - x1) / (y2 - y1);
        float x = x1;
        for (int i = 0; i < numFrames; ++i) {
            // Increment the x-value based on the slope of the line.
            x += slope;
            // Round the x-value and convert to an integer.
            int x_val = static_cast<int>(std::round(x));
            // Allocate memory for the frame.
            unsigned char ** frame = new unsigned char*[height];
            for (int j = 0; j < height; ++j) {
                frame[j] = new unsigned char[width];
                // Extract the pixel values for each row of the frame from the actualFrame array.
                for (int k = 0; k < width; ++k) {
                    frame[j][k] = FrameSequence::actualFrame[y1 + i + j][x_val + k];
                }
            }
            // Add the frame to the imageSequence vector.
            FrameSequence::imageSequence.push_back(frame);

            for (int j = 0; j < height; ++j) {
                delete frame[j];
            }
            delete [] frame;
        }
    }

}
/**
 * @brief outputs a .pgm files
 * 
 * @param op 
 * @param name 
 */


void FrameSequence::writeFrames(const std::string &  op, const std::string & name) {
    int size = FrameSequence::imageSequence.size();
    
    
    // Loop through all frames in the sequence
    for (int i = 0; i < size; ++i) {

        // Construct the output file path using the frame number
        // and the provided name, with up to 4 digits of leading 0s
        std::stringstream ss;
        ss << "./output/" << name << std::setfill('0') << std::setw(4) << i << ".pgm";
        std::string path = ss.str();

        // Create a new output file stream for the current frame
        std::ofstream ofs(path, std::ios::out | std::ios::binary);

        // Write the PGM header information to the file
        ofs << "P5" << std::endl;
        ofs << FrameSequence::width << " " <<FrameSequence::height << std::endl;
        ofs << 255 << std::endl;
        ofs << std::endl;

        // Depending on the operation requested, write the frame data to the file
        switch(op[0]) {
            case 'r':
                if (op == "reverse") {
                    // Write the current frame in reverse order
                    for (int j = 0; j < FrameSequence::height; ++j ) {
                        ofs.write( reinterpret_cast<char *>(FrameSequence::imageSequence[size - i - 1][j]), FrameSequence::width);
                    }
                } else if (op == "reinvert") {
                    // Write the current frame in reverse order, with inverted colors
                    for (int j = 0; j < FrameSequence::height; ++j ) {
                        for (int k = 0; k < FrameSequence::width; ++k) {
                            ofs << (unsigned char)( 255 - static_cast<int>(FrameSequence::imageSequence[size - i - 1][j][k] )) ;
                        }
                    }
                }
                break;
            case 'i':
                if (op == "invert") {
                    // Write the current frame with inverted colors
                    for (int j = 0; j < FrameSequence::height; ++j ) {
                        for (int k = 0; k < FrameSequence::width; ++k) {
                            ofs << (unsigned char)( 255 - static_cast<int>(FrameSequence::imageSequence[i][j][k]) ) ;
                        }
                    }
                }
                break;
            default:
                // Write the current frame as-is
                for (int j = 0; j < FrameSequence::height; ++j ) {
                    ofs.write( reinterpret_cast<char *>(FrameSequence::imageSequence[i][j]), FrameSequence::width);
                }
        }
    }
}




FrameSequence::~FrameSequence(){
    std::cout<<"Destructor"<<std::endl;

    int size = FrameSequence::imageSequence.size();

    std::cout<<"The size is "<<size<<std::endl;
    // Destroy the imageSequence
    for (int k = 0; k <FrameSequence::height; k++) {
            delete [] FrameSequence::imageSequence[k];
    }
    delete [] FrameSequence::imageSequence;
    FrameSequence::imageSequence.clear();
    std::cout<<"Image Sequence destroyed "<<std::endl; 


    // destroy actual frame
    std::cout<<"Destroyed the actualFrame"<<std::endl;
    for(int i = 0 ;i < FrameSequence::row; ++i) {
        delete [] FrameSequence::actualFrame[i];
    }
    delete [] FrameSequence::actualFrame;

}
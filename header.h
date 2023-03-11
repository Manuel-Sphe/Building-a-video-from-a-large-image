#ifndef IMG
#define IMG

    #include <vector>
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <math.h>
    #include <cmath>
    #include <cstring>
    #include <cstdio>
    #include <memory>

    class FrameSequence{
        private:
            // This an array of fram 
            std::vector<unsigned char**> imageSequence;
            unsigned char** actualFrame;
            int row, col, width, height;

        public:
            FrameSequence(void);
            ~FrameSequence();
            void readImage(const std::string & filename);
            void ExtractImage(int  x1,int x2,int y1,int y2,int w,int h);
            void writeFrames(std::string op, std::string name_base);
            
            
    };
#endif 

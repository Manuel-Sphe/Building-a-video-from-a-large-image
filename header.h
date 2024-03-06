#ifndef IMG
#define IMG

    #include <vector>
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <cmath>
    class FrameSequence {
        private:
            // This an array of frame
            std::vector<unsigned char**> imageSequence;
            unsigned char** actualFrame;
            int row, col, width, height;

        public:
            FrameSequence(void);
            void readImage(const std::string & );
            void ExtractImage(const int & ,const int & ,const  int &,const int & ,const int &,const int & );
            void writeFrames(const std::string & ,const std::string  & );
            ~FrameSequence();
    };
#endif

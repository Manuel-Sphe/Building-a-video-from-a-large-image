#ifndef IMG
#define IMG

    #include <vector>
    #include <string>
    class FrameSequence{
        private:
            // This an array of fram 
            std::vector<unsigned char**> imageSequence;
            unsiged char** myFrame;
            int row, col, width, height;

        public:
            FrameSequence(void);
            ~FrameSequence(void);
            void readImage(std::string filename);
            void ExtractImage(int,int,int,int,int,int);
            
            
    };
#endif 

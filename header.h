#ifndef IMG
#define IMG

    #include <vector>
    #include <string>
    class FrameSequence{
        private:
            // This an array of fram 
            std::vector<unsigned char**> imageSequence;
            int row, col;

        public:
            FrameSequence(void);
            ~FrameSequence(void);
            void readImage(std::string filename);
            
            
    };
#endif 

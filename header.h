#ifndef IMG
#define IMG

    #include <vector>
    class FrameSequence{
        private:
            // This an array of fram 
            std::vector<unsigned char**> imageSequence;
            int row, col;

        public:
            FrameSequence();
            ~FrameSequence();
            
    };
#endif 

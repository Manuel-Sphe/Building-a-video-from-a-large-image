#ifndef IMG
#define IMG

    #include <vector>
    class FrameSequence{
        private:
            std::vector<unsigned char**> imageSequence;
            int row, col;

        public:
            FrameSequence();
            ~FrameSequence();
            
    };
#endif 
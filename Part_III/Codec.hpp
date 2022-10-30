#ifndef CODEC_H
#define CODEC_H

#include <stdlib.h>
#include <sndfile.hh>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Codec {
    private:
        const size_t block_size = 1024;
        const double dctFrac = 0.2;
        
        fstream binaryFile;      // Binary file to decode
        SndfileHandle audioFile; // Audio file to encode

        size_t nChannels; // Number of channels
	    size_t nFrames;   // Number of frames
        size_t nBlocks;   // Number of blocks

        void encode(vector<short> samples); // Encode audio file into binary file
        void decode();                      // Decode binary file into audio file

        void dctTransform(vector<double> &samples); // Perform DCT Transformation
        void dctInvert(vector<double> &samples); // Perform DCT Invertion

    public:
        Codec(const char *filename, char modeIn);

};

#endif
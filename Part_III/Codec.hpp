#ifndef CODEC_H
#define CODEC_H

#include <stdlib.h>
#include <sndfile.hh>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

class Codec {
    private:
        const size_t block_size = 1024; // Size of blocks to be processed in the DCT (1024 is chosen)
        const double dctFrac = 0.2;     // % of low frequency coefficients to be kept (20% is chosen)
        int bit_cut = 4;                // Number of bits to be cut in quantization (4 is chosen)
        
        const char* binaryFile;  // Binary file to decode
        SndfileHandle audioFile; // Audio file to encode

        size_t nChannels; // Number of channels
	    size_t nFrames;   // Number of frames
        size_t nBlocks;   // Number of blocks

        // Encode audio file into binary file, using DCT and quantization
        void encode(vector<short> samples); 

        // Decode binary file into audio file, using IDCT
        void decode();                      

        // Perform DCT-II 
        void dctTransform(vector<double> &samples); 

        // Perform DCT-III (also called IDCT)
        void dctInvert(vector<double> &samples); 

        // Convert int value into binary value with specified length of numBits
        string intToBin(int value, int numBits){
            string aux = "";
            for (int i = numBits-1; i >= 0; i--) {
                int k = value >> i;
            if (k & 1){
                aux+="1";
            }
            else
                aux+="0";
            }
            return aux;
        }

        // Convert binary value (in form of vector<int>) into numeric value
        int binToInt(vector<int> bin){
            reverse(begin(bin), end(bin));
            int val = 0;
            for(int i = 0; i < bin.size(); i++){
                if (bin[i] == 1){
                    val += pow(2, i);
                }
            }
            return val;
        }

    public:
        Codec(const char *filename, char modeIn);

};

#endif
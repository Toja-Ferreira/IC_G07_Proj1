/*---------------------------------------*/
/* COMPILE USING g++ Codec.cpp -lsndfile */
/*---------------------------------------*/
#include "Codec.hpp"
#include "../Part_II/exe6/BitStream.cpp"
#include <sndfile.hh>
#include <stdexcept>
#include <cmath>

using namespace std;

Codec::Codec(const char *filename, char modeIn){
    if (modeIn == 'e' || modeIn == 'E') // Encode audio file to binary file
    { 
        audioFile = filename;
        if(audioFile.error()) {
            throw invalid_argument("ERROR! invalid input audio file\n");
        }

        if((audioFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
            throw invalid_argument("ERROR! file is not in WAV format\n");
        }

        if((audioFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
            throw invalid_argument("ERROR! file is not in PCM_16 format\n");
        }

        nChannels = {static_cast<size_t>(audioFile.channels())};
	    nFrames = {static_cast<size_t>(audioFile.frames())};
        nBlocks = {static_cast<size_t>(ceil(static_cast<double>(nFrames) / block_size))};

        // Number of samples
        vector<short> samples(nChannels * nFrames); 
	    audioFile.readf(samples.data(), nFrames);
        samples.resize(nBlocks * block_size * nChannels);

        // Perform encoding
        encode(samples);
    }

    else if (modeIn == 'd' || modeIn == 'D') // Decode binary file into audio file
    { 
        binaryFile = fstream(filename, ios::binary | ios::out);
        if (!binaryFile.is_open())
        {
            throw runtime_error("ERROR! Could not create binary file to write on");
        }

        // Perform decoding

    }   

    else
    {
        throw invalid_argument("ERROR! usage: <filename, 'e' | 'd'>");
    }
};

void Codec::encode(vector<short> samples){
    try
    {
        dctTransform(samples);
    }
    catch (exception const &e)
    {
        throw invalid_argument("ERROR! There was a problem encoding the file\n");
    }
    /*****************************************************************/
    /* Receber dados do dctTransform e escrever num ficheiro binario */ 
    /*****************************************************************/
}

void Codec::dctTransform(vector<short> samples){

    // Vector for holding DCT computations
    vector<double> val(block_size); 

    // Holds all DCT coefficients, channel by channel
    vector<vector<double>> x_dct(nChannels, vector<double>(nBlocks * block_size)); 

    /*****************************************************************/
    /* Escrever transformacao */ 
    /*****************************************************************/

};

void Codec::decode(){

}

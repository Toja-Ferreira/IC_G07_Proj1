/*---------------------------------------*/
/* COMPILE USING: g++ Codec.cpp -lsndfile */
/*---------------------------------------*/
#include "Codec.hpp"
#include "../Part_II/exe6/BitStream.cpp"
#include "../sndfile-example-src/wav_quant.h"
#include <sndfile.hh>
#include <stdexcept>
#include <cmath>
#include <bitset>
#include <string>

using namespace std;

Codec::Codec(const char *filename, char modeIn)
{
    if (modeIn == 'e' || modeIn == 'E') // Encode audio file into binary file
    {
        audioFile = filename;
        if (audioFile.error())
        {
            throw invalid_argument("ERROR! invalid input audio file\n");
        }

        if ((audioFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV)
        {
            throw invalid_argument("ERROR! file is not in WAV format\n");
        }

        if ((audioFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16)
        {
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
        cout << "Encoding audio file into binary file, please wait..." << endl;
        encode(samples);
    }

    else if (modeIn == 'd' || modeIn == 'D') // Decode binary file into audio file
    {
        binaryFile = filename;
        cout << "Decoding binary file into audio file, please wait..." << endl;
        decode();
    }

    else
    {
        throw invalid_argument("ERROR! usage: <filename, 'e' | 'd'>");
    }
};

void Codec::encode(vector<short> samples)
{   
    // Vector for holding DCT computations
    vector<double> val(block_size);

    // Holds all DCT coefficients, channel by channel
    vector<vector<double>> x_dct(nChannels, vector<double>(nBlocks * block_size));

    // Perform DCT-II transformation
    try
    {
        for (size_t n = 0; n < nBlocks; n++)
        {
            for (size_t c = 0; c < nChannels; c++)
            {
                double sumT = 0;
                for (size_t k = 0; k < block_size; k++)
                {
                    val[k] = samples[(n * block_size + k) * nChannels + c];
                }
        
                dctTransform(val);

                for (size_t k = 0; k < block_size * dctFrac; k++)
                {
                    x_dct[c][n * block_size + k] = val[k] / (block_size << 1);
                    samples[(n * block_size + k) * nChannels + c] += static_cast<short>(round(x_dct[c][n * block_size + k]));
                }
            }
        }

        // Perform quantization
        size_t i {};
        for(auto &s: samples){
            samples[i++] = s >> bit_cut;
        }

        // Write to binary file using BitStream class
        BitStream encodedFile("encodedAudio", 'w');

        // Write binary file header containing important info 
        string hFrames = Codec::intToBin(audioFile.frames(), 32);         // Frames      -> 32 bits
        string hSampleRate = Codec::intToBin(audioFile.samplerate(), 32); // Sample Rate -> 32 bits
        string hFormat = Codec::intToBin(audioFile.format(), 32);         // Format      -> 32 bits
        string hChannels = Codec::intToBin(audioFile.channels(), 8);      // Channels    -> 8 bits
        encodedFile.writeNBits(hFrames.c_str(), 32);
        encodedFile.writeNBits(hSampleRate.c_str(), 32);
        encodedFile.writeNBits(hFormat.c_str(), 32);
        encodedFile.writeNBits(hChannels.c_str(), 8);

        // Write sample data
        for(auto s : samples){
            string toBinary = bitset<16>(s).to_string();
            encodedFile.writeNBits(toBinary.c_str(), 16);
        }
        encodedFile.closeFile();

        cout << "A binary file with the encoded audio data has been created!" << endl;
    }
    catch (exception const &e)
    {
         throw runtime_error("An error occurred while encoding the file\n");
    }
}

void Codec::decode()
{ 
    // Get data from binary file to read
    ifstream mybinfile(binaryFile, ios::binary);
    mybinfile.seekg(0, ios::end);
    int file_size = mybinfile.tellg();
    mybinfile.seekg(0, ios::beg);
    mybinfile.close();

    // Read from binary file using BitStream class
    BitStream binToDecode(binaryFile, 'r');

    // Read binary file header
    int hFrames = binToInt(binToDecode.readNBits(32));
    int hSampleRate = binToInt(binToDecode.readNBits(32));
    int hFormat = binToInt(binToDecode.readNBits(32));
    int hChannels = binToInt(binToDecode.readNBits(8));

    // Read sample data and save in vector, to later write in audio file
    vector<int> aux;
    short shortVal;
    string binStr;
    vector<short> fileData;

    for(int i = 0; i < file_size; i++){
        aux = binToDecode.readNBits(16);
        for (int j = 0; j < 16; j++) {
            binStr.append(to_string(aux[j]));
        }
        fileData.push_back(static_cast<short>(stoi(binStr, 0, 2)));
        binStr = "";
        aux = {};
    }
    binToDecode.closeFile(); 

    /* 
    *
    * Although DCT-III (IDCT) transformation is correctly implemented in a function, we couldnt
    * successfuly apply it to the data
    * Thus, the sample data written in the new decoded audio file will be the one obtained directly 
    * from the binary file 
    *  
    */

    try
    {
        SndfileHandle sfhOut{"decodedAudio.wav", SFM_WRITE, hFormat, hChannels, hSampleRate};
        sfhOut.writef(fileData.data(), hFrames);
        cout << "The audio file has been created!" << endl;
    }
    catch (exception const &e)
    {
        throw runtime_error("An error occurred while decoding the file\n");
    }
    
}


void Codec::dctTransform(vector<double> &toTransform)
{
    double sqrtVal = sqrt(2/toTransform.size()); // Value of sqrt(2/N), as specified in the DCT-II formula
    for (size_t k = 0; k < block_size ; k++){
        double sum = 0;
        for (size_t n = 0; n < block_size; n++) {
            sum += toTransform[n] * cos((M_PI * k * (2*n+1)) / (block_size << 1));
        }
        if(k == 0){
            toTransform[k] = sqrtVal * (1 / sqrt(2)) * sum;
        }
        else{
            toTransform[k] = sqrtVal * sum;
        }
    }
}

void Codec::dctInvert(vector<double> &toInvert)
{   
    double sqrtVal = sqrt(2/toInvert.size()); // Value of sqrt(2/N), as specified in the DCT-III formula
    for (size_t k = 0; k < block_size ; k++){
        double sum = 0;
        for (size_t n = 0; n < block_size; n++) {
            if(k == 0){
                sum += (1 / sqrt(2)) * toInvert[n] * cos((M_PI * k * (2*n+1)) / (block_size << 1));
            }
            else{
                sum += toInvert[n] * cos((M_PI * k * (2*n+1)) / (block_size << 1));
            }
        }
        toInvert[k] = sqrtVal * sum;
    }
}
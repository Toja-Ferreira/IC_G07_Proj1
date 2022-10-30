/*---------------------------------------*/
/* COMPILE USING g++ Codec.cpp -lsndfile */
/*---------------------------------------*/
#include "Codec.hpp"
#include "../Part_II/exe6/BitStream.cpp"
#include "../sndfile-example-src/wav_quant.h"
#include <sndfile.hh>
#include <stdexcept>
#include <cmath>

using namespace std;

Codec::Codec(const char *filename, char modeIn)
{
    if (modeIn == 'e' || modeIn == 'E') // Encode audio file to binary file
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
        encode(samples);
    }

    else if (modeIn == 'd' || modeIn == 'D') // Decode binary file into audio file
    {
        binaryFile = fstream(filename, ios::binary | ios::out);
        if (!binaryFile.is_open())
        {
            throw runtime_error("ERROR! Could not create binary file to write on");
        }
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
                }
            }
        }
        
        for(size_t n = 0 ; n < nBlocks ; n++)
        {
            for(size_t c = 0 ; c < nChannels ; c++)
            {
                for(size_t k = 0 ; k < block_size ; k++)
                {   
                    val[k] = x_dct[c][n * block_size + k];
                }

                dctInvert(val);

                for(size_t k = 0 ; k < block_size ; k++)
                {   
                    samples[(n * block_size + k) * nChannels + c] += static_cast<short>(round(val[k]));
                }
            }
        }  
    
        try
        {
            SndfileHandle sfhOut{"compressed.wav", SFM_WRITE, audioFile.format(),
                                audioFile.channels(), audioFile.samplerate()};
            sfhOut.writef(samples.data(), audioFile.frames());
        }
        catch (exception const &e)
        {
            throw runtime_error("An error occurred while compressing the file\n");
        }
        cout << "A DCT compressed version of the audio file has been created!" << endl;
    }
    catch (exception const &e)
    {
        throw invalid_argument("ERROR! There was a problem encoding the file\n");
    }
    /*****************************************************************/
    /* Receber dados do dctTransform e escrever num ficheiro binario */
    /*****************************************************************/
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
    double sqrtVal = sqrt(2/toInvert.size()); // Value of sqrt(2/N), as specified in the DCT-II formula
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

void Codec::decode()
{
}

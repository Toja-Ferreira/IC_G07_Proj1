/*---------------------------------------*/
/* COMPILE USING: g++ test.cpp -lsndfile */
/*---------------------------------------*/
#include "../Codec.cpp"
#include <iostream>

using namespace std;

int main(){ 

    cout << "---------------------------------------------------------------------\n\n";

    // Change your audio file to encode here
    Codec encodeAudioFile("original.wav", 'e');

    cout << "\n---------------------------------------------------------------------\n\n";

    // Change your binary file to decode here
    Codec decodeBinaryFile("encodedAudio", 'd');

    cout << "\n---------------------------------------------------------------------\n";

}

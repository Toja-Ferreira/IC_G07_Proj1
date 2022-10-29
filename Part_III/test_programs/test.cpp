/*---------------------------------------*/
/* COMPILE USING g++ test.cpp -lsndfile */
/*---------------------------------------*/
#include "../Codec.cpp"
#include <iostream>

using namespace std;

int main(){

    Codec encodeAudioFile("sample.wav", 'e');

}

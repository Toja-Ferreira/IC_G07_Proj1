#include "../exe6/BitStream.cpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace std;

int main(int argc, char** argv){
    if (argc != 2)
    {
        throw invalid_argument("ERROR! Usage: <./decode filename>");
    }else if(!filesystem::exists(argv[1])){
        throw invalid_argument("ERROR! Please choose an existing binary file to decode to txt!");
    }

    try
    {
        //bin file to read from
        BitStream bsIn(argv[1], 'r');

        //txt file to write to
        ofstream mytxtfile("mytxtfile.txt");

        //size of file in bits
        ifstream myfile(argv[1], ios::binary);
        myfile.seekg(0, ios::end);
        int file_size = myfile.tellg();
        myfile.close();

        vector<int> arr;

        for(int i = 0; i < file_size; i++){
            arr = bsIn.readNBits(8);
            for (int j = 0; j < 8; j++) {
                mytxtfile << arr[j];
            }
            arr = {};
        }

        //close file
        mytxtfile.close();
        //close bitstream
        bsIn.closeFile();
    }
    catch(const exception& e)
    {
        cerr << "An error occurred while decoding the file:\n" << e.what() << endl;
    }
    cout<<"Binary file decoded successfully to mytxtfile.\n";
    return 0;
}
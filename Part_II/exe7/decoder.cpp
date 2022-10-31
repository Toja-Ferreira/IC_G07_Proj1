#include "../exe6/BitStream.cpp"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv){
    if (argc != 2)
    {
        throw invalid_argument("ERROR! Usage: <./decoder filename>");
    }

    try
    {
        //size of file in bits
        ifstream mybinfile(argv[1], ios::binary);
        if(!mybinfile.is_open()){
            throw invalid_argument("ERROR! Could not open binary file. Check if the file exists!");
        }

        //size of file in bytes
        mybinfile.seekg(0, ios::end);
        int file_size = mybinfile.tellg();
        mybinfile.seekg(0, ios::beg);

        //bin file to read from
        BitStream bsIn(argv[1], 'r');

        //txt file to write to
        ofstream mytxtfile("decodedFile.txt");

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
        cout<<"Binary file decoded successfully to decodedFile.txt.\n";
    }
    catch(const exception& e)
    {
        cerr << "An error occurred while decoding the file:\n" << e.what() << endl;
    }
    return 0;
}
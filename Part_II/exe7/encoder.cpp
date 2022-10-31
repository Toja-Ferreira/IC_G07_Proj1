#include "../exe6/BitStream.cpp"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv){
    if (argc != 2)
    {
        throw invalid_argument("ERROR! Usage: <./encoder filename.txt>");
    }

    try
    {
        int cnt = 0;
        char ch;

        //txt file to read from
        ifstream mytxtfile (argv[1]);
        if(!mytxtfile.is_open()){
            throw invalid_argument("ERROR! Could not open txt file. Check if the file exists!");
        }

        //size of file in bytes
        mytxtfile.seekg(0, ios::end);
        int file_size = mytxtfile.tellg();
        mytxtfile.seekg(0, ios::beg);

        //bin file to write to
        fstream encodedFile;
        BitStream bsOut("encodedFile", 'w');

        string mystring = "";
        char arr[mystring.length() + 1];
        
        while(mytxtfile >> noskipws >> ch){
            if(mystring.length() == 8){
                strncpy(arr,mystring.c_str(),8);
                bsOut.writeNBits(arr,8);
                mystring = "";
                cnt = 0;
            }
            mystring += ch;
            cnt++;
        }
        strncpy(arr,mystring.c_str(),strlen(arr));
        bsOut.writeNBits(arr,(file_size+cnt)-file_size);
        //close file
        mytxtfile.close();
        //close bitstream
        bsOut.closeFile();
        cout<<"Text file encoded successfully to encodedFile.\n";
    }
    catch(const exception& e)
    {
        cerr << "An error occurred while encoding the file:\n" << e.what() << endl;
    }
    return 0;
}
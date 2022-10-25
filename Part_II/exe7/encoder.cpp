#include "../exe6/BitStream.cpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace std;

int main(int argc, char** argv){
    if (argc != 2)
    {
        throw invalid_argument("ERROR! Usage: <./encode filename.txt>");
    }else if(!filesystem::exists(argv[1])){
        throw invalid_argument("ERROR! Please choose an existing txt file to encode to binary!");
    }

    try
    {
        int cnt = 0;
        char ch;

        //size of file in bits
        ifstream myfile (argv[1], ios::binary);
        myfile.seekg(0, ios::end);
        int file_size = myfile.tellg();
        myfile.close();

        //txt file to read from
        ifstream mytxtfile (argv[1]);

        //bin file to write to
        fstream mybinfile;
        BitStream bsOut("mybinfile", 'w');

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
    }
    catch(const exception& e)
    {
        cerr << "An error occurred while encoding the file:\n" << e.what() << endl;
    } 
    cout<<"Text file encoded successfully to mybinfile.\n";
    return 0;
}
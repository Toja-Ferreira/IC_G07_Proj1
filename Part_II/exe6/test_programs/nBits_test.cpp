#include "BitStream.cpp"
#include <iostream>

using namespace std;

int main(){

    /* Test N bit writing mode --> output file should contain 00100011 10000000*/
    BitStream testMultipleWrite("multiple_write_file", 'w');

    // Writes 00100011 -> "#"
    testMultipleWrite.writeNBits("00100011", 8);

    // Writes 1 bit and the class function automatically fills the remaining 7 bits to write 10000000
    testMultipleWrite.writeNBits("1", 1);

    testMultipleWrite.closeFile();
    cout << "File named multiple_write_file has been written!" << "\n";

    /*...................................................................................................*/

    /* Test  N bit reading mode --> reads from file containing 00100011 10000000 */
    BitStream testMultipleRead("multiple_read_file", 'r');

    // Outputs the first 5 bits of file -> 00100
    cout << "The first 5 bits from the file are: \n";
    for(auto i : testMultipleRead.readNBits(5)){
        cout << i;
    }
    cout << "\n";
    
    testMultipleRead.closeFile();
}
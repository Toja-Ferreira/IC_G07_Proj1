#include "../BitStream.cpp"
#include <iostream>

using namespace std;

int main(){

    /* Test N bit writing mode --> output file should contain 00100011 10000000*/
    BitStream testMultipleWrite("multiple_write_file", 'w');

    // Writes 00100011 -> "#"
    testMultipleWrite.writeNBits("00100011", 8);

    // Writes 1 bit and the Bitstream class automatically fills the remaining 7 bits to write 10000000
    testMultipleWrite.writeNBits("1", 1);

    testMultipleWrite.closeFile();
    cout << "File named multiple_write_file has been written!" << "\n";

    /*...................................................................................................*/

    /* Test N bit reading mode --> reads from file containing 00100011 10000000 */
    BitStream testMultipleRead("test_read_file", 'r');

    // Outputs the first 16 bits of file -> 00100011 10000000
    cout << "The first 16 bits from test_read_file are: \n";
    for(auto i : testMultipleRead.readNBits(16)){
        cout << i;
    }
    cout << "\n";
    
    testMultipleRead.closeFile();
}
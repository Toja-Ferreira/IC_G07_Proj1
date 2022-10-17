#include "BitStream.cpp"
#include <iostream>

using namespace std;

int main(){

    /* Test single bit writing mode --> output file should have 
    "#" (which is represented by 00100011) */
    BitStream testWrite ("write_file", 'w');
    testWrite.writeBit(0);
    testWrite.writeBit(0);
    testWrite.writeBit(1);
    testWrite.writeBit(0);
    testWrite.writeBit(0);
    testWrite.writeBit(0);
    testWrite.writeBit(1);
    testWrite.writeBit(1);
    testWrite.closeFile();
    
    /* Test single bit reading mode --> reads from file containing 00100011 */
    BitStream testRead ("read_file", 'r');
    cout << testRead.readBit(); // Returns 0
    cout << testRead.readBit(); // Returns 0
    cout << testRead.readBit(); // Returns 1
    cout << testRead.readBit(); // Returns 0
    cout << testRead.readBit(); // Returns 0
    cout << testRead.readBit(); // Returns 0
    cout << testRead.readBit(); // Returns 1
    cout << testRead.readBit(); // Returns 1
    cout << "\n";
    testRead.closeFile();
}
#include "../BitStream.cpp"
#include <iostream>

using namespace std;

int main(){

    /* Test single bit writing mode --> output file should contain 00100011 10000000*/
    BitStream testSingleWrite ("single_write_file",'w');

    // Writes 00100011 -> "#"
    testSingleWrite.writeBit(0);
    testSingleWrite.writeBit(0);
    testSingleWrite.writeBit(1);
    testSingleWrite.writeBit(0);
    testSingleWrite.writeBit(0);
    testSingleWrite.writeBit(0);
    testSingleWrite.writeBit(1);
    testSingleWrite.writeBit(1);

    // Writes 1 bit and the Bitstream class automatically fills the remaining 7 bits to write 10000000
    testSingleWrite.writeBit(1);

    testSingleWrite.closeFile();
    cout << "File named single_write_file has been written!" << "\n";
    
    /*...................................................................................................*/

    /* Test single bit reading mode --> reads from file containing 00100011 10000000 */
    BitStream testSingleRead ("test_read_file", 'r');
    cout << "File named test_read_file contains the following bits: \n";
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 1
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 1
    cout << testSingleRead.readBit(); // Returns 1

    cout << testSingleRead.readBit(); // Returns 1
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << testSingleRead.readBit(); // Returns 0
    cout << "\n";
    testSingleRead.closeFile();
}
#include "ALU.h"

int ALU::successiveOpCode(string arr[], int index, OpCodeFunction opCode, bool iter) {
    cout << arr[index] << " : ";

    index++;  // go to location of first operand

    // Retrive the first value
    uint32_t cumulative;
    stringstream base; // new, clean stringstream
    
    base << hex << arr[index]; // read in raw as hex type
    base >> cumulative;  // input into cumulative;

    index++;  // move to (what could be) second operand

    if (!iter) cumulative = opCode(cumulative, 0);  // if not iteratable, then run on single instruction and punt out

    // Otherwise, we iterate on the instruction
    while (arr[index][0] >= 48 && arr[index][0] <= 57 && iter) {  //ASCII range of numerical characters. Check to make sure not a command
        //TODO: add support for other bases?
        uint32_t operand;
        stringstream raw; // new, clean stringstream

        raw << hex << arr[index]; // read in raw as hex type
        raw >> operand;  // input into operand;

        index++; // move to next loaction

        // perform calculation
        if (iter) { cumulative = opCode(cumulative, operand); } // call successive op code

    }
    
    hexPrint(cumulative);

    return index-1;  // we've jumped to next command return prior index
}

uint32_t ALU::ALUOPCode(unsigned char code, uint32_t op1) {
}
uint32_t ALU::ALUOPCode(unsigned char code, uint32_t op1, uint32_t op2) {

}

uint32_t ALU::ADD(uint32_t c, uint32_t o) { return c + o; } // Addative
uint32_t ALU::AND(uint32_t c, uint32_t o) { return c & o; } // bitwise and
uint32_t ALU::LSR(uint32_t c, uint32_t o) { return c >> 1; }
uint32_t ALU::LSL(uint32_t c, uint32_t o) { return c << 1; }
uint32_t ALU::NOT(uint32_t c, uint32_t o) { return ~c; }
uint32_t ALU::ORR(uint32_t c, uint32_t o) { return c | o; } // bitwise or
uint32_t ALU::SUB(uint32_t c, uint32_t o) { return c - o; } // subtractive
uint32_t ALU::XOR(uint32_t c, uint32_t o) { return c ^ o; } // bitwise xor
uint32_t ALU::ASR(uint32_t c, uint32_t o) {
    if (c >= 0x80000000) return (c >> 1) + 0x80000000; // if the msb is a 1, we must preserve it
    return c >> 1;  // otherwise, we good
}


void ALU::hexPrint(uint32_t& result) { cout << "Result: 0x" << hex << result << endl; }  // Printing

#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <sstream>

using namespace std;

typedef uint32_t (*OpCodeFunction)(uint32_t, uint32_t);

int successiveOpCode(string[], int, OpCodeFunction, bool);
uint32_t ALUOPCode(unsigned char, uint32_t, uint32_t);

uint32_t ADD(uint32_t, uint32_t);  // successive addative
uint32_t AND(uint32_t, uint32_t);  // successive and-ing
uint32_t ASR(uint32_t, uint32_t);
uint32_t LSR(uint32_t, uint32_t); 
uint32_t LSL(uint32_t, uint32_t);
uint32_t NOT(uint32_t, uint32_t);
uint32_t ORR(uint32_t, uint32_t);
uint32_t SUB(uint32_t, uint32_t);
uint32_t XOR(uint32_t, uint32_t);

void hexPrint(uint32_t&);

// Globals
OpCodeFunction codec[9] = { &ADD, &SUB, &AND, &ORR, &XOR, &NOT, &ASR, &LSR, &LSL};




// Implementation
int successiveOpCode(string arr[], int index, OpCodeFunction opCode, bool iter) {
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

uint32_t ALUOPCode(unsigned char code, uint32_t op1, uint32_t op2) {
	return codec[code](op1, op2);
}

uint32_t ADD(uint32_t c, uint32_t o) { return c + o; } // Addative
uint32_t AND(uint32_t c, uint32_t o) { return c & o; } // bitwise and
uint32_t LSR(uint32_t c, uint32_t o) { return c >> 1; }
uint32_t LSL(uint32_t c, uint32_t o) { return c << 1; }
uint32_t NOT(uint32_t c, uint32_t o) { return ~c; }
uint32_t ORR(uint32_t c, uint32_t o) { return c | o; } // bitwise or
uint32_t SUB(uint32_t c, uint32_t o) { return c - o; } // subtractive
uint32_t XOR(uint32_t c, uint32_t o) { return c ^ o; } // bitwise xor
uint32_t ASR(uint32_t c, uint32_t o) {
    if (c >= 0x80000000) return (c >> 1) + 0x80000000; // if the msb is a 1, we must preserve it
    return c >> 1;  // otherwise, we good
}


void hexPrint(uint32_t& result) { cout << "Result: 0x" << hex << result << endl; }  // Printing


#endif
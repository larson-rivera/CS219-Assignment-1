//Programming Task 2: OP Code Simulator -- Main Driver
//Author: Larson Rivera
//Last modified: 2/26/2022

#include <iostream>
#include <fstream>
#include <sstream>

#include "ALU.h"

using namespace std;

// Globals
enum ALUCodes {ADD = 0, SUB, AND, ORR, XOR, NOT, ASR, LSR, LSL, MOV};
string ALUCodec[10] = {"ADD", "SUB", "AND", "ORR", "XOR", "NOT", "ASR", "LSR", "LSL", "MOV"};

enum Register {R0 = 0, R1, R2, R3, R4, R5, R6, R7};
string RegCodec[8] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7"};

// Prototypes
uint32_t moveRegister(unsigned char, uint32_t);
unsigned char stringToOpCode(string);
unsigned char stringToRegister(string);
uint32_t stringToHex(string);

ifstream fin;  // Input stream

string filename;
string input[100]; // raw input;

uint32_t regs[8] = {0};


// MAIN FUNCTION--------------------------------------------------------------
int main() {

    // Open the file
    do {
        cout << "Welcome to the Calculator. Please enter a file for analysis: ";
        cin >> filename;
        fin.open(filename.c_str());
    } while (!fin);

    // Read everything into a string
    int count = 0;                 // total Word Count

    while (!fin.eof()) {           // Read through the entire file
        fin >> input[count];
        count++;
    }
    fin.close();                   //close the file when done

    uint32_t i = 0; 
    while (i < count) {
        unsigned char opCode = stringToOpCode(input[i]);  // Get opCode
        unsigned char Rd = stringToRegister(input[i+1]);  // Get RD
        uint32_t oldVal;
        uint32_t Rn = regs[stringToRegister(input[i+3])]; // Get Rn (if there is one)

        if (opCode == MOV) {
            oldVal = moveRegister(Rd, stringToHex(input[i+3]));
            // Register Printouts
        }

        if (input [i+4] == ",") {  // This is a dual OP Code like add, sub, etc
            uint32_t Rm = regs[stringToRegister(input[i+5])];  // get RM

            oldVal = regs[Rd];
            regs[Rd] = ALU::ALUOPCode(opCode, Rn, Rm);
        } 
        
        else {  // This is a single op code like shifts
            oldVal = regs[Rd];
            regs[Rd] = ALU::ALUOPCode(opCode, Rn, 0);
        }
    }

    // Important Array Input information
    // MOV RD , RN , RM
    // 0    1 2  3 4  5

    return 0;
}

uint32_t moveRegister(unsigned char destination, uint32_t value) {
    uint32_t previousValue = regs[destination];
    regs[destination] = value;
    return previousValue;
}

unsigned char stringToOpCode(string input) {
    for (unsigned char i = 0; i < 10; i++) {
        if (input == ALUCodec[i]) return i;
    }
    return -1;
}

unsigned char stringToRegister(string input) {
    for (unsigned char i = 0; i < 8; i++) {
        if (input == RegCodec[i]) return i;
    }
    return -1;
}

uint32_t stringToHex(string input) {
    uint32_t conv;
    stringstream raw; // new, clean stringstream

    raw << hex << input; // read in raw as hex type
    raw >> conv;  // input into operand;
    return conv;
}
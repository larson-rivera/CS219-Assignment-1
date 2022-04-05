//Programming Task 2: OP Code Simulator -- Main Driver
//Author: Larson Rivera
//Last modified: 2/26/2022

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "ALU.h"

using namespace std;

// Globals
string ALUCodec[10] = {"ADD", "SUB", "AND", "ORR", "XOR", "NOT", "ASR", "LSR", "LSL", "MOV"};

enum Register {R0 = 0, R1, R2, R3, R4, R5, R6, R7};
string RegCodec[8] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7"};

// Prototypes
uint32_t moveRegister(int, uint32_t);
int stringToOpCode(string);
int stringToRegister(string);
uint32_t stringToHex(string);
void opCodePrintout(int, int, uint32_t, uint32_t);

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
        transform(input[count].begin(), input[count].end(), input[count].begin(), ::toupper);
        // Convert to upper case
        count++;
    }
    fin.close();                   //close the file when done

    cout << "Loading Complete..." << endl;

    // PROCESSING SECTION
    uint32_t i = 0; 
    while (i < count) {

        if (input[i].compare("END") == 0) break; // Condition for end of program

        int opCode = stringToOpCode(input[i]);  // Get opCode
        int Rd = stringToRegister(input[i+1]);  // Get RD
        uint32_t oldVal;
        int Rn, Rm;

        if (opCode == 9) {
            if (input[i+2][0] == 'R') oldVal = moveRegister(Rd, regs[stringToRegister(input[i+2])]); // moving registers
            else oldVal = moveRegister(Rd, stringToHex(input[i+2]));  // moving literal values
            i += 3;
        }

        else if (input [i+3][0] == 'R') {  // This is a dual OP Code like add, sub, etc
            Rn = regs[stringToRegister(input[i+2])];
            uint32_t Rm = regs[stringToRegister(input[i+3])];  // get RM

            oldVal = regs[Rd];
            regs[Rd] = ALUOPCode(opCode, Rn, Rm);
            i += 4;
        } 
        
        else {  // This is a single op code like shifts
            Rn = regs[stringToRegister(input[i+2])];
            oldVal = regs[Rd];
            regs[Rd] = ALUOPCode(opCode, Rn, 0);
            i += 3;
        }

        opCodePrintout(opCode, Rd, oldVal, regs[Rd]);
    }

    // Important Array Input information
    // MOV RD, RN, RM
    // 0    1   2   3

    return 0;
}

uint32_t moveRegister(int destination, uint32_t value) {
    uint32_t previousValue = regs[destination];
    regs[destination] = value;
    return previousValue;
}

int stringToOpCode(string input) {
    for (int i = 0; i < 10; i++) {
        if (input.compare(ALUCodec[i]) == 0) return i;
    }
    return -1;
}

int stringToRegister(string input) {
    for (int i = 0; i < 8; i++) {
        if (input.substr(0,2).compare(RegCodec[i]) == 0) return i;
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

void opCodePrintout(int opc, int r, uint32_t old, uint32_t ne) {
    cout << "OPCode " << ALUCodec[opc] << " is modifying Register " << RegCodec[r] << "\n";
    cout << "\t Old Value: " << old << "\n";
    cout << "\t New Value: " << ne << endl << endl;
}
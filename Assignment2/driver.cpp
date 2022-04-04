//Programming Task 2: OP Code Simulator -- Main Driver
//Author: Larson Rivera
//Last modified: 2/26/2022

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Globals
ifstream fin;  // Input stream

string filename;
string input[100]; // raw input;

// Protoypes
typedef uint32_t (*OpCodeFunction)(uint32_t, uint32_t);
int successiveOpCode(string[], int, OpCodeFunction, bool);

uint32_t ADD(uint32_t, uint32_t);  // sucerssive addative
uint32_t AND(uint32_t, uint32_t);  // successive and-ing
uint32_t ASR(uint32_t, uint32_t);
uint32_t LSR(uint32_t, uint32_t); 
uint32_t LSL(uint32_t, uint32_t);
uint32_t NOT(uint32_t, uint32_t);
uint32_t ORR(uint32_t, uint32_t);
uint32_t SUB(uint32_t, uint32_t);
uint32_t XOR(uint32_t, uint32_t);

void hexPrint(uint32_t&);


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

    // Processing Assembly
    int i = 0;
    while (i <= count) {
        // Successive Op Codes
        if (input[i] == "ADD") i = successiveOpCode(input, i, (OpCodeFunction) &ADD, true);
        if (input[i] == "AND") i = successiveOpCode(input, i, (OpCodeFunction) &AND, true);
        if (input[i] == "ORR") i = successiveOpCode(input, i, (OpCodeFunction) &ORR, true);
        if (input[i] == "SUB") i = successiveOpCode(input, i, (OpCodeFunction) &SUB, true);
        if (input[i] == "XOR") i = successiveOpCode(input, i, (OpCodeFunction) &XOR, true);

        //isolated Op Codes
        if (input[i] == "ASR") i = successiveOpCode(input, i, (OpCodeFunction) &ASR, false);
        if (input[i] == "LSR") i = successiveOpCode(input, i, (OpCodeFunction) &LSR, false);
        if (input[i] == "LSL") i = successiveOpCode(input, i, (OpCodeFunction) &LSL, false);
        if (input[i] == "NOT") i = successiveOpCode(input, i, (OpCodeFunction) &NOT, false);
        i++;
    }

    return 0;
}

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

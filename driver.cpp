//Programming Task 1: Assembly Adder -- Main Driver
//Author: Larson Rivera
//Last modified: 1/25/2022

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Globals
ifstream fin;  // Input stream

string filename;
string input[100]; // raw input;

// Protoypes
int successiveAddHex(string[], int);
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
        if (input[i] == "ADD") i = successiveAddHex(input, i);
        i++;
    }

    return 0;
}

int successiveAddHex(string arr[], int index) {
    uint32_t cumulative = 0;
    index++;  // move to first operand, current index is still command

    while (arr[index][0] >= 48 && arr[index][0] <= 57) {  //ASCII range of numerical characters. Check to make sure not a command
        //TODO: add support for other bases?
        uint32_t operand;
        stringstream raw; // new, clean stringstream

        raw << hex << arr[index]; // read in raw as hex type
        raw >> operand;  // input into operand;
        cumulative += operand;  // successive add

        index++; // move to next loaction
    }
    
    hexPrint(cumulative);

    return index-1;  // when new command detected, return modified index
}

void hexPrint(uint32_t& result) { cout << "Result: 0x" << hex << result << endl; }  // Printing

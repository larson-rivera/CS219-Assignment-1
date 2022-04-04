#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <sstream>

using namespace std;

typedef uint32_t (*OpCodeFunction)(uint32_t, uint32_t);

class ALU {
	private :
		static int successiveOpCode(string[], int, OpCodeFunction, bool);

		static uint32_t ADD(uint32_t, uint32_t);  // successive addative
        static uint32_t AND(uint32_t, uint32_t);  // successive and-ing
        static uint32_t ASR(uint32_t, uint32_t);
        static uint32_t LSR(uint32_t, uint32_t); 
        static uint32_t LSL(uint32_t, uint32_t);
		static uint32_t NOT(uint32_t, uint32_t);
		static uint32_t ORR(uint32_t, uint32_t);
		static uint32_t SUB(uint32_t, uint32_t);
		static uint32_t XOR(uint32_t, uint32_t);

    public :
		static uint32_t ALUOPCode(unsigned char code, uint32_t op1, uint32_t op2);

		static void hexPrint(uint32_t&);
};	

#endif
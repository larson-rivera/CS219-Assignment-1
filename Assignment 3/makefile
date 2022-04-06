#Programming Task 1: Text Analyzer -- Makefile
#Author: Larson Rivera
#Last modified: 9/6/20


all: assembly_calculator # All target 

assembly_calculator: driver.o  # Build from driver and word analysis objects
	g++ -o assembly_calculator driver.o

driver.o: driver.cpp ALU.h # Main driver object
	g++ -c -o driver.o driver.cpp

clean:  # cleaning target
	rm -rf *.o assembly_calculator
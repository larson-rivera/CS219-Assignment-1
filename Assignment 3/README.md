CS219, Spring 2022, Professor Poplin :: 
Larson Rivera, University of Nevada, Reno ::
Last Modified on 4/5/2022

===Programming Assignment 3===

---Accessing Instructions---

This program/assignment is available in a public github repository: https://github.com/larson-rivera/CS219-Assignment-1
This is the same repository as assingments 1 and 2, however, the most recent commit contains the final code for assignment 3.



---Build Instructions---

Builds with Linux Make. Main target is 'assembly_calculator'
    'Make all' will also suffice.



---Usage Instructions---

This program runs in-terminal and prompts the user to enter a filname with extension:
    EX: input.txt

The program will continue to prompt for a filename until it finds one it can open succesfully. Results displayed in-terminal.
A demo file "input.txt" is provided.



---Sources Used in Development---

A GeeksForGeeks article on the StringStream class in the base library was used to understand and develop hex conversion from strings
    "StringStream in C++ for Decimal to Hexadecimal and back": https://www.geeksforgeeks.org/stringstream-c-decimal-hexadecimal-back/

A CProgramming article on Function Pointers and a Stack Overflow thread on the same subject were used to understand function pointers for the purpose of this assignment. 
    "Function Pointers in C and C++": https://www.cprogramming.com/tutorial/function-pointers.html
    "Function Pointer as Paramerter?": https://stackoverflow.com/questions/2582161/function-pointer-as-parameter

A Stack Overflow thread on using the Algorithm library to convert strings to upper case letters. Used on line 51 driver.cpp
    "How to Convert a C++ String to Uppercase": https://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase

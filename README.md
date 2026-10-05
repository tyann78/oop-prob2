=====================================================
Project 1 - Problem #2: Student Information Management System

Environment

OS: macOS

Compiler: Apple clang version 21.0.0 (Target: arm64-apple-darwin27.0.0)

How to Compile
Using the provided Makefile:
$ make

(Alternatively, direct compilation without Makefile:
$ g++ -std=c++11 -Wall -o a.exe main.cpp StudentManager.cpp
)

How to Execute
Run the executable with the database text file name as a command-line argument:
$ ./a.exe file1.txt

Clean up (Optional)
To delete intermediate object files (.o) and the compiled executable:
$ make clean
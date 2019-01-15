#Sudoku-Solver

##Introduction
A minimal Sudoku Solver implemented in Visual C++ to solve all possible 9X9 sudokus. Algorithm used is a hybrdi algorithm-Constraint based and Backtrack Brute Force algorithm.

##Running the application
Just run the application backtrack_sudoku.exe and input the test filename

##Pre-requisites to compile the code
Visual Studio with C++ installed

##Running the tests
The solvable sudokus are the ones with atleast 17 given numbers or hints. Hence only those sudoku are "Valid". 
The application takes input of the problem sudoku from a text file.

Real sudoku:
-------------------------------
| 8  _  _ | _  5  _ | _  _  3 |
| _  _  _ | 4  6  _ | 7  _  _ |
| _  _  _ | 1  _  _ | 4  _  9 |
-------------------------------
| _  8  1 | _  _  _ | _  7  4 |
| 5  _  _ | _  _  _ | _  _  6 |
| 7  3  _ | _  _  _ | 8  1  _ |
-------------------------------
| 4  _  8 | _  _  6 | _  _  _ |
| _  _  2 | _  4  9 | _  _  _ |
| 1  _  _ | _  2  _ | _  _  8 |
-------------------------------

Input sudoku in file:
8...5...3
...46.7..
...1..4.9
.81....74
5.......6
73....81.
4.8..6...
..2.49...
1...2...8

The _ are replaced with . without any spaces and are left indentated. 
Do make sure to save the test file in the same directory as that of the application.

##Built With
Visual Studio


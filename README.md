# Threads-Vs-Process
Matrix multipliaction made by a sequential, process or thread program

# What's this project?
First there's a base program called 'Auxiliar.c' that recives matrix 1 rows and columns and matrix 2 rows and columns by the command line, and then creates random numbers, populate the matrixes with it, and save it in two .txt files separately.

And There are 3 programs that make the same thing: Matrix multipliaction and save every result in a file with the time that it took to calculate every cell and the total time the program took to do all the calculations. 
In Process and Threads case it will save the total time that process or that Thread took to execute all the multiplications.

MultSequencial.c - Recives the path of the files that contains matrix 1 and 2 made by Auxiliar.c and when run it will calculate everything in one process/thread or in other words, in only one flow.

MultProcess.c - Recives the path of the files that contains matrix 1 and 2 made by Auxiliar.c and a number P, all this by the command line. P is the number of process it will be created to every process calculate (matrix1 rows * matrix2 columns/ P) cells, so it will be run in P flows or acctually in the number of process the scheduling of the OS choose to run.

MultThreads.c - Recives Recives the path of the files that contains matrix 1 and 2 made by Auxiliar.c and a number P, all this by the command line. P is the number of Threads it will be created to every Thread calculate (matrix1 rows * matrix2 columns/ P) cells, so it will be run in P flows or acctually in the number of threads the scheduling of the OS choose to run.

# Warning
Threads and Process depends on something from the operational system called scheduling, the whole program and the test were developed on linux, so I'm not sure if the results are going to be the same on others OS, so I recommend to run it in Ubuntu-linux.

# How to run it?

Open each folder as a single project in your IDE or terminal

- Auxiliar
1. gcc Auxiliar.c -o Auxiliar
2. ./Auxiliar 100 100 100 100 (max 3200)

- Sequential
1. gcc multSequencial -o multSequencial
2. ./multSequencial matrizResultante.txt

- Process 
1. gcc multProcess.c -o multProcess
2. ./multProcess matriz1.txt matriz2.txt 8

- Thread
1. gcc multThreads.c -o multThreads
2. ./multThreads matriz1.txt matriz2.txt 8


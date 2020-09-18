# MIPS-P.V1


                       _______ _________ _______  _______ 
                      (       )\__   __/(  ____ )(  ____ \
                      | () () |   ) (   | (    )|| (    \/
                      | || || |   | |   | (____)|| (_____ 
                      | |(_)| |   | |   |  _____)(_____  )
                      | |   | |   | |   | (            ) |
                      | )   ( |___) (___| )      /\____) |
                      |/     \|\_______/|/       \_______)
                                                          
         _______  _______  _______ _________ _______  _______ _________
        (  ____ )(  ____ )(  ___  )\__    _/(  ____ \(  ____ \\__   __/
        | (    )|| (    )|| (   ) |   )  (  | (    \/| (    \/   ) (   
        | (____)|| (____)|| |   | |   |  |  | (__    | |         | |   
        |  _____)|     __)| |   | |   |  |  |  __)   | |         | |   
        | (      | (\ (   | |   | |   |  |  | (      | |         | |   
        | )      | ) \ \__| (___) ||\_)  )  | (____/\| (____/\   | |   
        |/       |/   \__/(_______)(____/   (_______/(_______/   )_(                                                                                            

TL;DR: Make sure to subtract "1" (stored in RF[6]) from RF[0], and everything else should be straight forward.
_____________________________________________________________________________________
WARNING: File will NOT work as intended if "1" for successive addition in Register 6 (7th slot of the register) is not utilized properly. 
This can be found on line 74 of the program (RF[6] = 1).
_____________________________________________________________________________________
PRE-REQUISITES for the program and base knowledge:
File: Make sure the file is in proper text document format, and that RF[6] is assigned a 
value of 1 (as per line 74 in the "main.c" program code). This 1 is assigned for the purpose of subtraction, and therefore your file should take this into account. 
When the subtraction operand is called, RF[0] should be set equal to RF[0] - RF[6] 
("4 0 0 6" is the command for subtraction (called by "4") and "0 0 6" (used for the operation RF[0] = RF[0] - RF[6]) 
The purpose of the subtraction operand call in the specified case above is for multiplication (as specified below in operations).

When subtraction is called (4, for sub operand), make sure to use RF[6] for subtraction.

We have provided the "test2.in" if you'd like to run the program using the same parameters we utilized (input2.in is displayed below on line 9):

5 0 0 5 3 0 0 0 5 0 0 5 3 0 0 3 1 3 0 0 1 0 0 3 2 2 3 2 4 0 0 6 9 0 0 0 8 0 0 20 3 2 0 2 1 0 0 2 7 0 0 0
_____________________________________________________________________________________
STEPS TO RUN THE PROGRAM:

Step 1.1) Run the program

Step 1.2) Input name of desired test file - when the program is run, it will prompt you to 
"Enter a file name." Then, input the desired file's name 

(ex: if the test file is named "test2.in", input "test2.in").

Step 2.1) When the program prompts, input a value for instruction "sio1." Enter a number for either addition or multiplication.

Step 2.2) When the program prompts again, input a second value for "sio1" again. Specify a number for the operation of addition or multiplication.

HOW TO READ OUTPUT (CONSOLE DISPLAY):

SAMPLE OUTPUT: 

/*Storing Word in Memory (sw   2 0 2)*/ 
 DM[2] = RF[2] = 10

PC = 40 | RF = [0, 0, 10, 5, 0, 0, 1, 0] | DM = [5, 0, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] | 
IFID = [3, 2, 0, 2] | IDEX = [3, 10, 0, 0] | EXDM = [3, 10, 0, 0] | DMWB = [3, 10, 0, 0] 
_____________________________________________________________________________________
DESCRIPTION OF EACH LINE OF SAMPLE OUTPUT ABOVE:

/*Storing Word in Memory (sw   2 0 2)*/ <-- DESCRIBES OPERAND CALL (also includes the registers/address/input specifiers 
(2 0 2 --> RF [2] = 10, DM[2] = RF[2], therefore DM[2] = 10)).

DM[2] = RF[2] = 10 <-- VISUALIZATION OF OPERATION OCCURING

PC = 40 | RF = [0, 0, 10, 5, 0, 0, 1, 0] | DM = [5, 0, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] | 
IFID = [3, 2, 0, 2] | IDEX = [3, 10, 0, 0] | EXDM = [3, 10, 0, 0] | DMWB = [3, 10, 0, 0] <-- VISUALIZATION OF VALUES STORED IN EACH ARRAY/BUFFER 
(PC, RF, DM, IFID, IDEX, EXDM, DMWB)
_____________________________________________________________________________________

OPERATIONS:

LW: Load word here is implemented by copying a value from specified address of Data Memory to a specified Register. 

Ex. (RF[0] = DM[0]) -> RF = [X, 0, 0...], then DM = [X, 0, 0...]
_____________________________________________________________________________________
ADD: Addition here is implemented by adding the values between two specified registers and 
setting a specified register to the value of the two added registers.

Ex. RF[0] = RF [1] + RF[2] (3 = 2 + 1) -> RF == [3, 2, 1...]
_____________________________________________________________________________________
SW: Store word here is implemented by copying a value from a specified Register to a specified address of Data Memory.

Ex. (DM[2] = RF[0]) -> DM = [0, 0, X...], then RF = [X, 0, 0...]
_____________________________________________________________________________________
SUB: Subtraction here is implemented by subtracting the values between two specified 
registers and setting a specified register to the value of the two subtracted registers.

NOTE: When subtraction is called (4, for sub operand), make sure to use RF[6] for subtraction.

Ex. RF[0] = RF [1] - RF[2] (1 = 2 - 1) -> RF == [1, 2, 1...]
_____________________________________________________________________________________
SIO1: Input here is implemented by taking input from the keyboard and storing the value in RF[0].

Ex. scanf("%d", &RF[0]); RF[0] = 5 (5 is input received from keyboard, therefore 5 is now 
stored in RF[0]).
_____________________________________________________________________________________
SIO2: Ouput here is implemented by displaying what is stored in RF[0] to the screen.

Ex. RF[0] = 5; printf("%d", RF[0]) (5 was the input received from the keyboard, therefore 5 
is what is printed to the screen).
_____________________________________________________________________________________
SIO3: Halt here is implemented by telling the program to stop executing when the halt function is called.

Ex. if(IR.opcode == 7) break; (if 7 is value received for IR.opcode, the program is told to 
break out of the inputted file, and to close the running instance of the file being read).
_____________________________________________________________________________________
JMP: Jump here is implemented by jumping to a specified address according to the Program 
Counter, and the Program Counter is assigned to the value of the specified instruction.

Ex. PC = IR.rz; IR.rz == 20; therefore, PC == 20; (it uses BEQZ (described below) to skip 
the jump, when necessary).
_____________________________________________________________________________________
BEQZ: Skip here in this program specifically is used for multiplication 
(the number of successive additions is stored in RF[0]). 
Skip also enacts a counting measure for how many times to skip (adding 4 to the Program Counter). 

Skip is implemented by first checking to see if RF[0] == 0. If it passes this check (i.e. RF
[0] == 0)  (one of your inputs should be stored in RF[0]).

Ex. (for Multiplication) Input 1 = 3; 3 -> RF[0], therefore RF[0] = 3; Input 2 = 5; 5 -> RF
[X], where X is equal to a valid register, therefore RF[X] = 5. 
When multiplying, the RF[0] allows for successive additions (as explained in BEQZ for multiplication). 

RF[0] = 3 , 5 -> RF[X]; 3 - 1 = RF[0] -> RF[0] = 2; 5 + 0 = 5; 2 - 1 -> RF[0] = 1;
5 + 5 = 10; 1 - 1 -> RF[0] = 0 -> 5 + 10 = 15; therefore 5 x 3 = 15.
_____________________________________________________________________________________
MLP (Multiplication): Multiplication implementation was specified above on lines 2, 54, and 
56 of the readme.txt. 

Multiplication is implemeneted using a combination of subtraction, jumping (including 
successive additions), and skipping.

Sub -> decrements for successive addition
Add -> adds a specified value for total specified times (Ex. 3 x 5 = 3 added by three, five times)
Jump -> loops 
Beqz -> ends the loops

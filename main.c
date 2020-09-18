/*
Please read the "readme.txt" file to see how to proceed.
*/
#include <stdio.h>

#define MAXIMSIZE 500
#define LW 1
#define ADD 2
#define SW 3
#define SUB 4
#define SIO1 5
#define SIO2 6
#define SIO3 7
#define JMP 8
#define BEQZ 9
#define REGISTERSIZE 8
#define DMSIZE 16

typedef struct Instruction {
  int opcode,rx,ry,rz;
} Instruction;

Instruction IR;

int main(void) {
  //asks user for the filename to be read
  char filename[50];
  printf("Enter a file name\n");
  scanf("%s", filename);
  //opens the selected file
  FILE *ifp = fopen(filename, "r");
  int  DM[DMSIZE] = {0}, RF[REGISTERSIZE] = {0}, i = 0, PC = 0, inputVal, j, MAR1, MAR2, instructMem, IFID[4] = {0}, IDEX[4] = {0}, EXDM[4] = {0}, DMWB[4] = {0}, IM[MAXIMSIZE];
  //opString sets an array to where each of the operations are in order, from "load word" to "beqz"
  char opString[9][5] = {"lw  ", "add ", "sw  ", "sub ", "sio1", "sio2", "sio3", "jmp ", "beqz"};

  printf("Assembling program...\nProgram Assembled.\n");

  while(!feof(ifp)) {
    //set MAR1 equivalent to the Program Counter
    MAR1 = PC;
    //scans for values from opString, and points instruction memory on where to perform the current operation in the file
    fscanf(ifp, "%d %d %d %d", &IM[MAR1], &IM[MAR1+1], &IM[MAR1+2], &IM[MAR1+3]);
    if(IM[MAR1] == LW)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == ADD)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == SW)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == SUB)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == SIO1)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == SIO2) 
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == SIO3) {
      printf(" halt\n");
      break;
    }
    else if (IM[MAR1] == JMP)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);
    else if (IM[MAR1] == BEQZ)
      printf(" %s %d %d %d", opString[IM[MAR1]-1], IM[MAR1+1], IM[MAR1+2], IM[MAR1+3]);

    printf("\n");
    //increment Program Counter by 4
    PC += 4;
  }
  
  //sets Program Counter to 0, and Register 6 to 1
  PC=0;
  RF[6] = 1;

  while(1) {
    //set MAR1 equivalent to the Program Counter
    MAR1 = PC;
    

    IR.opcode = IM[MAR1];
    IR.rx = IM[MAR1+1];
    IR.ry = IM[MAR1+2];
    IR.rz = IM[MAR1+3];

    MAR2 = IR.rz;

    IFID[0] = IM[MAR1];
    IFID[1] = IM[MAR1+1];
    IFID[2] = IM[MAR1+2];
    IFID[3] = IM[MAR1+3];

    IDEX[0] = IM[MAR1];
    IDEX[1] = 0;
    IDEX[2] = 0;
    IDEX[3] = 0;

    EXDM[0] = IM[MAR1];
    EXDM[1] = 0;
    EXDM[2] = 0;
    EXDM[3] = 0;

    DMWB[0] = IM[MAR1];
    DMWB[1] = 0;
    DMWB[2] = 0;
    DMWB[3] = 0;

    /* LOAD WORD */
    if(IR.opcode == LW) {
      printf("\n/*Loading word onto register (%s %d %d %d)*/\n RF[%d] = DM[%d] = %d\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, IR.rx, MAR2, DM[MAR2]);

      //Load data memory onto register zero
      RF[IR.rx] = DM[MAR2];

      DMWB[3] = RF[IR.rx];
    }
    /* ADD */
    else if (IR.opcode == ADD) {
      printf("\n/*Adding (%s %d %d %d)*/\n RF[%d] = RF[%d] + RF[%d] (%d = %d + %d)\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, IR.rx, IR.ry, IR.rz, RF[IR.ry] + RF[IR.rz], RF[IR.ry], RF[IR.rz]);

      //add register y and register z and store in register x
      RF[IR.rx] = RF[IR.ry] + RF[IR.rz];

      IDEX[1] = RF[IR.rx];
      EXDM[1] = RF[IR.rx];
      DMWB[1] = RF[IR.rx];

    }
    /* STORE WORD */
    else if (IR.opcode == SW) {

      printf("\n/*Storing Word in Memory (%s %d %d %d)*/\n DM[%d] = RF[%d] = %d\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, MAR2, IR.rx, RF[IR.rx]);

      //1 = IDEX, 2 = EXDM, and 3 = DMWB
      // INSTRUCTION DECODE AND EXECUTE = IDEX
      // EXECUTE AND DATA MEMORY ACCESS = EXDM
      // DATA MEMORY ACCESS AND WRITE BACK = DMWB
      DM[MAR2] = RF[IR.rx];

      IDEX[1] = DM[MAR2];
      EXDM[1] = DM[MAR2];
      DMWB[1] = DM[MAR2];

    }
    /* SUBTRACT */
    else if (IR.opcode == SUB) {
      printf("\n/*Subtracting (%s %d %d %d)*/\n RF[%d] = RF[%d] - RF[%d] (%d = %d - %d)\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, IR.rx, IR.ry, IR.rz, RF[IR.ry] - RF[IR.rz], RF[IR.ry], RF[IR.rz]);

      //subtract register z from register y and store in register x
      RF[IR.rx] = RF[IR.ry] - RF[IR.rz];

      IDEX[1] = RF[IR.rx];
      EXDM[1] = RF[IR.rx];
      DMWB[1] = RF[IR.rx];

    }
     /* INPUT */
    else if (IR.opcode == SIO1) {
      printf("\n/*input value (%s %d %d %d)*/\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz);

      //get input from keyboard and store in register 0
      scanf("%d", &RF[IR.rx]); 

      EXDM[3] = RF[0];
      DMWB[3] = RF[0];
    }
   /* OUTPUT */
    else if (IR.opcode == SIO2) {
      printf("\n/*outputting R0 to screen (%s %d %d %d)*/\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz);

      //display register 0 to screen
      printf("R[0] = %d\n\n", RF[IR.rx]);

      IDEX[1] = RF[0];
      EXDM[1] = RF[0];
      DMWB[1] = RF[0];
    }
    /* HALT */
    else if (IR.opcode == SIO3) {
      printf("\nProgram complete.\n");
      break;    
    }
    /* JUMP */
    else if (IR.opcode == JMP) {
      printf("\n/*Jumping (%s %d %d %d)*/\n Jumping to: %d\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, IR.rz);
      
      PC = IR.rz;
    //(just in case)
    //modulus operand here for jump operation (in regards to multiples of 4(vs. non-multiples))
      int mod = PC%4;
      PC-=mod;

      IDEX[1] = IR.rz;
      EXDM[1] = IR.rz;
      DMWB[1] = IR.rz;

    }
  /* SKIP */
    else if (IR.opcode == BEQZ) {
      printf("\n/*Skip if 0(%s %d %d %d)*/\n RF[0] = %d\n", opString[IR.opcode-1], IR.rx, IR.ry, IR.rz, RF[0]);
      
      //if register 0 == 0 skip
      if(RF[0] <= 0){
        printf("Skipping...\n");
         PC += 4;
      }

      IDEX[1] = RF[0];
      EXDM[1] = RF[0];
      DMWB[1] = RF[0];

    }

    //print the data after each command
    printf("\nPC = %d | RF = [", PC);
    for (j = 0; j < REGISTERSIZE; j++) 
    {
      if (j < REGISTERSIZE - 1)
        printf("%d, ", RF[j]);
      else
        printf("%d", RF[j]);
    }

    printf("] | DM = [");
    for (j = 0; j < DMSIZE; j++) {
      if (j < DMSIZE - 1)
        printf("%d, ", DM[j]);
      else
        printf("%d", DM[j]);
    }

    printf("] | IFID = [");
    for(j = 0; j < 4; j++) {
      if (j < 3)
        printf("%d, ", IFID[j]);
      else
        printf("%d", IFID[j]);
    }

    printf("] | IDEX = [");
    for(j = 0; j < 4; j++) {
      if (j < 3)
        printf("%d, ", IDEX[j]);
      else
        printf("%d", IDEX[j]);
    }

    printf("] | EXDM = [");
    for(j = 0; j < 4; j++) {
      if (j < 3)
        printf("%d, ", EXDM[j]);
      else
        printf("%d", EXDM[j]);
    }

    printf("] | DMWB = [");
    for(j = 0; j < 4; j++) {
      if (j < 3)
        printf("%d, ", DMWB[j]);
      else
        printf("%d]", DMWB[j]);
    }

    printf("\n");
    PC += 4;
  }

  //close the file once the halt operation is called
  fclose(ifp);
  return 0;
}
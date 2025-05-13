#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Memory_block[100][4];
char Instruction_register[4];
char General_purpose_register[4];
int Instruction_counter = 0;
int Toggle_register = 0;
int System_interrupt = 0;
int currentLine = 0;
int flag = 0;

// GD: Get Data from input file
void GD() {
    FILE *fp = fopen("input.txt", "r");
    fseek(fp, currentLine, SEEK_SET);
    char str[100];
    fgets(str, sizeof(str), fp);

    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    int col = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\n') continue;
        Memory_block[row][col++] = str[i];
        if (col == 4) { row++; col = 0; }
    }
    currentLine = ftell(fp);
    fclose(fp);
}

// PD: Put Data to output file
void PD() {
    FILE *fp = fopen("output.txt", "a");
    if (flag++) fprintf(fp, "\n");

    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 4; j++)
            if (Memory_block[row + i][j] != '_')
                fputc(Memory_block[row + i][j], fp);

    fclose(fp);
}

// H: Halt
void H() {
    FILE *fp = fopen("output.txt", "a");
    fprintf(fp, "\n\n");
    fclose(fp);
}

// LR: Load Register
void LR() {
    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    for (int i = 0; i < 4; i++) General_purpose_register[i] = Memory_block[row][i];
}

// SR: Store Register
void SR() {
    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    for (int i = 0; i < 4; i++) Memory_block[row][i] = General_purpose_register[i];
}

// CR: Compare Registers
void CR() {
    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    Toggle_register = 1;
    for (int i = 0; i < 4; i++) {
        if (General_purpose_register[i] != Memory_block[row][i]) {
            Toggle_register = 0;
            break;
        }
    }
}

// BT: Branch if Toggle
void BT() {
    if (Toggle_register)
        Instruction_counter = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
}

// Instruction Execution Loop
void EXECUTE_USER_PROGRAM() {
    while (1) {
        for (int i = 0; i < 4; i++)
            Instruction_register[i] = Memory_block[Instruction_counter][i];
        Instruction_counter++;

        if (Instruction_register[0] == 'G' && Instruction_register[1] == 'D') GD();
        else if (Instruction_register[0] == 'P' && Instruction_register[1] == 'D') PD();
        else if (Instruction_register[0] == 'H') { H(); break; }
        else if (Instruction_register[0] == 'L' && Instruction_register[1] == 'R') LR();
        else if (Instruction_register[0] == 'S' && Instruction_register[1] == 'R') SR();
        else if (Instruction_register[0] == 'C' && Instruction_register[1] == 'R') CR();
        else if (Instruction_register[0] == 'B' && Instruction_register[1] == 'T') BT();
    }

    printf("Execution complete.\n");
}
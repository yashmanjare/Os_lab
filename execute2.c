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

// Initialize memory and registers
void INIT() {
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
            Memory_block[i][j] = ' ';
    for (int i = 0; i < 4; i++) {
        Instruction_register[i] = ' ';
        General_purpose_register[i] = ' ';
    }
    Instruction_counter = 0;
    Toggle_register = 0;
    System_interrupt = 0;
    currentLine = 0;
    flag = 0;
}

// Print memory for debugging
void print_memory_block() {
    printf("\nMemory Block:\n\n");
    for (int i = 0; i < 100; i++) {
        printf("%02d  ", i);
        for (int j = 0; j < 4; j++) {
            printf("|%c", Memory_block[i][j]);
        }
        printf("|\n");
    }
}

// === Execution Functions ===

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

void H() {
    FILE *fp = fopen("output.txt", "a");
    fprintf(fp, "\n\n");
    fclose(fp);
    printf("Execution halted.\n");
}

void LR() {
    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    for (int i = 0; i < 4; i++) General_purpose_register[i] = Memory_block[row][i];
}

void SR() {
    int row = (Instruction_register[2] - '0') * 10 + (Instruction_register[3] - '0');
    for (int i = 0; i < 4; i++) Memory_block[row][i] = General_purpose_register[i];
}

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
}

// === Loader ===

void Load() {
    FILE *fp = fopen("input.txt", "r");
    char str[100];
    int jobCount = 0;

    if (fp == NULL) {
        printf("Error: input.txt not found.\n");
        exit(1);
    }

    while (fgets(str, 41, fp) != NULL) {
        if (strncmp(str, "$AMJ", 4) == 0) {
            printf("\n$AMJ instruction found - Start of Job #%d\n", jobCount + 1);
            getchar();

            INIT();  // Clear memory before each job
            int row = 0, col = 0;

            while (1) {
                if (fgets(str, sizeof(str), fp) == NULL)
                    break;
                if (strncmp(str, "$DTA", 4) == 0)
                    break;

                for (int i = 0; i < strlen(str); i++) {
                    if (str[i] == ' ' || str[i] == '\n') continue;
                    Memory_block[row][col++] = str[i];
                    if (col == 4) { col = 0; row++; }
                    if (row >= 100) break;
                }
            }

            currentLine = ftell(fp);  // save pointer for GD()
            printf("Job loaded. Starting execution...\n");
            EXECUTE_USER_PROGRAM();
        }

        if (strncmp(str, "$END", 4) == 0) {
            jobCount++;
            print_memory_block();
            printf("\nEnd of Job #%d\n", jobCount);
            printf("Press Enter to continue...\n");
            getchar();
        }
    }

    fclose(fp);
}

// === Main ===

int main() {
    printf("==== OS Phase 1: Loader + Execution ====\n");
    printf("Reading jobs from 'input.txt'\n");

    Load();

    printf("\nAll jobs processed. Output written to output.txt\n");
    return 0;
}
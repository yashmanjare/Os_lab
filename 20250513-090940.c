#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables and declarations
char Memory_block[100][4];
int currentLine;

// Function to initialize memory
void INIT(){
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 4; j++){
            Memory_block[i][j] = ' ';
        }
    }
    currentLine = 0;
}

// Function to print the memory block
void print_memory_block(){
    printf("\nMemory Block:\n\n");
    for (int i = 0; i < 100; i++){
        printf("%02d  ", i);
        for (int j = 0; j < 4; j++){
            printf("|%c", Memory_block[i][j]);
        }
        printf("|\n");
    }
}

// Load function to read from input file and populate memory
void Load(){
    FILE *fp = fopen("input.txt", "r");
    char str[100];
    int jobCount = 0;

    if (fp == NULL){
        printf("Error: input.txt not found.\n");
        exit(1);
    }

    while (fgets(str, 41, fp) != NULL){
        if (strncmp(str, "$AMJ", 4) == 0){
            printf("\n$AMJ instruction found - Start of job\n");
            getchar();  // pause for user input

            int row = 0, col = 0;

            while (1){
                if (fgets(str, sizeof(str), fp) == NULL)
                    break;

                if (strncmp(str, "$DTA", 4) == 0)
                    break;

                for (int i = 0; i < strlen(str); i++){
                    if (str[i] == ' ' || str[i] == '\n') continue;

                    Memory_block[row][col] = str[i];
                    col++;

                    if (col == 4){
                        col = 0;
                        row++;
                        if (row >= 100) break;  // prevent overflow
                    }
                }
            }

            currentLine = ftell(fp);  // save current position
            printf("Job loaded into memory.\n");
        }

        if (strncmp(str, "$END", 4) == 0){
            jobCount++;
            print_memory_block();
            printf("\nEnd of Job #%d\n", jobCount);
            printf("Press Enter to load next job...\n");
            getchar();
            INIT();  // reset memory
        }
    }

    fclose(fp);
}

// Main function
int main(){
    printf("==== OS Phase 1: Program Loader ====\n");
    printf("Reading and loading jobs from 'input.txt'\n");

    INIT();     // initialize memory
    Load();     // load input into memory

    printf("\nAll jobs processed.\n");
    return 0;
}
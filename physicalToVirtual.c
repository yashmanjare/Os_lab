#include <stdio.h> 
 
int main() { 
    int n = 4; // number of pages 
    int page_table[] = {2, 5, 1, 3}; // page table mapping page number to frame number 
    int page_size = 10; 
    int logical_addr; 
 
    // Accept logical address 
    printf("Enter logical address: "); 
    scanf("%d", &logical_addr); 
 
    // Step 3: Find out page number and offset 
    int page_num = logical_addr / page_size; 
    if (page_num >= n) { 
        printf("Invalid logical address\n"); 
        return 1; 
    } 
 
    int offset = logical_addr % page_size; 
 
    // Step 4: Find out physical address 
    int frame_num = page_table[page_num]; 
    int physical_addr = frame_num * page_size + offset; 
 
    // Step 5: Display data 
    printf("Logical Address: %d\n", logical_addr); 
printf("Page Number: %d\n", page_num); 
printf("Offset: %d\n", offset); 
printf("Frame Number: %d\n", frame_num); 
printf("Physical Address: %d\n", physical_addr); 
return 0; 
}
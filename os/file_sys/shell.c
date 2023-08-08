#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void) {
    while (1) { 
        printf("%s", prompt); 
        getline(&input_buff_ptr, &input_buff_n, stdin); 
        printf("You Entered : %s", input_buff_ptr); 

        free(input_buff_ptr); 
        input_buff_ptr = NULL; 
    } 
  	return 0;
}

/* 
TODO: 
* "exit" - quit shell 
*/

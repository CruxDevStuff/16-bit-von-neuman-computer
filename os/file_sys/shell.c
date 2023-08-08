#include <stdio.h>
#include "shell.h"

char name[20] = "Hello World boissss\n"; 

int main(void) {
    printf("%s", name); 
  	return 0;
}

/* 
TODO: 
* open_disk - create a file with the specified size 
* read_block
* write_block
* sync_disk 
*/

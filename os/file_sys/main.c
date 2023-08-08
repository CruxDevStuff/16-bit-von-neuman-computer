#include <unistd.h>
#include <sys/syscall.h>

int main(void) {
	// initgroups(); 
  	syscall(SYS_write, 1, "hello, world!\n", 14);
  	return 0;
}

/* 
TODO: 
* open_disk - create a file with the specified size 
* read_block
* write_block
* sync_disk 
*/

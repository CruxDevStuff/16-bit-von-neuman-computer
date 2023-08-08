.global _start		// Provide program starting address to linker
.align 2			// Make sure everything is aligned properly

// Setup the parameters to print hello world
// and then call the Kernel to do it.
_start: mov	X0, #1		// 1 = StdOut
	adr	X1, helloworld 	// string to print
	mov	X2, #13	    	// length of our string
	mov	X16, #4		// Unix write system call
	svc 	#0  // invoke sys call 

// Setup the parameters to exit the program
// and then call the kernel to do it.
	mov     X0, #0		// Use 0 return code
	mov     X16, #1		// System call number 1 terminates this program
	svc     #0  // invoke sys call 

helloworld:      .ascii  "Hello World!\n"

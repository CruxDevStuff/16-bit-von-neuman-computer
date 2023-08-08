lib = ../
CC = clang
CFLAGS = -g -Wall -I$(lib) 
DEPS = shell.h
OBJ = shell.o 
TARGET = $@

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJ) shell
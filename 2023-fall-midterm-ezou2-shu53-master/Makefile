
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -O0

# Links together files needed to create executable
puzzle: puzzle.o puzzle_funcs.o ppm_io.o
	$(CC) -o puzzle puzzle.o puzzle_funcs.o ppm_io.o

# Compiles mainFile.c to create mainFile.o
# Note that we list functions.h here as a file that
# main_file.c depends on, since main_file.c #includes it
puzzle.o: puzzle.c puzzle.h
	$(CC) $(CFLAGS) -c puzzle.c

# Compiles functions.c to create functions.o
# Note that we list functions.h here as a file that
# functions.c depends on, since functions.c #includes it
puzzle_funcs.o: puzzle_funcs.c puzzle.h 
	$(CC) $(CFLAGS) -c puzzle_funcs.c

# Compiles ppm_io.c to create ppm_io.o
# Note that we list ppm_io.h here as a file that
# ppm_io.c depends on, since ppm_io.c #includes it
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c
	

# test
# Links together files needed to create executable
test: puzzle_funcs.o puzzle_tests.o ppm_io.o
	$(CC) -o test puzzle_funcs.o puzzle_tests.o ppm_io.o

puzzle_tests.o: puzzle_tests.c puzzle.h
	$(CC) $(CFLAGS) -c puzzle_tests.c

# Removes all object files and the executable named main,
# so we can start fresh
clean:
	rm -f *.o puzzle test

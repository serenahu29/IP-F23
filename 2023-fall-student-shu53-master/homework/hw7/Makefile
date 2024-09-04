# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# target to create the DataLoopTest executable here
DataLoopTest: DataLoopTest.o DataLoop.o
	$(CC) -o DataLoopTest DataLoopTest.o DataLoop.o 

# Compiles DataLoopTest.cpp into an object file
DataLoopTest.o: DataLoopTest.cpp
	$(CC) $(CFLAGS) -c DataLoopTest.cpp

# Compiles DataLoop.cpp into an object file
DataLoop.o: DataLoop.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoop.cpp


# target to create the TDataLoopTest executable here
TDataLoopTest: TDataLoopTest.o
	$(CC) -o TDataLoopTest TDataLoopTest.o

# Compiles TDataLoopTest.cpp into an object file
TDataLoopTest.o: TDataLoopTest.cpp TDataLoop.h TDataLoop.inc
	$(CC) $(CFLAGS) -c TDataLoopTest.cpp
	
# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o DataLoopTest TDataLoopTest
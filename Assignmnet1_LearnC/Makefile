# Makefile / Assignment1 - Learn C
#
# ZW / CS5600 / Northeastern University
# Fall 2025 / Sep 8, 2025
#
# This Makefile compiles the Learn C assignment:
# - Builds the executable CS5600.LearnC
# - Compiles WangZ.CS5600.LearnC.c and mpg2km.c
# - Provides a 'clean' target to remove object files and executable


# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

# Name of the executable
TARGET = CS5600.LearnC

# Object files
OBJS = WangZ.CS5600.LearnC.o mpg2km.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main source file
WangZ.CS5600.LearnC.o: WangZ.CS5600.LearnC.c mpg2km.h
	$(CC) $(CFLAGS) -c WangZ.CS5600.LearnC.c

# Compile functions source file
mpg2km.o: mpg2km.c mpg2km.h
	$(CC) $(CFLAGS) -c mpg2km.c

# Remove executable and object files
clean:
	rm -f $(TARGET) *.o

# Makefile for genRand-wang.c / Assignment 2 - Random Number Generation
# ZW / Northeastern University
# 9/18/2025

CC = gcc
CFLAGS = -Wall -O2

TARGET = genRand
SRC = genRand-wang.C

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

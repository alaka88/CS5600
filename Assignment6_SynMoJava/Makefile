# Makefile for Assignment 6 - Synchronization with Monitors
# ZW
# Description: Compile and run the Java multi-threaded BoundedBuffer assignment

# Java compiler
JAVAC = javac

# Java runtime
JAVA = java

# Java source files
SOURCES = BoundedBuffer.java ProducerThread.java Main.java

# Main class
MAIN = Main

# Default target: always compile
all: clean compile

# Compile Java source files
compile:
	$(JAVAC) $(SOURCES)

# Run the program
run: all
	$(JAVA) $(MAIN)

# Clean compiled class files
clean:
	rm -f *.class

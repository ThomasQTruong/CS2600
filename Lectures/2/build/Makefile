# By Thomas Truong
# Quickly compiles and links every .c file in the
# src folder, and places them into the bin folder.

# Directory paths.
SRC = ../src/
BIN = ../bin/

# Every object file needed for linking.
OBJECTS = Lecture.o
# The path of every object file.
PATHS = $(foreach path, $(OBJECTS), $(BIN)$(path))

# Function names to run.
all: main

# Functions.
main: $(PATHS)
	g++ -o $(BIN)$@ $^

# Compile .c files to .o files.
$(BIN)%.o: $(SRC)%.c
	g++ -c -o $@ $<

# make run.
run:
	make clean
	make
	$(BIN)main

# make clean.
clean:
	rm -f $(BIN)*

# By Thomas Truong
# Quickly compiles and links every .c file in the
# src folder, and places them into the bin folder.

# Directory paths.
SRC = ../src/
BIN = ../bin/
# Output file name, default: main -> (main.c).
OUTPUT_NAME = main

# Every object file needed for linking.
OBJECTS = tee.o
# The path of every object file.
PATHS = $(foreach path, $(OBJECTS), $(BIN)$(path))

# Function names to run.
all: $(OUTPUT_NAME)

# Functions.
$(OUTPUT_NAME): $(PATHS)
	g++ -o $(BIN)$@ $^

# Compile .c files to .o files.
$(BIN)%.o: $(SRC)%.c
	g++ -c -o $@ $<

# make run.
run:
	make clean
	make
	$(BIN)$(OUTPUT_NAME)

# make clean.
clean:
	rm -f $(BIN)*

# @author: Telmen Enkhtuvshin
# Makefile helper to manage compilation of Round Robin & SJF Files

# Compiler name
CC = gcc

# Define source files
SRC = RR_inital.c SJF_inital.c

# Define object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Define executables
EXEC1 = RR
EXEC2 = SJF

# Default target (build both executables)
all: $(EXEC1) $(EXEC2)

# Compile first executable
$(EXEC1): RR_inital.o
	$(CC) RR_inital.o -o $(EXEC1)

# Compile second executable
$(EXEC2): SJF_inital.o
	$(CC) SJF_inital.o -o $(EXEC2)

# Compile object files
%.o: %.c
	$(CC) -c $< -o $@

# Run both executables
run: $(EXEC1) $(EXEC2)
	./$(EXEC1) & ./$(EXEC2)

# Clean compiled files
clean:
	rm -f $(OBJ) $(EXEC1) $(EXEC2)
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = main.c TADs/system/system.c TADs/system/auxiliares.c TADs/time/consultar_time.c TADs/partida/consultar_partida.c TADs/classificacao/imprimir_classificacao.c TADs/time/time.c TADs/partida/partida.c TADs/partida/atualizar_partida.c TADs/partida/inserir_partida.c TADs/partida/remover_partida.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = programa

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
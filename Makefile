CC = gcc

SRC = $(wildcard *.c)
TARGET = MemoryManager

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^

clean: $(EXE)
	$(RM) $(TARGET)

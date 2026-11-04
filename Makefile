CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude

TARGET = build/passagesystem
SRC = src/main.c src/passerkort.c

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build/*

.PHONY: all clean
CC        := gcc
CFLAGS    := -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude

BUILD_DIR := build
TARGET    := $(BUILD_DIR)/passagesystem

SRCS      := $(wildcard src/*.c)
OBJS      := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
SRC_DIR := src
BUILD_DIR := build
TARGET := main

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

STD ?= c17
SAN ?= -fsanitize=address,undefined -fno-omit-frame-pointer
WARN := -Wall -Wextra -Wpedantic -Wshadow

CPPFLAGS := -D_POSIX_C_SOURCE=200809L
CFLAGS := -std=$(STD) $(WARN) -g -O0 $(SAN) -MMD -MP
LDFLAGS := $(SAN)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
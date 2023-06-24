SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
OBJ_DIR := obj
TST_DIR := test

OBJECTS := $(addprefix $(OBJ_DIR)/,cpu.o op.o)
TEST_OBJ := $(OBJ_DIR)/test.o

CC := gcc
CFLAGS := -g -MMD -MP
CLIBS := -lSDL2 -pthread

.PHONY: all clean test

all: main

main: $(BIN_DIR)/main

test: $(BIN_DIR)/test

$(BIN_DIR)/main: $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

$(BIN_DIR)/test: $(TEST_OBJ) $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I$(INC_DIR) $(CFLAGS) -c $<  -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

runtest:
	./bin/test

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)


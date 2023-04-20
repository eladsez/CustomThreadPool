SRC_DIR=./src
OBJ_DIR=./build
CC=gcc
LD_FLAGS=-L$(OBJ_DIR) -l
ENC_LIB=./build/libCodec.so

.PHONY: clean all

all: Coder

encoder: $(OBJ_DIR)/basic_main.o
	$(CC) $(OBJ_DIR)/basic_main.o $(ENC_LIB) -o encoder

tester: $(OBJ_DIR)/stdin_main.o
	$(CC) $(OBJ_DIR)/stdin_main.o $(ENC_LIB) -o tester

Coder: $(OBJ_DIR)/coder.o
	$(CC) $(OBJ_DIR)/coder.o $(ENC_LIB) -o Coder

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG) -c -o $@ $<

clean:
	rm -rIf encoder tester $(OBJ_DIR)/*.o Coder

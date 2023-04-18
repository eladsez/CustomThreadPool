

SRC_DIR=./src
OBJ_DIR=./build
CC=gcc
LD_FLAGS=-L$(OBJ_DIR) -l
ENC_LIB=libCodec.so

all: encoder tester

encoder: $(OBJ_DIR)/basic_main.o
	$(CC) $(OBJ_DIR)/basic_main.o $(LD_FLAGS):$(ENC_LIB) -o encoder

tester: $(OBJ_DIR)/stdin_main.o
	$(CC) $(OBJ_DIR)/stdin_main.o $(LD_FLAGS):$(ENC_LIB) -o tester

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG) -c -o $@ $<

clean:
	-rm encoder tester $(OBJ_DIR)/*.o
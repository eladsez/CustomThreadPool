SRC_DIR=./src
OBJ_DIR=./build
CC=gcc
LD_FLAGS=-L$(OBJ_DIR) -l
ENC_LIB=./build/libCodec.so
AR=ar
AR_FLAGS=rcs

.PHONY: clean all

all: Coder

Coder: $(OBJ_DIR)/coder.o $(OBJ_DIR)/thread_pool.a $(OBJ_DIR)/safe_inc.a
	$(CC) $(OBJ_DIR)/coder.o $(ENC_LIB) -o Coder -lpthread $(OBJ_DIR)/safe_inc.a $(OBJ_DIR)/thread_pool.a

$(OBJ_DIR)/thread_pool.a: $(OBJ_DIR)/thread_pool.o $(OBJ_DIR)/safe_inc.a
	$(AR) $(AR_FLAGS) $@ $^ -lpthread

$(OBJ_DIR)/safe_inc.a: $(OBJ_DIR)/safe_inc.o
	$(AR) $(AR_FLAGS) $@ $^ -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG) -c -o $@ $<

clean:
	rm -rIf encoder tester $(OBJ_DIR)/*.o Coder $(OBJ_DIR)/*.a

INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./lib

CC:=gcc
CFLAGS:=-I$(INC_DIR) -lm

DEPS:=		boson_string.h

all: io_obj

io_obj: boson_string

boson_string: $(SRC_DIR)/boson_string.c $(INC_DIR)/boson_string.h
	$(CC) -c -o $(OBJ_DIR)/boson_string.o $(SRC_DIR)/boson_string.c $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o
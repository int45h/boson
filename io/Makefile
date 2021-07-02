INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./lib

CC:=gcc
CFLAGS:=-I$(INC_DIR) -lm

DEPS:=		boson_io.h

all: io_obj

io_obj: boson_io

boson_io: $(SRC_DIR)/boson_io.c $(INC_DIR)/boson_io.h
	$(CC) -c -o $(OBJ_DIR)/boson_io.o $(SRC_DIR)/boson_io.c $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o
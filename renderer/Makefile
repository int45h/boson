INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./lib

CC:=gcc
CFLAGS:=-I$(INC_DIR) -lm

DEPS:=		boson_window.h

all: render_obj

render_obj: boson_window boson_render_objects

boson_window: $(SRC_DIR)/boson_window.c $(INC_DIR)/boson_window.h
	$(CC) -c -o $(OBJ_DIR)/boson_window.o $(SRC_DIR)/boson_window.c $(CFLAGS)

boson_render_objects: $(SRC_DIR)/boson_render_objects.c $(INC_DIR)/boson_render_objects.h
	$(CC) -c -o $(OBJ_DIR)/boson_render_objects.o $(SRC_DIR)/boson_render_objects.c $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o
INC_DIR=./glm/include
SRC_DIR=./glm/src
OBJ_DIR=./glm/lib

CC:=gcc
CFLAGS:=-I$(INC_DIR) -lm

DEPS:=		common.h, mat.h, vec.h, quat.h

all: math_obj

math_obj: mat4f mat3f mat2f quatf vec4f vec3f vec2f

mat4f: $(SRC_DIR)/mat4f.c $(INC_DIR)/mat4f.h
	$(CC) -c -o $(OBJ_DIR)/mat4f.o $(SRC_DIR)/mat4f.c $(CFLAGS)

mat3f: $(SRC_DIR)/mat3f.c $(INC_DIR)/mat3f.h
	$(CC) -c -o $(OBJ_DIR)/mat3f.o $(SRC_DIR)/mat3f.c $(CFLAGS)

mat2f: $(SRC_DIR)/mat2f.c $(INC_DIR)/mat2f.h
	$(CC) -c -o $(OBJ_DIR)/mat2f.o $(SRC_DIR)/mat2f.c $(CFLAGS)

quatf: $(SRC_DIR)/quatf.c $(INC_DIR)/quatf.h
	$(CC) -c -o $(OBJ_DIR)/quatf.o $(SRC_DIR)/quatf.c $(CFLAGS)

vec4f: $(SRC_DIR)/vec4f.c $(INC_DIR)/vec4f.h
	$(CC) -c -o $(OBJ_DIR)/vec4f.o $(SRC_DIR)/vec4f.c $(CFLAGS)

vec3f: $(SRC_DIR)/vec3f.c $(INC_DIR)/vec3f.h
	$(CC) -c -o $(OBJ_DIR)/vec3f.o $(SRC_DIR)/vec3f.c $(CFLAGS)

vec2f: $(SRC_DIR)/vec2f.c $(INC_DIR)/vec2f.h
	$(CC) -c -o $(OBJ_DIR)/vec2f.o $(SRC_DIR)/vec2f.c $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o
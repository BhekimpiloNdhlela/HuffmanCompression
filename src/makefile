## http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
TARGET = compressor
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall
OBJ_LOC=../obj
LIB_LOC=../lib
TEST_LOC=../tests


.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, $(OBJ_LOC)/%.o, $(wildcard *.c))
HEADERS = $(wildcard $(LIB_LOC)/*.h)

$(OBJ_LOC)/%.o: %.c $(HEADERS)
	mkdir -p $(OBJ_LOC)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(OBJ_LOC)/*.o
	-rm -f $(TARGET)
	-rm -f $(TEST_LOC)/*.txt*

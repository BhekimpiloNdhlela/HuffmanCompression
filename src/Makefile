NAME     = compress

DEBUG    = -ggdb
OPTIMISE = -O0
WARNINGS = -Wall
TARGET   = -m32
CFLAGS   = $(DEBUG) $(OPTIMISE) $(WARNINGS) $(TARGET)

CC       = gcc
RM       = rm -f
COMPILE  = $(CC) $(CFLAGS)

# C main
C_OBJS   = compress.o utils.o huffman.o heap.o

$(NAME): $(C_OBJS)
	$(COMPILE) -o $@ $^

heap.o: heap.c ../lib/heap.h
	$(COMPILE) -c $<

utils.o: utils.c ../lib/utils.h
	$(COMPILE) -c $<

huffman.o: huffman.c ../lib/huffman.h
	$(COMPILE) -c $<

main.o: main.c
	$(COMPILE) -c $<
.PHONY: all clean types

all: $(NAME)

clean:
	$(RM) *.o *.map *.s *.bin *~ .*swp .*swo .*swn
	$(RM) $(NAME)

CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
#SRC += ./xui/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c
INC =-I.
INC +=-I../lib
INC +=-I../lib/tls

LIB =-lm -lpthread
LIB +=-L../lib/tls -ltls

all:
	$(CC) $(INC) -g -Wall $(SRC) $(LIB) -o main
clean:
	rm -f bin/*
	
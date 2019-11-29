CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
#SRC += ./xui/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c
INC =-I.
INC +=-I../lib
INC +=-I../lib/sdk
INC +=-I../lib/gui
INC +=-I../lib/tls

LIB =-lm -lpthread
LIB +=-L../lib/sdk -lsdk
LIB +=-L../lib/gui -lgui
LIB +=-L../lib/tls -ltls

all:
	$(CC) $(INC) -g -Wall $(SRC) $(LIB) -o master
clean:
	rm -f bin/*
	
	
	#-lpthread
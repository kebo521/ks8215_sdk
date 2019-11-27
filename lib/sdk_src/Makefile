CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
#SRC += ./xui/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c
INC =-I.
INC +=-I../

LIB =-lm -lpthread

all:
	$(CC) $(INC) -g -Wall $(SRC) $(LIB) -shared -o ../sdk/libsdk.so
clean:
	rm -f bin/*
	
	
	#-lpthread
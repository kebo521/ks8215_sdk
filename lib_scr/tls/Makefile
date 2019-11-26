CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
SRC += ./library/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c
#-L. -lmbedtls
 
all:
	$(CC) -I. -g -Wall $(SRC) -shared -o libtls.so
clean:
	rm -f bin/*
	
	
	#-lpthread
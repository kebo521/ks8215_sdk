CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
SRC += ./library/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c
#-L. -lmbedtls
 
all:
	$(CC) -I. -I../ -g -Wall $(SRC) -fPIC -shared -o ../tls/libtls.so
clean:
	rm -f bin/*
	
	
	#-lpthread
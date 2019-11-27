CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := *.c
#SRC += ./xui/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c

 
all:
	$(CC) -g -Wall $(SRC) -lm -lpthread -shared -o ../gui/libgui.so
clean:
	rm -f bin/*
	
	
	#-lpthread
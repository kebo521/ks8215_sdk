CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += -g 
CFLAGS  += -Wall 
SRC := xui_fb.c xui_ui.c xui_font.c xui_gui.c ui_menu.c QR_Encode.c language.c key_hard.c EvenMsg.c
#SRC += ./xui/*.c
#SRC += ./bit/bitmap.c ./bit/linux_fb.c

INC =-I.
INC +=-I../
 
all:
	$(CC) $(INC) -g -Wall $(SRC) -fPIC -lm -lpthread -shared -o ../gui/libgui.so
clean:
	rm -f bin/*
	
	
	#-lpthread
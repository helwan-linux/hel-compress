CC = gcc
CFLAGS = -Wall -O2 -Iinclude `pkg-config --cflags gtk+-3.0`
LDFLAGS = -lz -lbz2 -lzstd -lssl -lcrypto -larchive
GTK_LIBS = `pkg-config --libs gtk+-3.0`

# CLI Objects (بدون gui.o)
CLI_SRC = src/main.c src/compressor.c src/lang_manager.c src/utils.c
CLI_OBJ = $(CLI_SRC:.c=.o)

# GUI Objects (مع gui.c)
GUI_SRC = src/gui.c src/compressor.c src/lang_manager.c src/utils.c
GUI_OBJ = $(GUI_SRC:.c=.o)

all: hel-compress hel-gui

# بناء أداة سطر الأوامر
hel-compress: $(CLI_OBJ)
	$(CC) $(CLI_OBJ) -o $@ $(LDFLAGS)

# بناء الواجهة الرسومية
hel-gui: $(GUI_OBJ)
	$(CC) $(GUI_OBJ) -o $@ $(LDFLAGS) $(GTK_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o hel-compress hel-gui

.PHONY: all clean

CC = gcc
CFLAGS = -Wall -O2 -Iinclude `pkg-config --cflags gtk+-3.0`
LDFLAGS = -lz -lbz2 -lzstd -lssl -lcrypto `pkg-config --libs gtk+-3.0`

SRC = src/main.c src/compressor.c src/lang_manager.c src/utils.c src/gui.c
OBJ = $(SRC:.c=.o)

hel-compress: $(OBJ)
    $(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

clean:
    rm -f $(OBJ) hel-compress

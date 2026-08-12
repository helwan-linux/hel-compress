# Makefile - النسخة المتكاملة للمشروع
CC = gcc
# إضافة -Iinclude لضمان عثور المترجم على ملفات الـ .h داخل مجلد include
CFLAGS = -Wall -O2 -Iinclude `pkg-config --cflags gtk+-3.0`
# ربط المكتبات اللازمة للضغط والتشفير والواجهة الرسومية
LDFLAGS = -lz -lbz2 -lzstd -lssl -lcrypto `pkg-config --libs gtk+-3.0`

# تحديد مسارات ملفات المصدر
SRC = src/main.c src/compressor.c src/lang_manager.c src/utils.c src/gui.c
# تحويل ملفات .c إلى .o
OBJ = $(SRC:.c=.o)

# الهدف الرئيسي: بناء البرنامج التنفيذي
hel-compress: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# قاعدة بناء ملفات الـ .o من الـ .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# تنظيف الملفات المؤقتة
clean:
	rm -f src/*.o hel-compress

.PHONY: all clean

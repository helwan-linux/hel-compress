#include <gtk/gtk.h>
#include "compressor.h"

GtkWidget *progress_bar;
GtkWidget *combo_algo;
GtkWidget *check_encrypt;
GtkWidget *file_chooser;

static CompressionAlgo get_selected_algo() {
    const gchar *algo = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_algo));
    if (g_strcmp0(algo, "gzip") == 0) return ALGO_GZIP;
    if (g_strcmp0(algo, "bzip2") == 0) return ALGO_BZIP2;
    if (g_strcmp0(algo, "zstd") == 0) return ALGO_ZSTD;
    return ALGO_ZLIB;
}

static void on_compress_clicked(GtkWidget *widget, gpointer data) {
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    if (!filename) {
        g_print("لم يتم اختيار ملف.\n");
        return;
    }

    CompressionAlgo algo = get_selected_algo();
    gboolean encrypt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_encrypt));

    int result = compress_file(filename, "output.hc", algo, encrypt);
    if (result == 0) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 1.0);
        g_print("تم ضغط الملف بنجاح إلى output.hc\n");
    } else {
        g_print("فشل عملية الضغط!\n");
    }

    g_free(filename);
}

static void on_decompress_clicked(GtkWidget *widget, gpointer data) {
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    if (!filename) {
        g_print("لم يتم اختيار ملف.\n");
        return;
    }

    CompressionAlgo algo = get_selected_algo();
    gboolean decrypt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_encrypt));

    int result = decompress_file(filename, "result.txt", algo, decrypt);
    if (result == 0) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 1.0);
        g_print("تم فك ضغط الملف بنجاح إلى result.txt\n");
    } else {
        g_print("فشل فك الضغط أو خطأ في مفتاح التشفير!\n");
    }

    g_free(filename);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *button_compress, *button_decompress;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Helwan Compress");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 250);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    file_chooser = gtk_file_chooser_button_new("اختر ملف", GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(grid), file_chooser, 0, 0, 2, 1);

    combo_algo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_algo), "zlib");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_algo), "gzip");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_algo), "bzip2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_algo), "zstd");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_algo), 0);
    gtk_grid_attach(GTK_GRID(grid), combo_algo, 0, 1, 2, 1);

    check_encrypt = gtk_check_button_new_with_label("تفعيل التشفير AES-256 الآمن");
    gtk_grid_attach(GTK_GRID(grid), check_encrypt, 0, 2, 2, 1);

    button_compress = gtk_button_new_with_label("ضغط ملف");
    g_signal_connect(button_compress, "clicked", G_CALLBACK(on_compress_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_compress, 0, 3, 1, 1);

    button_decompress = gtk_button_new_with_label("فك ضغط ملف");
    g_signal_connect(button_decompress, "clicked", G_CALLBACK(on_decompress_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_decompress, 1, 3, 1, 1);

    progress_bar = gtk_progress_bar_new();
    gtk_grid_attach(GTK_GRID(grid), progress_bar, 0, 4, 2, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

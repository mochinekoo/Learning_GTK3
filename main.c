#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

static void on_button_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget* messageDialog = gtk_message_dialog_new(
                                      NULL,
                                      GTK_DIALOG_DESTROY_WITH_PARENT,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      "ボタンが押されたよ");
    gtk_dialog_run(GTK_DIALOG(messageDialog));
    gtk_widget_destroy(messageDialog);
}

static void openFileChooser(GtkWidget *button, gpointer user_data) {
    GtkWidget* fileChooserDialog = gtk_file_chooser_dialog_new(
                                      "ファイルを選択",
                                      NULL,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "キャンセル", GTK_RESPONSE_CANCEL,
                                      "開く", GTK_RESPONSE_ACCEPT,
                                      NULL);
    if (gtk_dialog_run(GTK_DIALOG(fileChooserDialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileChooserDialog));
        printf("選択されたファイル: %s\n", filename);
        g_free(filename);
    }
    gtk_widget_destroy(fileChooserDialog);
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello, GTK!");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *button = gtk_button_new_with_label("押すとダイアログ");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(box), button);

    GtkWidget* fileOpenButton = gtk_button_new_with_label("ファイルを開く");
    g_signal_connect(fileOpenButton, "clicked", G_CALLBACK(openFileChooser), NULL);
    gtk_container_add(GTK_CONTAINER(box), fileOpenButton);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <cairo.h>

int launchgtk();
void on_start_game_button_clicked();
void on_exit_button_clicked();
void draw(int x, int y, int width, int weight);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer
user_data);
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer
user_data);
void matCoord_To_Pixel(int x, int y , int* X, int*Y);
void pixel_To_MatCoord(int x, int y, int *X, int *Y);
#endif

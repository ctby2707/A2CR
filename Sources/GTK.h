#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <cairo.h>




int launchgtk();
void on_Start_clicked();
void on_Pause_clicked();
void set_score_label(char* score);
void set_live_label(char* live);
void set_level_label(char* level);
void draw(int x, int y, int width, int weight);
void change_color_pac_man(char color);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer
user_data);
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer
user_data);
void matCoord_To_Pixel(int x, int y , int* X, int*Y);
void pixel_To_MatCoord(int x, int y, int *X, int *Y);
#endif

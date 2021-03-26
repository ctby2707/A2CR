#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "GTK.h"
#include "pac-man.h"

//GTK global Variable
GtkWidget      *window;
GtkWidget      *fixed1;
GtkWidget      *start_game_button;
GtkWidget      *exit_button;
GtkDrawingArea *area;
GtkBuilder     *builder;
GtkOverlay     *overlay;
GtkWidget      *image;

int launchgtk()
{
  gtk_init(NULL,NULL);

  builder = gtk_builder_new_from_file("Sources/pac-man_gui.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

  //initisation of widgets

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
  overlay = GTK_OVERLAY(gtk_overlay_new());
  start_game_button = GTK_WIDGET(gtk_builder_get_object(builder,"start_game_button"));
  exit_button = GTK_WIDGET(gtk_builder_get_object(builder,"exit_button"));
  image = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
  area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
  //connect widgets to respective function

  g_signal_connect(start_game_button,"clicked",G_CALLBACK(on_start_game_button_clicked),NULL);
  g_signal_connect(exit_button,"clicked",G_CALLBACK(on_exit_button_clicked),NULL);
  g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
  g_signal_connect(area, "draw", G_CALLBACK(on_draw), get_game());
  g_signal_connect(window, "key_press_event", G_CALLBACK(on_key_press), NULL);
  g_signal_connect(window, "key_release_event", G_CALLBACK(on_key_release), NULL);
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
  gtk_overlay_add_overlay(overlay,GTK_WIDGET(area));
  gtk_overlay_add_overlay(overlay,image);
  //display window and begin windows loop

  gtk_widget_show(window);

  gtk_main();
  return EXIT_SUCCESS;
}

void on_start_game_button_clicked()
{
  printf("start_game \n");
  g_timeout_add(41,loop,NULL);
}

void on_exit_button_clicked()
{
  printf("exit \n");
}
void draw(int x, int y, int width, int weight)
{
 gtk_widget_queue_draw_area(GTK_WIDGET(area),x,y,width,weight);
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  Game *game = (Game *)user_data;
  int *map = game->map;
  for(int x = 0; x < 31; x++)
  {
    for(int y = 0; y < 28; y++)
    {
      if(map[x*28+y] == 2)
      {
        int X,Y;
        matCoord_To_Pixel(x,y,&X,&Y);
        cairo_set_source_rgb(cr,1,1,0);
        cairo_rectangle(cr,X+9,Y+9,5,5);
        cairo_fill(cr);
      }
      if(map[x*28+y] == 3)
      {
        int X,Y;
        matCoord_To_Pixel(x,y,&X,&Y);
        cairo_set_source_rgb(cr,1,1,0);
        cairo_rectangle(cr,X+4,Y+4,10,10);
        cairo_fill(cr);
      }
    }
    cairo_set_source_rgb(cr,1,1,0);//yellow
    cairo_rectangle(cr,game->pac_man.x,game->pac_man.y,20,20);
    cairo_fill(cr);
    cairo_set_source_rgb(cr,1,0,0);//red
    cairo_rectangle(cr,game->blinky.x,game->blinky.y,20,20);
    cairo_fill(cr);
    cairo_set_source_rgb(cr,1,0.5,0);//orange
    cairo_rectangle(cr,game->clyde.x,game->clyde.y,20,20);
    cairo_fill(cr);
  }
  return TRUE;
}
//--------------Input Functions----------------------------------------------

gboolean is_active = FALSE;
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  if(!is_active)
  {
    is_active = TRUE;
    if(event->keyval == GDK_KEY_z)
      request_move('N');
    if(event->keyval == GDK_KEY_q)
      request_move('G');
    if(event->keyval == GDK_KEY_s)
      request_move('S');
    if(event->keyval == GDK_KEY_d)
      request_move('D');
  }
  return TRUE;
}
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  is_active = FALSE;
  return TRUE;
}

//--------------Conversion Functions------------------------------------------
void matCoord_To_Pixel(int x, int y , int* X, int*Y)
{
  *X = 10+y*22;
  *Y = 25+x*22;
  return;
}

void pixel_To_MatCoord(int x, int y, int *X, int *Y)
{
  *X = (y-25)/22;
  *Y = (x-10)/22;
}

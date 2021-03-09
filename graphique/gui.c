#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <cairo.h>

//Make them Global

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *start_game_button;
GtkWidget *exit_button;
GtkDrawingArea *area;
GtkBuilder *builder;
GtkOverlay *overlay;
GtkWidget *image;


const int wall = 0;
const int alley = 1;
const int alley_pac_gum = 2;
const int alley_super = 3;
const int fantom_home = 4;
const int tunnel = 5;
const int map_ylen = 31;
const int map_xlen = 28;

int map[31][28] ={
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
  {0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0}, //1
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //2
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //3
  {0,2,2,2,2,3,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,3,2,2,2,2,0}, //4
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //5
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //6
  {0,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,0}, //7
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //8
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //9
  {5,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,5}, //10
  {0,2,0,0,0,0,2,0,0,1,0,0,0,4,4,0,0,0,1,0,0,2,0,0,0,0,2,0}, //11
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //12
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //13
  {0,2,2,2,2,2,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,2,2,2,2,2,0}, //14
  {0,1,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,0}, //15
  {0,1,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,1,0}, //16
  {0,1,1,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,1,1,0}, //17
  {0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,0,0,0}, //18
  {0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0}, //19
  {5,1,1,1,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,1,1,1,5}, //20
  {0,1,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,1,0}, //21
  {0,1,0,0,0,0,2,0,0,2,2,2,2,1,1,2,2,2,2,0,0,2,0,0,0,0,1,0}, //22
  {0,2,2,2,2,2,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,2,2,2,2,2,0}, //23
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //24
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //25
  {0,2,0,0,2,3,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,3,2,0,0,2,0}, //26
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //27
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //28
  {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0}, //29
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //30



//function when button clicked

void on_start_game_button_clicked()
{
  printf("start_game \n");
}

void on_exit_button_clicked()
{
  printf("exit \n");
}

void do_drawing (cairo_t *cr)
{
  //set background color to black
  //cairo_set_source_rgb(cr,0,0,0);
  //cairo_paint(cr);
  //drawing every pac gum to test cairo function and map settings 
  int y = 0;
  while (y<map_ylen)
    {
      int x = 0;
      while(x<map_xlen)
  {
    if(map[y][x]==2)
      {
        cairo_set_source_rgb(cr,1,1,0);
        cairo_rectangle(cr,18+x*22,30+y*22,5,5);
        cairo_fill(cr);
      }
   /*
          //if the map supperposition doesnt work we have still this
    if(map[y][x]==0)
      {
         cairo_set_source_rgb(cr,0,0,1);
        cairo_rectangle(cr,x*20-7,y*20-7,20,20);
        cairo_fill(cr);
      }
    */
    x = x + 1;
  }
      y = y + 1;
    }
  //propagate the signal
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  printf("draw  \n");
  do_drawing(cr);
  return FALSE;
}



int launchgtk()
{
  gtk_init(NULL,NULL);

  builder = gtk_builder_new_from_file("pac-man_gui.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

  g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

  //initisation of widgets

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
  overlay = gtk_overlay_new();
  start_game_button = GTK_WIDGET(gtk_builder_get_object(builder,"start_game_button"));
  exit_button = GTK_WIDGET(gtk_builder_get_object(builder,"exit_button"));
  image = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
  area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));

  //connect widgets to respective functions

  g_signal_connect(start_game_button,"clicked",G_CALLBACK(on_start_game_button_clicked),NULL);
  g_signal_connect(exit_button,"clicked",G_CALLBACK(on_exit_button_clicked),NULL);
  g_signal_connect(area, "draw", G_CALLBACK(on_draw), NULL);

  gtk_overlay_add_overlay(overlay,area);
  gtk_overlay_add_overlay(overlay,image);


  //display window and begin windows loop

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

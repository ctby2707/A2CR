#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <cairo.h>
//Global Variable

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *start_game_button;
GtkWidget *exit_button;
GtkDrawingArea *area;
GtkBuilder *builder;
GtkOverlay *overlay;
GtkWidget *image;

typedef struct Player
{
  GdkRectangle rect;
  guint event;
  guint direction;
  int x;
  int y;
} Player;

const int speed = 1;
const int wall = 0;
const int alley = 1;
const int alley_pac_gum = 2;
const int alley_super = 3;
const int fantom_home = 4;
const int tunnel = 5;
const int map_ylen = 28;
const int map_xlen = 31;
int score = 0;

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
gboolean on_move_p(gpointer user_data)
{
  Player* player = user_data;
  if(player->direction == 0)
  {
    player->rect.y = player->rect.y - speed;
  }
  else if(player->direction == 1)
  {
    player->rect.y = player->rect.y + speed;
  }
  else if(player->direction == 2)
  {
    player->rect.x = player->rect.x - speed;
  }
  else if(player->direction == 3)
  {
    player->rect.x = player->rect.x + speed;
  }
  player->x = (player->rect.x-18)/22;
  player->y = (player->rect.y-30)/22;
  printf("{%i,%i}\n",player->x,player->y);
   gtk_widget_queue_draw_area(GTK_WIDGET(area),0,0,635,760);
  return TRUE;
}
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  Player* player = user_data;
  if(event->keyval == GDK_KEY_z)
  {
    player->direction = 0;
  }
  else if(event->keyval == GDK_KEY_s)
  {
    player->direction = 1;
  }
  else if(event->keyval == GDK_KEY_q)
  {
    player->direction = 2;
  }
  else if(event->keyval == GDK_KEY_d)
  {
    player->direction = 3;
  }
  else
  {
    player->direction = -1;
  }
  if(player->event == 0)
    player->event = g_timeout_add(10,on_move_p,player);
  return TRUE;
}
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  Player* player = user_data;
  if(player->event != 0)
    g_source_remove(player->event);
  player->event = 0;
  return TRUE;
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  //drawing every pac gum to test cairo function and map settings
  Player* p = user_data;
  for(int x = 0; x < map_xlen; x++)
  {
    for(int y = 0; y < map_ylen; y++)
    {
      if(map[x][y]==2)
      {
        cairo_set_source_rgb(cr,1,1,0);
        cairo_rectangle(cr,18+y*22,30+x*22,5,5);
        cairo_fill(cr);
      }
    }
  }

  cairo_set_source_rgb(cr,1,1,0);
  cairo_rectangle(cr,p->rect.x,p->rect.y,p->rect.width,p->rect.height);
  cairo_fill(cr);
  return FALSE;
}

int launchgtk()
{
  gtk_init(NULL,NULL);

  builder = gtk_builder_new_from_file("pac-man_gui.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

  //initisation of widgets

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
  overlay = GTK_OVERLAY(gtk_overlay_new());
  start_game_button = GTK_WIDGET(gtk_builder_get_object(builder,"start_game_button"));
  exit_button = GTK_WIDGET(gtk_builder_get_object(builder,"exit_button"));
  image = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
  area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
  //connect widgets to respective functions

  Player player = {
    .rect = { 40, 42, 22, 22 },
    .event = 0,
    .direction = 0,
    .x = 1,
    .y = 1
  };

  g_signal_connect(start_game_button,"clicked",G_CALLBACK(on_start_game_button_clicked),NULL);
  g_signal_connect(exit_button,"clicked",G_CALLBACK(on_exit_button_clicked),NULL);
  g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
  g_signal_connect(area, "draw", G_CALLBACK(on_draw), &player);
  g_signal_connect(window, "key_press_event", G_CALLBACK(on_key_press), &player);
  g_signal_connect(window, "key_release_event", G_CALLBACK(on_key_release), &player);

  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
  gtk_overlay_add_overlay(overlay,GTK_WIDGET(area));
  gtk_overlay_add_overlay(overlay,image);
  //display window and begin windows loop

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

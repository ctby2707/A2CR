#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "GTK.h"
#include "game_init.h"
#include "game_events.h"
#include "loop.h"
#include "main.h"
#include "train.h"
#include "play.h"
//GTK global Variable

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *Start;
GtkWidget *Pause;
GtkWidget *Qactivate;
GtkDrawingArea *area;
GtkBuilder *builder;
GtkOverlay *overlay;
GtkWidget *image;
GtkWidget *score_label;
GtkWidget *live_label;
GtkWidget *level_label;
int alreadystarted = 0;
cairo_t *crg;


int launchgtk()
{

  gtk_init(NULL, NULL);
  builder = gtk_builder_new_from_file("Data/pac-man_gui.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

  //initisation of widgets

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  overlay = GTK_OVERLAY(gtk_overlay_new());
  Start = GTK_WIDGET(gtk_builder_get_object(builder, "Start"));
  Pause = GTK_WIDGET(gtk_builder_get_object(builder, "Pause"));
  Qactivate = GTK_WIDGET(gtk_builder_get_object(builder, "Qactivate"));
  image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
  area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
  score_label = GTK_WIDGET(gtk_builder_get_object(builder, "score_label"));
  live_label = GTK_WIDGET(gtk_builder_get_object(builder, "live_label"));
  level_label = GTK_WIDGET(gtk_builder_get_object(builder, "level_label"));

  //connect widgets to respective function

  g_signal_connect(Start, "clicked", G_CALLBACK(on_Start_clicked), NULL);
  g_signal_connect(Pause, "clicked", G_CALLBACK(on_Pause_clicked), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), window);
  g_signal_connect(Qactivate,"clicked",G_CALLBACK(on_Qactivate_clicked), NULL);
  g_signal_connect(area, "draw", G_CALLBACK(on_draw), NULL);
  //g_signal_connect(window, "key_press_event", G_CALLBACK(on_key_press), NULL);
  //g_signal_connect(window, "key_release_event", G_CALLBACK(on_key_release), NULL);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  //gtk_overlay_add_overlay(overlay,GTK_WIDGET(area));
  //gtk_overlay_add_overlay(overlay,image);
  //display window and begin windows loop

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

void on_window_destroy(GtkWidget *widget,GdkEvent *event,gpointer data)
{
  printf("tamere \n");
  gtk_main_quit();
}

void on_Start_clicked()
{
  Game *game = get_game();
  gtk_widget_set_sensitive(Pause, TRUE);
  gtk_widget_set_sensitive(Start, FALSE);
  if (alreadystarted == 0)
  {
    g_timeout_add(100, play, NULL);
    change_game_status(game, 1);
    alreadystarted = 1;
  }
  else
    change_game_status(game, 1);
}

void on_Pause_clicked()
{
  Game *game = get_game();
  gtk_widget_set_sensitive(Start, TRUE);
  gtk_widget_set_sensitive(Pause, FALSE);
  change_game_status(game, 0);
}

void on_Qactivate_clicked()
{
  Game *game = get_game();
  if(game->mode == 0)
    {
      game->mode = 1;
      gtk_button_set_label(GTK_BUTTON(Qactivate), "Agent mode enable");
    }
  else
    {
      game->mode = 0;
      gtk_button_set_label(GTK_BUTTON(Qactivate), "AI mode enable");
    }
}


void set_score_label(char *score)
{
  gtk_label_set_text(GTK_LABEL(score_label), score);
}
void set_live_label(char *live)
{
  gtk_label_set_text(GTK_LABEL(live_label), live);
}
void set_level_label(char *level)
{
  gtk_label_set_text(GTK_LABEL(level_label), level);
}

void draw(int x, int y, int width, int weight)
{
  gtk_widget_queue_draw_area(GTK_WIDGET(area), x, y, width, weight);
}

void change_color_pac_man(char color)
{
  Game *game = (Game *)get_game();
  if (color == 'b')
  {
    cairo_set_source_rgb(crg, 0, 0, 0.7); //blue
  }
  else
    cairo_set_source_rgb(crg, 1, 1, 0); //yellow

  cairo_rectangle(crg, game->pac_man.x, game->pac_man.y, 20, 20);
  cairo_fill(crg);
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  crg = cr;
  Game *game = get_game();
  int *map = game->map;
  int *pac_man_open;
  int *ghost_pixel_art = game->ghost_pixel_art;
  if (game->open == 3)
  {
    pac_man_open = game->pac_man_open;
    game->open = 0;
  }
  else
  {
    pac_man_open = game->pac_man_closed;
    game->open = game->open + 1;
  }
  for (int x = 0; x < 31; x++)
  {
    for (int y = 0; y < 28; y++)
    {
      if (map[x * 28 + y] == 2)
      {
        int X, Y;
        matCoord_To_Pixel(x, y, &X, &Y);
        cairo_set_source_rgb(cr, 1, 1, 0);
        cairo_rectangle(cr, X + 9, Y + 9, 5, 5);
        cairo_fill(cr);
      }
      if (map[x * 28 + y] == 3)
      {
        int X, Y;
        matCoord_To_Pixel(x, y, &X, &Y);
        cairo_set_source_rgb(cr, 1, 1, 0);
        cairo_rectangle(cr, X + 4, Y + 4, 10, 10);
        cairo_fill(cr);
      }
    }

    if (game->pac_man.color == 'y')
      cairo_set_source_rgb(cr, 1, 1, 0); //yellow
    else
      cairo_set_source_rgb(cr, 0, 0, 0.75); //blue

    /*
    //old pac man print
    cairo_rectangle(cr,game->pac_man.x,game->pac_man.y,20,20);
    cairo_fill(cr);
     */

    for (int x = 0; x < 7; x++)
    {
      for (int y = 0; y < 7; y++)
      {
        if (game->pac_man.dir == 'E')
        {
          if (pac_man_open[y * 7 + x] == 0)
          {

            cairo_rectangle(cr, game->pac_man.x + 4 * x, game->pac_man.y + 4 * y - 4, 4, 4);
            cairo_fill(cr);
          }
        }
        if (game->pac_man.dir == 'S')
        {
          if (pac_man_open[x * 7 + y] == 0)
          {

            cairo_rectangle(cr, game->pac_man.x + 4 * x, game->pac_man.y + 4 * y - 4, 4, 4);
            cairo_fill(cr);
          }
        }
        if (game->pac_man.dir == 'N')
        {
          if (pac_man_open[(x)*7 + (6 - y)] == 0)
          {

            cairo_rectangle(cr, game->pac_man.x + 4 * x, game->pac_man.y + 4 * y - 4, 4, 4);
            cairo_fill(cr);
          }
        }
        if (game->pac_man.dir == 'W')
        {
          if (pac_man_open[(y)*7 + (6 - x)] == 0)
          {

            cairo_rectangle(cr, game->pac_man.x + 4 * x, game->pac_man.y + 4 * y - 4, 4, 4);
            cairo_fill(cr);
          }
        }
      }
    }

    for (int x = 0; x < 7; x++)
    {
      for (int y = 0; y < 7; y++)
      {
        if (ghost_pixel_art[y * 7 + x] == 1)
        {
          if(game->blinky.eat == 0 && game->chase > 0)
            cairo_set_source_rgb(cr, 0, 0, 1); //blue
          else
            cairo_set_source_rgb(cr, 1, 0, 0); //red

          cairo_rectangle(cr, game->blinky.x + 4 * x, game->blinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          if(game->clyde.eat == 0 && game->chase > 0)
            cairo_set_source_rgb(cr, 0, 0, 1); //blue
          else
            cairo_set_source_rgb(cr, 1, 0.5, 0); //orange

          cairo_rectangle(cr, game->clyde.x + 4 * x, game->clyde.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          if(game->inky.eat == 0 && game->chase > 0)
            cairo_set_source_rgb(cr, 0, 0, 1); //blue
          else
            cairo_set_source_rgb(cr, 0, 0, 1); //blue

          cairo_rectangle(cr, game->inky.x + 4 * x, game->inky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          if(game->pinky.eat == 0 && game->chase > 0)
            cairo_set_source_rgb(cr, 0, 0, 1); //blue
          else
            cairo_set_source_rgb(cr, 1, 0.7, 0.8); //pink

          cairo_rectangle(cr, game->pinky.x + 4 * x, game->pinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);
        }
        if (ghost_pixel_art[y * 7 + x] == 2)
        {
          cairo_set_source_rgb(cr, 1, 1, 1); //white
          cairo_rectangle(cr, game->blinky.x + 4 * x, game->blinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->clyde.x + 4 * x, game->clyde.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->inky.x + 4 * x, game->inky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->pinky.x + 4 * x, game->pinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);
        }
        if (ghost_pixel_art[y * 7 + x] == 0)
        {
          cairo_set_source_rgb(cr, 0, 0, 0); //black
          cairo_rectangle(cr, game->blinky.x + 4 * x, game->blinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->clyde.x + 4 * x, game->clyde.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->inky.x + 4 * x, game->inky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);

          cairo_rectangle(cr, game->pinky.x + 4 * x, game->pinky.y + 4 * y - 4, 4, 4);
          cairo_fill(cr);
        }
      }
    }
  }
  return TRUE;
}
//--------------Input Functions----------------------------------------------

/*gboolean is_active = FALSE; INPUT FUNCTIONS KEY

  <<<<<<< HEAD
  gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
  {
  if (!is_active)
  {
  is_active = TRUE;
  if (event->keyval == GDK_KEY_Up)
  request_move('N');
  if (event->keyval == GDK_KEY_Left)
  request_move('G');
  if (event->keyval == GDK_KEY_Down)
  request_move('S');
  if (event->keyval == GDK_KEY_Right)
  request_move('D');
  }
  return TRUE;
  }
  gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
  {
  is_active = FALSE;
  return TRUE;
  }*/

//--------------Conversion Functions------------------------------------------
void matCoord_To_Pixel(int x, int y, int *X, int *Y)
{
  *X = 10 + y * 22;
  *Y = 25 + x * 22;
  return;
}

void pixel_To_MatCoord(int x, int y, int *X, int *Y)
{
  *X = (y - 25) / 22;
  *Y = (x - 10) / 22;
}
void middle_of_case(int X, int Y, int *x, int *y)
{
  *x = 10 + Y * 22;
  *y = 25 + X * 22;
}

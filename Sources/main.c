#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include "GTK.h"
#include "pac-man.h"
#include <math.h>

int main()
{
  srand(time(NULL));
  return launchgtk();
}

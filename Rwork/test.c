#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adam_optim.h"

double grad(double m)
{
  return ((2 * m) - 2);
}


int main()
{
  double w0 = 0;
  double b0 = 0;
  double dw;
  double db;
  double w0old;
  struct AdamOpti adam;
  initAdamOpti(&adam);
  double t = 1;
  int conv = 0;

  while (conv == 0)
  {
    dw = grad(w0);
    db = grad(b0);
    w0old = w0;

    update(&adam, t, &w0, &b0, &dw, &db);

    if (w0 == w0old)
      conv = 1;
    if (conv == 1)
      printf("converged after %lf iterqtions \n", t);
    else
      printf("iteration %lf : weights = %lf \n", t, w0);
    t++;
  }
}

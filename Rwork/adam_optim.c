#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adam_optim.h"

void initAdamOpti(struct AdamOpti *adam)
{
  adam->m_dw =0;
  adam->m_db =0;
  adam->v_dw =0;
  adam->v_db =0;
  adam->beta1 = 0.9;
  adam->beta2 = 0.999;
  adam->eta = 0.01;
  adam->epsi = 0.000000001;
}

void update(struct AdamOpti *adam, double t, double* w, double* b, double* dw, double* db)
{
  //momentum beta 1//
  //weights//
  adam->m_dw = adam->beta1 * adam->m_dw + (1 - adam->beta1) * *dw;
  //biases//
  adam->m_db = adam->beta1 * adam->m_db + (1 - adam->beta1) * *db;

  //rms beta 2//
  //weights//
  adam->v_dw = adam->beta2 * adam->v_dw + (1 - adam->beta2) * pow((*dw), 2);
  //biases//
  adam->v_db = adam->beta2 * adam->v_db + (1 - adam->beta2) * *db;

  //bias correction//
  double m_dw_c = adam->m_dw / (1 - pow((adam->beta1), t));
  double m_db_c = adam->m_db / (1 - pow((adam->beta1), t));
  double v_dw_c = adam->v_dw / (1 - pow((adam->beta2), t));
  double v_db_c = adam->v_db / (1 - pow((adam->beta2), t));

  //update//
  *w = *w - adam->eta * (m_dw_c / (sqrt(v_dw_c) + adam->epsi));
  *b = *b - adam->eta * (m_db_c / (sqrt(v_db_c) + adam->epsi));
}

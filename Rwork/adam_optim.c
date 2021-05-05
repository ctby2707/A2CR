#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adam_opti.h"

void update(struct* AdamOpti, int t, double* w, double* b, double* dw, double* db)
{
  //momentum beta 1//
  //weights//
  AdamOpti->m_dw = AdamOpti->beta1 * AdamOtpi->m_dw + (1-AdamOpti->beta1) * *dw;
  //biases//
  AdamOpti->m_db = AdamOpti->beta1 * AdamOtpi->m_db + (1-AdamOpti->beta1) * *db;

  //rms beta 2//
  //weights//
  AdamOpti->v_dw = AdamOpti->beta2 * AdamOtpi->v_dw + (1-AdamOpti->beta2) * (*dw)**2;
  //biases//
  AdamOpti->v_db = AdamOpti->beta2 * AdamOtpi->v_db + (1-AdamOpti->beta2) * *db;

  //bias correction//
  double m_dw_c = AdamOpti->m_dw / (1-((AdamOpti->beta1)**t));
  double m_db_c = AdamOpti->m_db / (1-((AdamOpti->beta1)**t));
  double v_dw_c = AdamOpti->v_dw / (1-((AdamOpti->beta2)**t));
  double v_db_c = AdamOpti->v_db / (1-((AdamOpti->beta2)**t));

  //update//
  *w = *w - AdamOpti->eta * (m_dw_c / (sqrt(v_dw_c) + AdamOpti->espi));
  *b = *b - AdamOpti->eta * (m_db_c / (sqrt(v_db_c) + AdamOpti->espi));
}

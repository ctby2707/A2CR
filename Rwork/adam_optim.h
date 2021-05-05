#ifndef ADAM_OPTI_H
#define ADAM_OPTI_H

struct AdamOpti
{
  double m_dw = 0;
  double m_db = 0;
  double v_dw = 0;
  double v_db = 0;
  double beta1 = 0.9;
  double beta2 = 0.999;
  double eta = 0.01;
  double epsi = 0.000000001;
};

void update(struct* AdamOpti, int t, double* w, double* b, double* dw, double* db);

#endif

#ifndef ADAM_OPTI_H
#define ADAM_OPTI_H

struct AdamOpti
{
  double m_dw;
  double m_db;
  double v_dw;
  double v_db;
  double beta1;
  double beta2;
  double eta;
  double epsi;
};


void initAdamOpti(struct AdamOpti *adam);


void update(struct AdamOpti *adam, double t, double* w, double* b, double* dw, double* db);


#endif

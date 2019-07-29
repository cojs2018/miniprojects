#include "fourier_transform.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>

using namespace std;
using namespace Data;

vector<complex<double>> wave::transform(vector<double> am, vector<double> fs, int sr, int ns)
{
  complex<double> s;
  vector<complex<double>> result_before_integration;

  for(int j = 0; j < ns; j++)
  {
    s = exp(1i * am.at(j) * j/sr);
    result_before_integration.pushback(s);
  }

  vector<complex<double>> result;
  result = wave::integ(result_before_integration, 0, double(ns), 1.0);
}

vector<complex<double>> wave::integ(vector<complex<double>> v, double x0, double x1, double h)
{
  vector<complex<double>> r;

  for(double j = x0; j < x1; j = j + h)
  {
    complex<double> rr;
    for(double k = x0; k <= j + h; k = k + h)
    {
      complex<double> u = v.at(k);
      double ureal = u.real();
      double uim = u.imag();

      if((k == x0) || (k == j + h))
      {
        rr = rr + (ureal + uim*1i);
      }
      else
      {
        rr = rr + (3 * (ureal + uim*1i));
      }
    }
    rr = 3*rr/8;
    r.pushback(rr);
  }

  return r;
}

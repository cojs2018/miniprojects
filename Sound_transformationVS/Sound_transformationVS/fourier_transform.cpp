#include "fourier_transform.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>

using namespace std;
using namespace Data;

vector<complex<double>> wave::transform(vector<double> am, vector<double> fs, int sr, int ns)
{ /* Function that performs Fourier transform on a given sound wave by
   * first multiplying the amplitude by the element number over the sampling
   * frequency, and imaginary value i, taking the exponent and multiplying by
   * the wave equation. After this the integral of the data is found. */
  complex<double> s;
  vector<complex<double>> result_before_integration;

  for(int j = 0; j < ns; j++)
  { //Note: 1/sr (sampling frequency) would give the time period.
    s = cos(am.at(j) * j/sr)*exp(1i * am.at(j) * double(j/sr));
    result_before_integration.push_back(s);
  }

  vector<complex<double>> result;
  result = wave::integ(result_before_integration, 0, double(ns), 1.0);

  return result;
}

vector<complex<double>> wave::integ(vector<complex<double>> v, double x0, double x1, double h)
{ /* Function working out the complex integral of given data using Simpson's
   * 3/8ths rule.*/
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
        rr = rr + (3.0 * (ureal + uim*1i));
      }
    }
    rr = 3.0 * rr / 8.0;
    r.push_back(rr);
  }

  return r;
}

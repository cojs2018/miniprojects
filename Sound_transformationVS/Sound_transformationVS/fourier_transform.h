#pragma
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>

namespace Data
{
	static class wave
	{
	public:
		//Variables
		int sampling_rate;
		int number_of_samples;
		std::vector<double> amplitude;
		std::vector<double> frequency;

		std::vector<std::complex<double>> transform(std::vector<double>, std::vector<double>, int, int);
		std::vector<std::complex<double>> integ(std::vector<std::complex<double>>, double, double, double);
	};
}

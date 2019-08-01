#pragma
#include <vector>


namespace Data
{
  static class sound_file
  {
  public:
    int sampling_rate;
    int number_of_samples;
    std::vector<double> amplitude;
    std::vector<double> frequency;
  }
}

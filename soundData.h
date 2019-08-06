#pragma
#include <vector>

#define Sound_CONFIG_VERSION @Sound_CONFIG_VERSION@

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

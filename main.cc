#pragma
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "soundData.h"

using namespace std;
using namespace Data;

typedef struct WAV_HEADER{
  char  Riff[4];
  unsigned long ChunkSize;
  char WAVE[4];
  char fmt[4];
  unsigned long Subchunk1Size;
  unsigned short AudioFormat;
  unsigned short NumOfChan;
  unsigned long SamplesPerSec; //Frequency. Amplitude is 2*pi*f.
  unsigned long bytesPerSec;
  unsigned short blockAllign;
  unsigned short bitsPerSample;
  char Subchunk2ID[4];
  unsigned long Subchunk2Size;
  bytes *data;
}wav_hdr;

int main(int args, char *argv[])
{
  vector<sound_file> sf;

  wav_hdr newWaveHDR;
  FILE* wave_file;
  int headerSize = sizeof(newWaveHDR),filelength = 0;

  do {
    sound_file sf0;

    //Get file path
    const char* file_path = ".../example.wav";
    wave_file = fopen(file_path, 'r');

    size_t bytesRead = fread(&newWaveHDR, 1, headerSize, wave_file);
    if(bytesRead > 0)
    {
      //Read Data
      uint16_t bytesPerASample = newWaveHDR.bitsPerSample / 8;
      uint16_t numSamples = newWaveHDR.ChunkSize / bytesPerASample;

      sf0.number_of_samples = int(numSamples);

      uint32_t fs = newWaveHDR.SamplesPerSec; //Sampling frequency
      sf0.sampling_rate = int(fs);

      static const uint16_t BUFFER_SIZE = 4096;
      int8_t* buffer = new int8_t[BUFFER_SIZE];
      while((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wave_file)) > 0)
      {
        //Read raw audio data to extract a vector of amplitude and frequency
        vector<double> freq;
        vector<double> amp;

        uint32_t audio_data_size = newWaveHDR.Subchunk2Size;
        bytes *data_store = newWaveHDR.data;
        for(int i = 0, i < audio_data_size, i++)
        {
          //Height of each byte will be the amplitude
          double a = double(data_store[i]);
          double f = 2 * PI / a; //Frequency is 2*pi over amplitude.

          freq.pushback(f);
          amp.pushback(a);
        }

        sf0.frequency = freq;
        sf0.amplitude = amp;
      }
      delete [] buffer;
      buffer = nullptr;
      filelength = getFileSize(wave_file);
    }

    unsigned long audio_length = newWaveHDR.Subchunk2Size();
  } while(1);
}

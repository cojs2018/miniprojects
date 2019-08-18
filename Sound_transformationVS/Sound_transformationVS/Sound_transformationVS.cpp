#pragma
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <complex>
#include <ctime>
#include "soundData.h"
#include "fourier_transform.h"
#include <cstddef>

constexpr auto PI = 3.14159265359;

using namespace std;
using namespace Data;

typedef struct WAV_HEADER { //Define structure for wave file data
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
	unsigned short* data;
}wav_hdr;

int main(int args, char* argv[])
{
	sound_file sf0; //Sound file instance object

	//Define new structure
	wav_hdr newWaveHDR;
	FILE* wave_file;
	int headerSize = sizeof(newWaveHDR), filelength = 0;

	do {
		//Get file path
		const char* file_path = ".../example.wav";
		const char* mode = "r";
		wave_file = fopen(file_path, mode);

		size_t bytesRead = fread(&newWaveHDR, 1, headerSize, wave_file);
		if (bytesRead > 0)
		{
			//Read Data
			uint16_t bytesPerASample = newWaveHDR.bitsPerSample / 8;
			uint16_t numSamples = newWaveHDR.ChunkSize / bytesPerASample;

			sf0.number_of_samples = int(numSamples);

			uint32_t fs = newWaveHDR.SamplesPerSec; //Sampling frequency
			sf0.sampling_rate = int(fs);

			static const uint16_t BUFFER_SIZE = 4096;
			int8_t* buffer = new int8_t[BUFFER_SIZE];
			while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wave_file)) > 0)
			{
				//Read raw audio data to extract a vector of amplitude and frequency
				vector<double> freq;
				vector<double> amp;

				uint32_t audio_data_size = newWaveHDR.Subchunk2Size;
				unsigned short* data_store = newWaveHDR.data;
				for (int i = 0; i < audio_data_size; i++)
				{
					//Height of each byte will be the amplitude
					double a = double(data_store[i]);
					double f = 2 * PI / a; //Frequency is 2*pi over amplitude.

					freq.push_back(f); //Add to vectors
					amp.push_back(a);
				}

				sf0.frequency = freq; //Set as instance of sound file
				sf0.amplitude = amp;
			}
			delete[] buffer;
			buffer = nullptr;
			//filelength = getFileSize(wave_file);
		}

		unsigned long audio_length = newWaveHDR.Subchunk2Size;
	} while (1);

	sound_file sf1;
	sound_file sf1_imag;

	wave wv; //Generate new wave
	vector<complex<double>> new_amp = wv.transform(sf0.amplitude, sf0.frequency, sf0.sampling_rate, sf0.number_of_samples);
	vector<double> real_values;
	vector<double> imag_values;
	//Extract real and imaginary vales from each vector entry
	for (int count = 0; count < new_amp.size(); count++)
	{
		//Define element of the vector
		complex<double> z_element = new_amp.at(count);

		real_values.push_back(z_element.real());
		sf1.frequency.push_back(z_element.real() * 2 * PI);
		imag_values.push_back(z_element.imag());
		sf1_imag.frequency.push_back(z_element.imag() * 2 * PI);
	}

	sf1.sampling_rate = sf0.sampling_rate; //Instance where this stays the same.
	sf1.number_of_samples = real_values.size();
	sf1.amplitude = real_values;

	sf1_imag.sampling_rate = sf0.sampling_rate;
	sf1_imag.number_of_samples = imag_values.size();
	sf1_imag.amplitude = imag_values;
}
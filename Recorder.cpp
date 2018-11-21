#include "Recorder.h"

Recorder::Recorder() {
	freqX = 0;
	freqY = 0;
	magnitudeX = 0;
	magnitudeY = 0;
	magnitude = 0;

}

Recorder::Recorder(const Int16 *samples)
{
	freqX = 0;
	freqY = 0;
	magnitudeX = 0;
	magnitudeY = 0;

}

bool Recorder::onStart() {

	setProcessingInterval(milliseconds(200));

	return true;
}

void Recorder::fft(CArray& samples)
{

	const int N = 2000;
	const double PI = 3.141592653589793238460;
	Complex s;

	if (N <= 1) return;
	CArray even =samples[slice(0, N / 2, 2)];
	CArray odd = samples[slice(1, N / 2, 2)];

	fft(even);
	fft(odd);

	for (int k = 0; k < N / 2; k++)
	{
		Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
		samples[k] = even[k] + t;
		s = samples[k];
		samples[k + N / 2] = even[k] - t;
		
	}
	power = s.real();
}

void Recorder::analyzeSamples(const Int16 *samples, size_t sampleCount)//CArray& samples
{
	//cout << analyze.get_id() << endl;

	clock_t t;
	t = clock();
	for (int j = 0; j < 8; ++j) {
		//goertzel = thread(&Recorder::goertzelFilter, this, samples, targetFrequencies[j], 200);//goertzel;
		goertzelFilter(samples, targetFrequencies[j] , 200);
		//fft(samples);
		magnitude = power;
		
		if (magnitude > magnitudeX && magnitude > magnitudeY) {
			freqY = freqX;
			magnitudeY = magnitudeX;
			freqX = targetFrequencies[j];
			magnitudeX = magnitude;
		}
		else if (magnitude > magnitudeY) {
			freqY = targetFrequencies[j];
			magnitudeY = magnitude;
		}
		//goertzel.join();
	}
	//cout << goertzel.get_id() << endl;
	//freqs = thread(&Recorder::freqToHex, this, freqX, freqY);
	//cout << freqs.get_id() << endl;
	//freqs.join();
	freqToHex(freqX, freqY);
	cout << hexValue << " : " << freqX << "-" << freqY << endl;
	t = clock()-t;
	//myfile.open("GoertzelThread.txt");
	//cout << t << ',' << endl;
	//myfile << t << ',';
	

	freqX = 0;
	freqY = 0;
	magnitudeX = 0;
	magnitudeY = 0;

	//cout << sampleCount << endl;
}

bool Recorder::onProcessSamples(const Int16 *samples, size_t sampleCount)//CArray& samples) 
{	
	analyze = thread(&Recorder::analyzeSamples, this, samples, sampleCount);

	analyze.join();
	return true;
}

void Recorder::onStop()
{

}

void Recorder::goertzelFilter(const Int16 *samples, double freq, int N) {
	
	double s_prev = 0.0;
	double s_prev2 = 0.0;
	double coeff, normalizedfreq, s;
	double PI = 3.141592653589793238460;
	normalizedfreq = freq / 8000; //freq / samplingRate
	coeff = 2 * cos(2 * PI * normalizedfreq);
	for (int i = 0; i < N; i++) {
		s = samples[i] + coeff * s_prev - s_prev2;
		s_prev2 = s_prev;
		s_prev = s;
	}
	power = s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2;
}


void Recorder::freqToHex(int inFreqX, int inFreqY) {
	switch (inFreqX + inFreqY) {
	case 1336 + 941:
		hexValue = '0';
		break;
	case 1209 + 697:
		hexValue = '1';
		break;
	case 1336 + 697:
		hexValue = '2';
		break;
	case 1477 + 697:
		hexValue = '3';
		break;
	case 1209 + 770:
		hexValue = '4';
		break;
	case 1336 + 770:
		hexValue = '5';
		break;
	case 1477 + 770:
		hexValue = '6';
		break;
	case 1209 + 852:
		hexValue = '7';
		break;
	case 1336 + 852:
		hexValue = '8';
		break;
	case 1477 + 852:
		hexValue = '9';
		break;
	case 1633 + 697:
		hexValue = 'A';
		break;
	case 1633 + 770:
		hexValue = 'B';
		break;
	case 1633 + 852:
		hexValue = 'C';
		break;
	case 1633 + 941:
		hexValue = 'D';
		break;
	case 1477 + 941:
		hexValue = 'E';
		break;
	case 1209 + 941:
		hexValue = 'F';
		break;
	}
}

char Recorder::getHexValue() {
	return hexValue;
}

Recorder::~Recorder() {
	stop();
}
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <future>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <mutex>
#include <condition_variable>
#include <valarray>
#include <complex>
#include <fstream>


using namespace std;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
using namespace sf;

class Recorder : public SoundRecorder {
public:
	Recorder();
	Recorder(const Int16 *samples);

	virtual bool onStart();
	virtual bool onProcessSamples(const Int16 *samples, size_t sampleCount);//CArray& samples);
	virtual void onStop();

	void goertzelFilter(const Int16 samples[], double freq, int N);
	void analyzeSamples(const Int16 *samples, size_t sampleCount);//CArray& samples/*, size_t sampleCount*/);
	void fft(CArray& samples);

	void freqToHex(int freqX, int freqY);

	char getHexValue();

	thread analyze;
	thread goertzel;
	thread freqs;

	~Recorder();

protected:
	int targetFrequencies[8] = { 697,770,852,941,1209,1336,1477,1633 };

	int freqX;
	int freqY;

	char hexValue;
	double magnitudeX;
	double magnitudeY;
	double magnitude;
	double power;
	Complex poweri;
	Complex magnitudei;
	Complex magnitudeiX;
	Complex magnitudeiY;
	ofstream myfile;
	

};


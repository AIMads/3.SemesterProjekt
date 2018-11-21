#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

class DTMFGenerator {
public:
	DTMFGenerator();
	DTMFGenerator(int TPS);

	void frameToTones(string frame);
	void hexToTone(char hex);
	void play();

	double getFreqX();
	double getFreqY();

	~DTMFGenerator();
protected:
	int samples;
	double sampleRate;
	double amplitude;
	double twoPi;
	int toneNum;
	int tonesPerSecond;
	//Int16 freqi[2000];
	double freqX;
	double freqY;
	double x;
	double y;

	unsigned long frameSize;

	SoundBuffer buffer;
	Sound sound;
	Int16* rawTones;
};



#include "DTMFGenerator.h"

DTMFGenerator::DTMFGenerator() {}

DTMFGenerator::DTMFGenerator(int TPS) {
	tonesPerSecond = TPS;
	sampleRate = 20000.;
	samples = sampleRate / tonesPerSecond;
	amplitude = 1000.;
	twoPi = 6.28318;

	freqX;
	freqY;
	x = 0;
	y = 0;

	toneNum = 0;
}

void DTMFGenerator::frameToTones(string frame) {

	frameSize = frame.size();

	rawTones = new Int16[frameSize*samples];

	for (int i = 0; i < frame.size(); i++) {
		char hex = frame[i];

		hexToTone(hex);

		Int16* raw = new Int16[samples];

		double xincrement = freqX / (samples * (sampleRate / samples));
		double yincrement = freqY / (samples * (sampleRate / samples));

		for (int i = 0; i < samples; i++) {
			raw[i] = amplitude * (sin(x * twoPi) + sin(y * twoPi));
			x += xincrement;
			y += yincrement;
		}

		for (int j = 0; j < samples; j++) {
			rawTones[toneNum*samples + j] = raw[j];
		}
		toneNum++;

		delete[] raw;
	}
}

void DTMFGenerator::hexToTone(char hex) {
	switch (hex) {
	case '0':
		freqX = 1336.;
		freqY = 941.;
		break;
	case '1':
		freqX = 1209.;
		freqY = 697.;
		break;
	case '2':
		freqX = 1336.;
		freqY = 697.;
		break;
	case '3':
		freqX = 1477.;
		freqY = 697.;
		break;
	case '4':
		freqX = 1209.;
		freqY = 770.;
		break;
	case '5':
		freqX = 1336.;
		freqY = 770.;
		break;
	case '6':
		freqX = 1477.;
		freqY = 770.;
		break;
	case '7':
		freqX = 1209.;
		freqY = 852.;
		break;
	case '8':
		freqX = 1336.;
		freqY = 852.;
		break;
	case '9':
		freqX = 1477.;
		freqY = 852.;
		break;
	case 'A':
		freqX = 1633.;
		freqY = 697.;
		break;
	case 'B':
		freqX = 1633.;
		freqY = 770.;
		break;
	case 'C':
		freqX = 1633.;
		freqY = 852.;
		break;
	case 'D':
		freqX = 1633.;
		freqY = 941.;
		break;
	case 'E':
		freqX = 1477.;
		freqY = 941.;
		break;
	case 'F':
		freqX = 1209.;
		freqY = 941.;
		break;
	}

	cout << hex << " : " << freqX << " - " << freqY << endl;
}

void DTMFGenerator::play() {
	if (!buffer.loadFromSamples(rawTones, frameSize*samples, 1, sampleRate)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	sound.setBuffer(buffer);
	sound.play();
	sleep(milliseconds(((1000 / tonesPerSecond)*toneNum)));
}

double DTMFGenerator::getFreqX() {
	return freqX;
}

double DTMFGenerator::getFreqY() {
	return freqY;
}

DTMFGenerator::~DTMFGenerator() {}
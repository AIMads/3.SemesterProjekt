#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

#include "DTMFGenerator.h"
#include "Recorder.h"
#include <thread>
#include <mutex>

//mutex mtx;
using namespace std;
using namespace sf;

int main() {
	DTMFGenerator generator(10);
	//thread first(&DTMFGenerator::frameToTones, generator,"12345678901234567890");
	generator.frameToTones("0123456789ABCDEF");
	generator.play();

	Recorder recorder;

	recorder.start(8000);
	//first.join();
	//recorder.second.join();

	while (true) {
		sleep(seconds(1));
	}
	
	return 0;
}
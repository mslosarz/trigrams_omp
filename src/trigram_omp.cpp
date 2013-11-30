/*
 * trigram_omp.cpp
 *
 *  Created on: 29 lis 2013
 */

#include <iostream>
#include <vector>

#include "InMemoryFile.h"
#include "Timer.h"
#include "TrigramProcessor.h"

#include <fstream>

using namespace std;

int main(int argc, char **argv) {

	Timer timer;
	vector<string> files;
	files.push_back("/usr/share/dict/polish");

	cout << "Dictionary readed in: " << endl;
	timer.start();
	InMemoryFile inMemoryFile(files);
	timer.finish_and_print_duration();

	cout << "Cube created in: " << endl;
	timer.start();
	TrigramProcessor processor(inMemoryFile);
	timer.finish_and_print_duration();

	cout << "Trigrams calculated in: " << endl;
	timer.start();
	processor.calculate_trigrams();
	timer.finish_and_print_duration();

	cout << "Trigrams saved in: " << endl;
	timer.start();
	cout << processor;
	timer.finish_and_print_duration();
	return 0;
}


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

using namespace std;

int main(int argc, char **argv) {

	Timer timer;
	vector<string> files;
	files.push_back("/opt/PRiR/trigramy_omp/main.cpp");

	timer.start();
	InMemoryFile inMemoryFile(files);
	timer.finish_and_print_duration();

	timer.start();
	TrigramProcessor processor(inMemoryFile);
	timer.finish_and_print_duration();

	timer.start();
	processor.calculate_trigrams();
	timer.finish_and_print_duration();

	timer.start();
	cout << processor;
	timer.finish_and_print_duration();
	return 0;
}


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
#include "StatisticsFile.h"

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

	ofstream file;

	StatisticsFile statistic(processor);
	file.open("out");
	file << statistic;
	file.close();

	StatisticsFile stats;
	cout << "Reading trigrams from statistic file in: " << endl;
	ifstream infile;
	infile.open("out");
	infile >> stats;
	infile.close();

	cout << "Trigrams: " << stats.get_statistics().size() << endl;

	return 0;
}


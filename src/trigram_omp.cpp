/*
 * trigram_omp.cpp
 *
 *  Created on: 29 lis 2013
 */

#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>

#include "InMemoryFile.h"
#include "Timer.h"
#include "TrigramProcessor.h"
#include "StatisticsFile.h"
#include "LanguageMatcher.h"

using namespace std;

void create_statistics(int argc, char**argv) {
	if (argc < 4) {
		cout << argv[0] << " <thread_count> <lang> <file1> [<file2>... "
				<< endl;
		return;
	}
	int threadCount = atoi(argv[1]);

	string lang = string(argv[2]);
	vector<string> files;

	for (int i = 3; i < argc; i++) {
		files.push_back(string(argv[i]));
	}

	omp_set_num_threads(threadCount);

	Timer timer;

	InMemoryFile inMemoryFile(files);

	TrigramProcessor processor(inMemoryFile);

	timer.start();
	processor.calculate_trigrams();
	timer.finish_and_print_duration();

	ofstream file;
	StatisticsFile statistic(processor);
	file.open(lang.c_str());
	file << statistic;
	file.close();
}

bool sort_responses(MatcherResponse* i, MatcherResponse* j) {
	return (i->get_probability() > j->get_probability());
}

void recognize_lang(int argc, char**argv, vector<string>& known_langs) {
	if (argc < 2) {
		cout << argv[0] << " <thread_count> <file>" << endl;
		return;
	}

	vector<ifstream> knowledge_files(known_langs.size());
	vector<StatisticsFile> knowledge(knowledge_files.size());

	int threadCount = atoi(argv[1]);
	omp_set_num_threads(threadCount);

	for (unsigned int i = 0; i < knowledge_files.size(); i++) {
		knowledge_files[i].open(known_langs[i].c_str());
		knowledge_files[i] >> knowledge[i];
		knowledge[i].set_lang(known_langs[i]);
		knowledge_files[i].close();
	}

	vector<string> unknow_files = { argv[2] };
	StatisticsFile unknown;

	InMemoryFile in_memory(unknow_files);
	TrigramProcessor processor(in_memory);
	processor.calculate_trigrams();
	processor >> unknown;

	LanguageMatcher matcher(knowledge, unknown);
	Timer timer;

	timer.start();
	vector<MatcherResponse*>& matches = matcher.match_langs();
	timer.finish_and_print_duration();

	sort(matches.begin(), matches.end(), sort_responses);

	for (auto it = matches.begin(); it != matches.end(); ++it) {
		cout << (*it)->get_lang() << " ->: " << (*it)->get_probability() << endl;
	}

}

int main(int argc, char **argv) {
	if (argc > 3) {
		create_statistics(argc, argv);
	} else {
		vector<string> knowns_lang = { "pl", "fr", "en_GB", "chf" };
		recognize_lang(argc, argv, knowns_lang);
	}
	return 0;
}


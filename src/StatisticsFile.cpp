/*
 * StatisticsFile.cpp
 *
 *  Created on: 30 lis 2013
 */

#include <atomic>
#include <string>
#include <sstream>

#include "StatisticsFile.h"

StatisticsFile::StatisticsFile(string lang) :
		processor(NULL), lang(lang) {
	statistics = new vector<StatisticsItem*>();
}

StatisticsFile::StatisticsFile(TrigramProcessor& processor, string lang) :
		processor(&processor), lang(lang) {
	statistics = new vector<StatisticsItem*>();
}

vector<StatisticsItem*>& StatisticsFile::get_statistics() {
	return *statistics;
}

StatisticsFile::~StatisticsFile() {
	if (statistics != NULL) {
		for (auto it = statistics->begin(); it != statistics->end(); ++it) {
			delete *it;
		}
	}
	delete statistics;
	statistics = NULL;
}

ofstream & operator<<(ofstream &out, StatisticsFile &statistics) {
	if (statistics.is_writable()) {
		atomic<int>*** cube = statistics.get_cube();
		unsigned int cube_size = statistics.get_cube_size();
		int hit_number = statistics.get_hit_number();

		for (unsigned int i = 0; i < cube_size; i++) {
			for (unsigned int j = 0; j < cube_size; j++) {
				for (unsigned int k = 0; k < cube_size; k++) {
					atomic<int>& val = cube[i][j][k];
					if (val) {
						out << char(i) << char(j) << char(k) << '\t' << val
								<< '\t' << float(val) / hit_number << endl;
					}
				}
			}
		}
	}
	return out;
}

ifstream & operator >>(ifstream &in, StatisticsFile& statistics) {
	if (statistics.is_loaded() == false) {
		vector<StatisticsItem*>& results = statistics.get_statistics();
		string line;
		while (getline(in, line)) {
			StatisticsItem* item = new StatisticsItem();
			line >> (*item);
			results.push_back(item);
		}
	}
	return in;
}

TrigramProcessor& operator >>(TrigramProcessor &processor,
		StatisticsFile& statistics) {
	if (statistics.is_loaded() == false && statistics.is_writable() == false) {
		statistics.set_processor(&processor);
		vector<StatisticsItem*>& results = statistics.get_statistics();
		atomic<int>*** cube = processor.get_character_cube();
		unsigned int cube_size = processor.cube_size;
		int hit_number = processor.get_hit_number();

		for (unsigned int i = 0; i < cube_size; i++) {
			for (unsigned int j = 0; j < cube_size; j++) {
				for (unsigned int k = 0; k < cube_size; k++) {
					atomic<int>& val = cube[i][j][k];
					if (val) {
						StatisticsItem* item = new StatisticsItem();
						char t[4] = {char(i), char(j), char(k), 0};
						item->set_trigram(t);
						item->set_occurs(val);
						item->set_normalized(float(val) / hit_number);
						results.push_back(item);
					}
				}
			}
		}
	}
	return processor;
}

string & operator >>(string &in, StatisticsItem& item) {
	stringstream ss;
	char trigram[4] = {0};
	int occurs;
	float normalized;
	ss << in;
	ss >> trigram >> occurs >> normalized;
	item.set_trigram(trigram); item.set_occurs(occurs); item.set_normalized(normalized);
	return in;
}

/*
 * StatisticsFile.cpp
 *
 *  Created on: 30 lis 2013
 */

#include <atomic>
#include <string>

#include "StatisticsFile.h"

StatisticsFile::StatisticsFile() : processor(NULL) {
	statistics = new vector<StatisticsItem>();
}

StatisticsFile::StatisticsFile(TrigramProcessor& processor) : processor(&processor) {
	statistics = new vector<StatisticsItem>();
}

vector<StatisticsItem>& StatisticsFile::get_statistics(){
	return *statistics;
}

StatisticsFile::~StatisticsFile() {
	delete statistics;
	statistics = NULL;
}

fstream & operator<<(fstream &out, StatisticsFile &statistics) {
	if (statistics.is_writable()) {
		atomic<int>*** cube = statistics.get_cube();
		unsigned int cube_size = statistics.get_cube_size();
		int max_hit_number = statistics.get_max_hit_number();

		for (unsigned int i = 0; i < cube_size; i++) {
			for (unsigned int j = 0; j < cube_size; j++) {
				for (unsigned int k = 0; k < cube_size; k++) {
					atomic<int>& val = cube[i][j][k];
					if (val) {
						out << char(i) << char(j) << char(k) << '\t' << val
								<< '\t'
								<< float(val) / max_hit_number
								<< endl;
					}
				}
			}
		}
	}
	return out;
}

fstream & operator >>(fstream &in, StatisticsFile& statistics){
	if (statistics.is_loaded() == false) {
		vector<StatisticsItem> results = statistics.get_statistics();
		while(in.eof() == false){
			StatisticsItem item;
			in >> item;
			results.push_back(item);
		}
	}
	return in;
}

fstream & operator >>(fstream &in, StatisticsItem& item){
	string key;
	int occurs;
	float normalized;

	in >> key;
	in >> occurs;
	in >> normalized;

	item.set_key(key);
	item.set_occurs(occurs);
	item.set_normalized(normalized);
	return in;
}

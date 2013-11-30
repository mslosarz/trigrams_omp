/*
 * StatisticsFile.cpp
 *
 *  Created on: 30 lis 2013
 */

#include <atomic>
#include <string>
#include <sstream>

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

ofstream & operator<<(ofstream &out, StatisticsFile &statistics) {
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

ifstream & operator >> (ifstream &in, StatisticsFile& statistics){
	if (statistics.is_loaded() == false) {
		vector<StatisticsItem>& results = statistics.get_statistics();
		string line;
		while(getline(in, line)){
			StatisticsItem item;
			line >> item;
			results.push_back(item);
		}
	}
	return in;
}

string & operator >>(string &in, StatisticsItem& item){
	stringstream ss;
	ss << in;
	ss.read(&item.get_key()[0], 3);
	ss >> item.get_occurs() >> item.get_normalized();
	return in;
}

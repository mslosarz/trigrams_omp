/*
 * StatisticsFile.h
 *
 *  Created on: 30 lis 2013
 */

#include <fstream>
#include <atomic>

#include "TrigramProcessor.h"

#ifndef STATISTICSFILE_H_
#define STATISTICSFILE_H_

using namespace std;

class StatisticsItem;

class StatisticsFile {
public:
	StatisticsFile();
	StatisticsFile(TrigramProcessor& processor);

	friend ofstream & operator<<(ofstream &out, StatisticsFile &statistics);

	bool is_writable() {
		return processor != NULL;
	}

	bool is_loaded() {
		return statistics->size() > 0;
	}

	vector<StatisticsItem>& get_statistics();
	friend ifstream & operator >>(ifstream &in, StatisticsFile& statistics);

	atomic<int>*** get_cube() {
		return processor->get_character_cube();
	}

	unsigned int get_cube_size() {
		return processor->cube_size;
	}

	int get_max_hit_number() {
		return processor->get_max_hit_number();
	}

	~StatisticsFile();
private:
	vector<StatisticsItem>* statistics;
	TrigramProcessor* processor;
};

class StatisticsItem {
public:
	friend class StatisticsFile;

	StatisticsItem() :
			key(""), occurs(0), normalized(0.0f) {
		key.resize(4);
	}

	inline string &get_key() {
		return key;
	}
	inline int &get_occurs() {
		return occurs;
	}

	inline float &get_normalized() {
		return normalized;
	}

	inline void set_key(string key) {
		this->key = key;
	}

	inline void set_occurs(int occurs) {
		this->occurs = occurs;
	}

	inline void set_normalized(float normalized) {
		this->normalized = normalized;
	}

	~StatisticsItem() {
	}

	friend string & operator >>(string &in, StatisticsItem& item);
private:
	string key;
	int occurs;
	float normalized;
};

#endif /* STATISTICSFILE_H_ */

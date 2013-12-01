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
	StatisticsFile(string lang = "unknown");
	StatisticsFile(TrigramProcessor& processor, string lang = "unknown");

	friend ofstream & operator<<(ofstream &out, StatisticsFile &statistics);

	bool is_writable() {
		return processor != NULL;
	}

	bool is_loaded() {
		return statistics->size() > 0;
	}

	string get_lang() {
		return lang;
	}

	void set_lang(string lang) {
		this->lang = lang;
	}

	void set_processor(TrigramProcessor* processor) {
		if (processor != NULL) {
			this->processor = processor;
		}
	}

	vector<StatisticsItem*>& get_statistics();
	friend ifstream & operator >>(ifstream &in, StatisticsFile& statistics);
	friend TrigramProcessor& operator >>(TrigramProcessor&processor,
			StatisticsFile& statistics);

	atomic<int>*** get_cube() {
		return processor->get_character_cube();
	}

	unsigned int get_cube_size() {
		return processor->cube_size;
	}

	int get_hit_number() {
		return processor->get_hit_number();
	}

	~StatisticsFile();
private:
	vector<StatisticsItem*>* statistics;
	TrigramProcessor* processor;
	string lang;
};

class StatisticsItem {
public:
	friend class StatisticsFile;

	StatisticsItem() : occurs(0), normalized(0.0f) {
		key[3] = '\0';
	}

	inline void set_trigram(char t[4]){
		for(unsigned int i = 0; i < 4; i++){
			t[i] ? key[i] = t[i] : key[i] = ' ';
		}
	}

	inline char* get_trigram(){
		return key;
	}

	inline int get_occurs() {
		return occurs;
	}

	inline float get_normalized() {
		return normalized;
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
	char key[4];
	int occurs;
	float normalized;
};

#endif /* STATISTICSFILE_H_ */

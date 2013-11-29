/*
 * TrigramProcessor.h
 *
 *  Created on: 29 lis 2013
 */

#include <atomic>
#include <vector>

#include "InMemoryFile.h"

#ifndef TRIGRAMPROCESSOR_H_
#define TRIGRAMPROCESSOR_H_

class TrigramProcessor {
public:
	TrigramProcessor(const InMemoryFile& file);
	const unsigned int cube_size;
	void calculate_trigrams();

	inline atomic<int>*** get_character_cube() {
		return character_cube;
	}

	inline int get_max_hit_number(){
		return max_hit_number;
	}

	~TrigramProcessor();
private:
	friend ostream & operator<<(ostream &out, TrigramProcessor &processor);
	const InMemoryFile& file;
	int max_hit_number;

	atomic<int>*** character_cube;

	void createCube();
};

#endif /* TRIGRAMPROCESSOR_H_ */

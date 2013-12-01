/*
 * TrigramProcessor.cpp
 *
 *  Created on: 29 lis 2013
 */
#include <atomic>
#include <iostream>
#include <cstring>
#include <omp.h>

#include "TrigramProcessor.h"

TrigramProcessor::TrigramProcessor(const InMemoryFile& file) :
		cube_size(129), file(file), hit_number(0) {
	createCube();
}

void TrigramProcessor::calculate_trigrams() {

	unsigned int text_size = file.get_text_size();
	char* text = file.get_text();
	int thread_count = omp_get_max_threads();
	unsigned int hit = 0;
	#pragma omp parallel for reduction(+ : hit)
	for (unsigned int character = 0; character < text_size / 3; character++) {
		int index = character * 3;
		int i = int(text[index]);
		int j = int(text[index + 1]);
		int k = int(text[index + 2]);

		bool hasNoValue = (i == 0 || j == 0 || k == 0);
		bool containsOnlySpaces = i == ' ' && j == ' ' && k == ' ';

		if (hasNoValue || containsOnlySpaces) {
			continue;
		}
		character_cube[i][j][k]++;
		hit++;
	}
	hit_number = hit;

}

void TrigramProcessor::createCube() {
	character_cube = new atomic<int>**[cube_size];
	for (unsigned int i = 0; i < cube_size; i++) {
		character_cube[i] = new atomic<int>*[cube_size];
		for (unsigned int j = 0; j < cube_size; j++) {
			character_cube[i][j] = new atomic<int> [cube_size];
			for (unsigned int k = 0; k < cube_size; k++) {
				character_cube[i][j][k] = 0;
			}
		}
	}
}

TrigramProcessor::~TrigramProcessor() {
	if (character_cube != NULL)
		for (unsigned int i = 0; i < cube_size; i++) {
			for (unsigned int j = 0; j < cube_size; j++) {
				delete character_cube[i][j];
			}
			delete character_cube[i];
		}
	delete character_cube;
	character_cube = NULL;
}

ostream & operator<<(ostream &out, TrigramProcessor &processor) {
	std::atomic<int>*** character_cube = processor.get_character_cube();
	const unsigned int cube_size = processor.cube_size;
	int hit_number = processor.get_hit_number();
	for (unsigned int i = 0; i < cube_size; i++) {
		for (unsigned int j = 0; j < cube_size; j++) {
			for (unsigned int k = 0; k < cube_size; k++) {
				atomic<int>& val = character_cube[i][j][k];
				if (val) {
					out << char(i) << char(j) << char(k) << '\t' << val << '\t'
							<< float(val) / hit_number
							<< endl;
				}
			}
		}
	}
	return out;
}

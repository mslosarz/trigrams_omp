/*
 * InMemoryFile.cpp
 *
 *  Created on: 29 lis 2013
 */
#include <iostream>
#include <sstream>

#include "InMemoryFile.h"

InMemoryFile::InMemoryFile(const vector<string>& files_path) :
		text_size(0) {
	vector<ifstream> files(files_path.size());
	open_files(files_path, files);

	text_size = get_files_size(files);
	text_size += 1; // '\0'
	text = new char[text_size];
	text[text_size - 1] = '\0';

	read_files_content(files);
	close_files(files);
}

void InMemoryFile::open_files(const vector<string>& files_path,
		vector<ifstream>& files) {
	for (unsigned int i = 0; i < files_path.size(); i++) {
		files[i].open(files_path[i].c_str());
	}
}

unsigned int InMemoryFile::get_files_size(vector<ifstream>& files) {
	unsigned int files_size = 0;
	for (unsigned int i = 0; i < files.size(); i++) {
		files_size += file_size(files[i]);
	}
	return files_size;
}

void InMemoryFile::read_files_content(vector<ifstream>& files) {
	char* text_pointer = text;
	for (unsigned int i = 0; i < files.size(); i++) {
		while (files[i] >> (*text_pointer)) {
			(*text_pointer) = replace_unsupported(*text_pointer);
			text_pointer++;
		}
	}
}

void InMemoryFile::close_files(vector<ifstream>& files) {
	for (unsigned int i = 0; i < files.size(); i++) {
		files[i].close();
	}
}

unsigned int InMemoryFile::file_size(ifstream& file) {
	file.seekg(0, ios::end);
	unsigned int size = file.tellg();
	file.seekg(0, ios::beg);
	return size;
}

char InMemoryFile::replace_unsupported(char character) {
	bool isNotPrintable = character <= 31;
	bool fromExtendCharacterTable = 128 <= character;
	if (isNotPrintable || fromExtendCharacterTable) {
		return ' ';
	}
	return character;
}

InMemoryFile::~InMemoryFile() {
	delete text;
	text = NULL;
}


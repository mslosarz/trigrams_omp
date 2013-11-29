/*
 * InMemoryFile.h
 *
 *  Created on: 29 lis 2013
 */

#include <string>
#include <vector>
#include <fstream>

#ifndef INMEMORYFILE_H_
#define INMEMORYFILE_H_

using namespace std;

class InMemoryFile {
public:
	InMemoryFile(const vector<string>& files_to_read);
	~InMemoryFile();

	inline char* get_text() const {
		return text;
	}

	inline unsigned int get_text_size() const {
		return text_size;
	}
private:
	unsigned int file_size(ifstream& file);
	char replace_unsupported(char character);
	void open_files(const vector<string>& files_path, vector<ifstream>& files);
	unsigned int get_files_size(vector<ifstream>& files);
	void read_files_content(vector<ifstream>& files);
	void close_files(vector<ifstream>& files);

	char* text;
	unsigned int text_size;
};

#endif /* INMEMORYFILE_H_ */

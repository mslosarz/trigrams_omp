#include <unordered_map>
#include "TimeCalculator.h"
#include "FileInMemoryContainer.h"
#include "StatisticFile.h"

#include <string>

#ifndef TRIGRAMPROCESSOR_H
#define TRIGRAMPROCESSOR_H

using namespace std;

class TrigramProcessor
{
public:
    TrigramProcessor(FileInMemoryContainer& input_file, string lang, StatisticFile* output_file = NULL);
    unordered_map<string, int>* calculate_trigrams();
    void save_statistics_to_file();
    ~TrigramProcessor();
private:
    FileInMemoryContainer& _input_file;

    string _lang;

    StatisticFile* _output_file;

    unordered_map<string, int>* _trigrams;

    unordered_map<string, int>* merge(vector<unordered_map<string, int>>& thread_word);
};

#endif // TRIGRAMPROCESSOR_H

#include "TrigramProcessor.h"
#include "TimeCalculator.h"
#include <omp.h>

using namespace std;

TrigramProcessor::TrigramProcessor(FileInMemoryContainer& input_file, string& lang, StatisticFile& output_file) : _input_file(input_file), _lang(lang), _output_file(output_file)
{
}

TrigramProcessor::~TrigramProcessor()
{
    delete _trigrams;
    _trigrams = NULL;
}

void TrigramProcessor::calculate_trigrams()
{
    unsigned char* text = _input_file.text();
    int text_size = _input_file.text_size();
    vector<unordered_map<string, int>> threads_words(omp_get_max_threads());
    #pragma omp parallel for
    for(int i = 0; i < text_size/3; i++)
    {
        unordered_map<string, int>& local_words = threads_words[omp_get_thread_num()];
        string trigram((const char*)text, 3*i, 3);
        local_words[trigram]++;
    }
    _trigrams = merge(threads_words);
}

unordered_map<string, int>* TrigramProcessor::merge(vector<unordered_map<string, int>>& threads_words)
{
    int thread_num = omp_get_max_threads();
    unordered_map<string, int>* result = new unordered_map<string, int>();
    for(int i = 0; i < thread_num; i++)
    {
        unordered_map<string, int>& thread_words = threads_words[i];
        for (auto it = thread_words.begin(); it != thread_words.end(); ++it )
        {
            (*result)[it->first] += it->second;
        }
    }
    return result;
}

void TrigramProcessor::save_statistics_to_file()
{
    _output_file.write(*_trigrams, _lang);
}

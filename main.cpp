#include <iostream>
#include <omp.h>
#include <string>
#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

#include "TimeCalculator.h"
#include "FileInMemoryContainer.h"
#include "TrigramProcessor.h"
#include "StatisticFile.h"
#include "LanguageMatcher.h"

#include <unordered_map>

using namespace std;

TimeCalculator timer;

bool matcher_response_comparator (MatcherResponse* i,MatcherResponse* j) { return (i->percent()<j->percent()); }

int main(int argc, char *argv[])
{
    srand(time(NULL));


//    if(argc < 4)
//    {
//        cout << argv[0] << " <thread_count> <lang> <file1> [<file2>... " << endl;
//        return -1;
//    }
//    int threadCount = atoi(argv[1]);
//
//    string lang = string(argv[2]);
//    vector<string> files;
//
//    for(int i = 3; i < argc; i++)
//    {
//        files.push_back(string(argv[i]));
//    }
//
//    omp_set_num_threads(threadCount);
//
//    FileInMemoryContainer input_files(&files);
//    StatisticFile output_file;
//
//    TrigramProcessor processor(input_files, lang, output_file);
//
//    timer.start();
//    processor.calculate_trigrams();
//    timer.finish();
//    timer.printDuration();
//
//    processor.save_statistics_to_file();

    vector<string> files;
    files.push_back("./test_file");
    FileInMemoryContainer file_under_analize(&files);

    TrigramProcessor trigram_processor(file_under_analize, "unknown");
    unordered_map<string, int>* unknow_trigrams = trigram_processor.calculate_trigrams();

    cout << "unknow_trigrams.size() " << unknow_trigrams->size() << endl;

    vector<unordered_map<string, int>*> dictionaries;
    StatisticFile statistic_file;
    dictionaries.push_back(statistic_file.read("spanish"));
    dictionaries.push_back(statistic_file.read("british-english"));
    dictionaries.push_back(statistic_file.read("french"));

    cout << "dictionaries.size() " << dictionaries.size() << endl;

    vector<LanguageMatcher*> matchers;

    matchers.push_back(new LanguageMatcher("sp", dictionaries[0]));
    matchers.push_back(new LanguageMatcher("en-GB", dictionaries[1]));
    matchers.push_back(new LanguageMatcher("fr", dictionaries[2]));

    vector<MatcherResponse*> responses;

    for(unsigned int i = 0; i < matchers.size(); i++){
        responses.push_back(matchers[i]->matchLanguage(unknow_trigrams));
    }

    sort(responses.begin(), responses.end(), matcher_response_comparator);
    for(unsigned int i = 0; i < responses.size(); i++){
        cout << responses[i]->lang() << "\t->\t" << responses[i]->percent() << endl;
    }

    return 0;
}

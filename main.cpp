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


    if(argc < 4)
    {
        cout << argv[0] << " <thread_count> <lang> <file1> [<file2>... " << endl;
        return -1;
    }
    int threadCount = atoi(argv[1]);

    string lang = string(argv[2]);
    vector<string> files;

    for(int i = 3; i < argc; i++)
    {
        files.push_back(string(argv[i]));
    }

    omp_set_num_threads(threadCount);

    FileInMemoryContainer input_files(&files);
    StatisticFile output_file;

    TrigramProcessor processor(input_files, lang, &output_file);

    timer.start();
    processor.calculate_trigrams();
    timer.finish();
    timer.printDuration();

    processor.save_statistics_to_file();

    return 0;
}

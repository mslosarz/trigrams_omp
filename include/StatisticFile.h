#include<string>
#include<unordered_map>

#ifndef STATISTICFILE_H
#define STATISTICFILE_H

using namespace std;

class StatisticFile
{
public:
    StatisticFile(string path = "./", string extension = ".dat");
    unordered_map<string, int>* read(string file_name);
    void write(unordered_map<string, int>& statistics, string file_name = "out");
    unordered_map<string, int>* statistics()
    {
        return _statistics;
    }
private:
    string _path;
    string _extension;
    unordered_map<string, int>* _statistics;
};

#endif // STATISTICFILE_H

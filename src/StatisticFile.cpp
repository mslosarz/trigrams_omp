#include "StatisticFile.h"
#include <iostream>
#include <fstream>
#include <sstream>

StatisticFile::StatisticFile(string path, string extension) : _path(path), _extension(extension), _statistics(NULL)
{}

unordered_map<string, int>* StatisticFile::read(string file_name)
{
    string read_from = _path + file_name + ".dat";
    ifstream file;
    file.open(read_from);
    _statistics = new unordered_map<string, int>();
    string line;
    while(getline(file, line))
    {
        stringstream stream(line);
        string key;
        int value;
        stream >> key;
        stream >> value;
        (*_statistics)[key] = value;
    }
    file.close();
    return _statistics;
}

void StatisticFile::write(unordered_map<string, int>& statistics, string file_name)
{
    string write_to = _path + file_name + ".dat";
    ofstream file;
    file.open(write_to);
    for (auto it = statistics.begin(); it != statistics.end(); ++it )
    {
        file << it->first << "\t" << it->second << endl;
    }
    file.close();
}

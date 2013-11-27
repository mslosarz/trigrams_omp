#include "StatisticFile.h"
#include <iostream>
#include <fstream>

StatisticFile::StatisticFile(string path, string extension) : _path(path), _extension(extension)
{}

StatisticFile::~StatisticFile()
{
}

unordered_map<string, int>* StatisticFile::read(string& file_name)
{
    string read_from = _path + file_name + ".dat";
    ifstream file;
    file.open(read_from);
    unordered_map<string, int>* statistics = new unordered_map<string, int>();

    while(file.eof() == false){
        string key;
        int value;
        file >> key;
        file >> value;
        (*statistics)[key] = value;
    }
    file.close();
    return statistics;
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

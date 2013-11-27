#include "FileInMemoryContainer.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

FileInMemoryContainer::FileInMemoryContainer(vector<string> *files_paths) : _text(NULL), _text_size(0)
{
    vector<FileInfo*>* files = open_all(files_paths);

    get_size_of(files);

    read_content_to_memory_from(files);

    close_all(files);
}

vector<FileInfo*>* FileInMemoryContainer::open_all(vector<string>* files_paths)
{
    vector<FileInfo*>* files = new vector<FileInfo*>();
    int files_count = files_paths->size();
    for(int i = 0; i < files_count; i++)
    {
        int file_descriptor = open((char const*) (*files_paths)[i].c_str(), O_RDONLY);
        if(file_descriptor < 0)
        {
            throw string("File " + (*files_paths)[i] + " not found");
        }
        files->push_back(new FileInfo(file_descriptor));
    }
    return files;
}

vector<FileInfo*>* FileInMemoryContainer::get_size_of(vector<FileInfo*>* files)
{
    for(unsigned int i = 0; i<files->size(); i++)
    {

        int file_size = lseek((*files)[i]->descriptor(), 0, SEEK_END);
        (*files)[i]->set_size(file_size);

        _text_size += file_size;

        lseek((*files)[i]->descriptor(), 0, SEEK_SET);
    }
    return files;
}


void FileInMemoryContainer::read_content_to_memory_from(vector<FileInfo*>* files)
{
    _text = new unsigned char[_text_size];
    unsigned char* pointer = _text;
    for(unsigned int i = 0; i < files->size(); i++)
    {
        read((*files)[i]->descriptor(), pointer, (*files)[i]->size());
        pointer += (*files)[i]->size();
    }
    for(int i = 0; i < _text_size; i++)
    {
        if(_text[i] == '\n')
        {
            _text[i] = ' ';
        }
    }
}

void FileInMemoryContainer::close_all(vector<FileInfo*>* files)
{
    for(unsigned int i = 0; i< files->size(); i++)
    {
        close((*files)[i]->descriptor());
    }
}

FileInMemoryContainer::~FileInMemoryContainer()
{
    delete _text;
    _text = NULL;
}


#include <string>
#include <vector>

#ifndef FILEINMEMORYCONTAINER_H
#define FILEINMEMORYCONTAINER_H

using namespace std;

class FileInfo;

class FileInMemoryContainer
{
public:
    FileInMemoryContainer(vector<string> *files_paths);

    virtual ~FileInMemoryContainer();

    unsigned char* text()
    {
        return _text;
    }

    int text_size()
    {
        return _text_size;
    }

private:
    unsigned char* _text;

    int _text_size;

    vector<FileInfo*>* open_all(vector<string>* files_paths);

    vector<FileInfo*>* get_size_of(vector<FileInfo*>* files);

    void read_content_to_memory_from(vector<FileInfo*>* files);

    void close_all(vector<FileInfo*>* files);
};


class FileInfo
{
    friend class FileInMemoryContainer;
public:

    int descriptor()
    {
        return _descriptor;
    }

    int size()
    {
        return _size;
    }

    void set_size(int size)
    {
        _size = size;
    }

private:
    FileInfo(int descriptor): _descriptor(descriptor), _size(0) {}

    int _descriptor;
    int _size;
};
#endif // FILEINMEMORYCONTAINER_H

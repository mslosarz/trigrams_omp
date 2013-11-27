#include "LanguageMatcher.h"
#include <vector>
#include <iostream>

LanguageMatcher::LanguageMatcher(string lang, unordered_map<string, int>* statistics):
    _lang(lang), _lang_statistics(statistics)
{
}

LanguageMatcher::~LanguageMatcher()
{
    delete _response;
    _response = NULL;
}

MatcherResponse* LanguageMatcher::matchLanguage(unordered_map<string, int>* file_statistics)
{
    float percent = 0;
    vector<string> common_key;

    for(auto it = file_statistics->begin(); it != file_statistics->end(); ++it)
    {
        if((*_lang_statistics)[it->first])
        {
            common_key.push_back(it->first);
        }
    }
    _response = new MatcherResponse(_lang, percent);
    return _response;
}

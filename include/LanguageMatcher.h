#include "MatcherResponse.h"
#include <vector>
#include <string>
#include <unordered_map>

#ifndef LANGUAGEMATCHER_H
#define LANGUAGEMATCHER_H


class LanguageMatcher
{
public:
    LanguageMatcher(string lang, unordered_map<string, int>* lang_statistics);
    MatcherResponse* matchLanguage(unordered_map<string, int>* file_statistics);
    ~LanguageMatcher();
private:
    string _lang;
    unordered_map<string, int>* _lang_statistics;
    MatcherResponse* _response;

};

#endif // LANGUAGEMATCHER_H

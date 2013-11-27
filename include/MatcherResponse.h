#include <string>

#ifndef MATCHERRESPONSE_H
#define MATCHERRESPONSE_H

using namespace std;

class MatcherResponse
{
public:
    MatcherResponse(string lang, float percent) : _lang(lang), _percent(percent) {}
    float percent()
    {
        return _percent;
    }
    string lang()
    {
        return _lang;
    }
private:
    string _lang;
    float _percent;
};

#endif // MATCHERRESPONSE_H

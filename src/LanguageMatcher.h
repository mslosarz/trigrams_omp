/*
 * LanguageMatcher.h
 *
 *  Created on: 30 lis 2013
 */

#include <vector>

#include "StatisticsFile.h"

#ifndef LANGUAGEMATCHER_H_
#define LANGUAGEMATCHER_H_

using namespace std;

class MatcherResponse;

class LanguageMatcher {
public:
	LanguageMatcher(vector<StatisticsFile>& known_langs, StatisticsFile& unknown_lang);
	vector<MatcherResponse*>& match_langs();
	~LanguageMatcher();
private:
	vector<StatisticsFile>& known_langs;
	StatisticsFile& unknown_lang;
	vector<MatcherResponse*>* response;
};

class MatcherResponse {
public:
	MatcherResponse(string lang) : lang(lang), probability(.0f){
	}

	~MatcherResponse(){
	}

	string& get_lang(){
		return lang;
	}

	float& get_probability(){
		return probability;
	}

private:
	string lang;
	float probability;

};

#endif /* LANGUAGEMATCHER_H_ */

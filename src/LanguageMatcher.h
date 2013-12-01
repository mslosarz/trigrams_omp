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
	MatcherResponse* match(StatisticsFile& known_lang, StatisticsFile& unknown_lang);
	vector<pair<int, int> > merge(vector<vector<pair<int, int> > >& partial_result);

	vector<StatisticsFile>& known_langs;
	StatisticsFile& unknown_lang;
	vector<MatcherResponse*>* response;
};

class MatcherResponse {
public:
	MatcherResponse(string lang, float probability = 0.0f) : lang(lang), probability(probability){
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

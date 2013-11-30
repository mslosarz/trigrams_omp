/*
 * LanguageMatcher.cpp
 *
 *  Created on: 30 lis 2013
 */

#include "LanguageMatcher.h"

LanguageMatcher::LanguageMatcher(vector<StatisticsFile>& known_langs,
		StatisticsFile& unknown_lang) :
		known_langs(known_langs), unknown_lang(unknown_lang) {
	response = new vector<MatcherResponse*>();
}

vector<MatcherResponse*>& LanguageMatcher::match_langs(){

	return *response;
}

LanguageMatcher::~LanguageMatcher() {
	if(response != NULL){
		for(auto it = response->begin(); it != response->end(); ++it){
			delete *it;
		}
	}
	delete response;
	response = NULL;
}


/*
 * LanguageMatcher.cpp
 *
 *  Created on: 30 lis 2013
 */

#include <omp.h>

#include "LanguageMatcher.h"

LanguageMatcher::LanguageMatcher(vector<StatisticsFile>& known_langs,
		StatisticsFile& unknown_lang) :
		known_langs(known_langs), unknown_lang(unknown_lang) {
	response = new vector<MatcherResponse*>();
}

vector<pair<int, int> > LanguageMatcher::merge(vector<vector<pair<int, int> > >& partial_result) {
	vector<pair<int, int> > result;
	for (unsigned int i = 0; i < partial_result.size(); i++) {
		for (unsigned int j = 0; j < partial_result[i].size(); j++) {
			result.push_back(partial_result[i][j]);
		}
	}
	return result;
}

MatcherResponse* LanguageMatcher::match(StatisticsFile& known_lang,
		StatisticsFile& unknown_lang) {
	vector<StatisticsItem*>& known_stats = known_lang.get_statistics();
	vector<StatisticsItem*>& unknown_stats = unknown_lang.get_statistics();

	vector<vector<pair<int, int> > > partial_result(omp_get_max_threads());
	unsigned int known_size = known_stats.size();
	unsigned int unknown_size = unknown_stats.size();

#pragma omp parallel for
	for (unsigned int i = 0; i < known_size; i++) {
		char *kt = known_stats[i]->get_trigram();
		for (unsigned int j = 0; j < unknown_size; j++) {
			char* ut = unknown_stats[j]->get_trigram();
			if(kt[0] == ut[0] && kt[1] == ut[0] && kt[2] == ut[2]){
				pair<int, int> p(i, j);
				partial_result[omp_get_thread_num()].push_back(p);
			}
		}
	}

	vector<pair<int, int> > result = merge(partial_result);

	float global_error = .0f;
#pragma omp parallel for reduction(+ : global_error)
	for (unsigned int i = 0; i < partial_result.size(); i++) {
		pair<int, int> index = result[i];
		float error = known_stats[index.first]->get_normalized()
				- unknown_stats[result[i].second]->get_normalized();
		error *= error;
		global_error += error;
	}
	return new MatcherResponse(known_lang.get_lang(), 1 - global_error);
}

vector<MatcherResponse*>& LanguageMatcher::match_langs() {
	for (unsigned int i = 0; i < known_langs.size(); i++){
		response->push_back(match(known_langs[i], unknown_lang));
	}
	return *response;
}

LanguageMatcher::~LanguageMatcher() {
	if (response != NULL) {
		for (auto it = response->begin(); it != response->end(); ++it) {
			delete *it;
		}
	}
	delete response;
	response = NULL;
}


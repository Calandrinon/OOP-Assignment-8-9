#pragma once
#include <iostream>
#include <vector>
#include "repository.h"
#include "recording.h"
using namespace std;

class Service {
	private:
		Repository* repository;
		Repository* watch_list;

	public:
		Service(Repository*);
		vector<string> tokenize(string line, char delimiter);
		string strip(string str);
		void validate_location(string location);
		void validate_time_of_creation(string time_of_creation);
		void validate_times_accessed(string times_accessed);		
		void add(string title, string location, string timeOfCreation, string timesAccessed, string footagePreview);
		void remove(string title);
		bool search(string title);
		string next();
		void save();
		vector<Recording> get_watchlist();
		void update(string title, string location, string time_of_creation, string times_accessed, string footage_preview);
		vector<Recording> get_repository_container();
		~Service();
};

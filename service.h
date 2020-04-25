#pragma once
#include <iostream>
#include <vector>
#include "repository.h"
#include "recording.h"
#include "validator.h"
using namespace std;

class Service {
	private:
		MemoryRepository* repository;
		FileRepository* file_repository;
		Validator validator;
		bool has_file_repository;

	public:
		Service(Repository*);
		void add(string title, string location, string timeOfCreation, string timesAccessed, string footagePreview);
		void remove(string title);
		bool search(string title);
		string next();
		void save();
		vector<Recording> get_watchlist();
		void update(string title, string location, string time_of_creation, string times_accessed, string footage_preview);
		vector<Recording> get_repository_container();
		bool does_service_have_file_repository();
		string get_file_repository_filename();
		void set_file_repository_filename(string new_filename);
        void set_watchlist_filename(string file_path);
		~Service();
};

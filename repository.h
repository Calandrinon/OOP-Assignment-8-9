#pragma once
#include <iostream>
#include <vector>
#include "dynamicvector.h"
#include "recording.h"
using namespace std;

class Repository {
	private:
		vector<Recording> container;
		vector<Recording> watch_list;
		int selected_recording;

	public:
		Repository();
		void add(Recording r);
		vector<Recording> get_container();
		void remove(string title);
		string next();
		void save();
		vector<Recording> get_watchlist();
		bool search(string title);
		~Repository();
};

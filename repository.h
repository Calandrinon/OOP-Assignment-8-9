#pragma once
#include <iostream>
#include <vector>
#include "dynamicvector.h"
#include "recording.h"
using namespace std;

class Repository {
	private:
		DynamicVector<Recording> container;	
	
	public:
		Repository();
		void add(Recording r);
		vector<Recording> get_container();
		void remove(string title);
		bool search(string title);
		~Repository();
};

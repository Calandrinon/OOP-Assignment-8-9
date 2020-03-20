#pragma once
#include <iostream>
#include <vector>
#include "dynamicvector.h"
#include "recording.h"
using namespace std;

class Repository {
	private:
		//DynamicVector<Recording> vector;	
		vector<Recording> container;
	
	public:
		Repository();
		void add(Recording r);
		//DynamicVector<Recording> get_container();
		vector<Recording> get_container();
		~Repository();
};

#pragma once
#include <iostream>
#include <vector>
#include "repository.h"

class Service {
	private:
		Repository* repository;

	public:
		Service(Repository*);
		std::vector<std::string> tokenize(std::string line, char delimiter);
		std::string strip(std::string str);
};

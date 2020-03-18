#include "service.h"
#include <sstream>
using namespace std;

Service::Service(Repository* repository) {
	this->repository = repository;
}


std::vector<std::string> Service::tokenize(std::string line, char delimiter) {
	vector<string> tokens;

	stringstream stream(line);
	string token;

	while(getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}


std::string Service::strip(std::string str) {
	while (str[0] == ' ' || str[0] == '\n')
		str.erase(0,1);

	while (str[str.size()-1] == ' ' || str[str.size()-1] == '\n')
		str.erase(str.size()-1,1);

	return str;
}

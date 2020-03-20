#include "service.h"
#include <sstream>
#include "myexceptions.h"
#include "recording.h"
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


void Service::validate_location(string location) {
	vector<string> tokens = tokenize(location, ' ');

	if (tokens[0] != "deck" || tokens[2] != "sector") {
		CommandFormatException command_format_exception;
		throw command_format_exception;
	}
}



void Service::validate_time_of_creation(string time_of_creation) {
	vector<string> tokens = tokenize(time_of_creation, '-');

	if (tokens.size() != 3) {
		CommandFormatException command_format_exception;
		throw command_format_exception; 
	}

	int month = stoi(tokens[0]);
	int day = stoi(tokens[1]);
	int year = stoi(tokens[2]);
	//Conversion is not necessary but for validating the date(reassuring the fact that
	//the date is a series of numbers) it is useful because it throws exceptions.
}


void Service::validate_times_accessed(string times_accessed) {
	int times = stoi(times_accessed);
}


void Service::add(string title, string location, string time_of_creation, string times_accessed, string footage_preview) {
	validate_location(location);
	validate_time_of_creation(time_of_creation);
	validate_times_accessed(times_accessed);

	Recording recording(title, location, time_of_creation, stoi(times_accessed), footage_preview); 	
	repository->add(recording);
}


vector<Recording> Service::get_repository_container() {
	return repository->get_container();
}
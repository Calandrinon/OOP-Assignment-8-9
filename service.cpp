#include "service.h"
#include <sstream>
#include "myexceptions.h"
#include "recording.h"
#include "dynamicvector.h"
using namespace std;

Service::Service(Repository* repository) {
	this->repository = repository;
	this->watch_list = new Repository();
}


DynamicVector<std::string> Service::tokenize(std::string line, char delimiter) {
	/**
	 * 
	 * Splits a string into tokens by using a delimiter and returns them in a DynamicVector
	 * 
	 * Input:
	 * 		- line: string
	 * 		- delimiter: character
	 * 
	 * Output:
	 * 		- tokens: DynamicVector
	 **/
	DynamicVector<string> tokens;

	stringstream stream(line);
	string token;

	while(getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}


std::string Service::strip(std::string str) {
	/**
	 * 
	 * Removes all trailing whitespaces and newline characters.
	 * 
	 * Input:
	 * 		- str: the string
	 * 
	 * Output:
	 * 		- str: the string after its trailing whitespaces and \n characters have been removed. 
	 * **/
	while (str[0] == ' ' || str[0] == '\n')
		str.erase(0,1);

	while (str[str.size()-1] == ' ' || str[str.size()-1] == '\n')
		str.erase(str.size()-1,1);

	return str;
}


void Service::validate_time_of_creation(string time_of_creation) {
	/**
	 * 
	 * Validates a date given as a string
	 * The date should look like this: 01-01-2000
	 * 
	 * Input:
	 * 		- time_of_creation: a date given as a string
	 **/
	DynamicVector<string> tokens = tokenize(time_of_creation, '-');

	if (tokens.size() != 3) {
		CommandFormatException command_format_exception("Incorrect time of creation format!\n");
		throw command_format_exception; 
	}

	int month = stoi(tokens[0]);
	int day = stoi(tokens[1]);
	int year = stoi(tokens[2]);

	if (month < 1 || month > 12 || day < 1 || day > 31) {
		CommandFormatException command_format_exception("Incorrect date!\n");
		throw command_format_exception; 
	} 

	tokens.free();
	//Conversion is not necessary but for validating the date(reassuring the fact that
	//the date is a series of numbers) it is useful because it throws an invalid_argument
	//exception in case the date string is just formed of letters.
}


void Service::validate_times_accessed(string times_accessed) {
	/**
	 * Validates the times_accessed parameter
	 * 
	 * Input:
	 * 		- times_accessed: a string
	 **/
	int times = stoi(times_accessed);
}


void Service::add(string title, string location, string time_of_creation, string times_accessed, string footage_preview) {
	/**
	 * 
	 * Adds a new recording to the repository.
	 * 
	 * Input:
	 * 		- title, location, time_of_creation, times_accessed, footage_preview: strings
	 **/
	validate_time_of_creation(time_of_creation);
	validate_times_accessed(times_accessed);

	Recording recording(title, location, time_of_creation, stoi(times_accessed), footage_preview); 	
	repository->add(recording);
}


DynamicVector<Recording> Service::get_repository_container() {
	/**
	 * Gets the contents of the custom-made DynamicVector from the repository.
	 * 
	 **/
	return repository->get_container();
}


bool Service::search(string title) {
	return repository->search(title);
}


void Service::remove(string title) {
	/**
	 * 
	 * Removes a recording from the repository by its title.
	 * 
	 * Input:
	 * 		- title: string
	 **/
		
	repository->remove(title);
}


void Service::update(string title, string location, string time_of_creation, string times_accessed, string footage_preview) {
	/**
	 * 
	 * Updates the details of a recording in the repository.
	 * In case the recording with the specified title does not exist, the method throws
	 * a RepositoryException.
	 * 
	 * Input:
	 * 		- title, location, time_of_creation, times_accessed, footage_preview: strings
	 * Throws:
	 * 		- RepositoryException: in case the recording with the given title doesn't exist
	 **/
	validate_time_of_creation(time_of_creation);
	validate_times_accessed(times_accessed);

	if (!repository->search(title)) {
		RepositoryException re("RepositoryException: The element cannot be updated because it doesn't exist!\n");
		throw re;
	}
	
	repository->remove(title);
	Recording recording(title, location, time_of_creation, stoi(times_accessed), footage_preview); 	
	repository->add(recording);
}


void Service::next() {
	repository->next();
}


Service::~Service() {
	delete watch_list;
}
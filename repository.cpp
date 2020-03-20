#include "repository.h"

Repository::Repository() {

}


void Repository::add(Recording r) {
	container.push_back(r);
}


vector<Recording> Repository::get_container() {
	return container;
}


Repository::~Repository() {
	//container.free_vector();
}

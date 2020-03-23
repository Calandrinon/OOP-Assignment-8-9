#include "repository.h"

Repository::Repository() {

}


void Repository::add(Recording r) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i].get_title() == r.get_title()) {
			cout << "Can't add duplicate elements!\n";
			return;
		}
	}

	container.push_back(r);
}


vector<Recording> Repository::get_container() {
	vector<Recording> vector_container;

	for (int i = 0; i < container.size(); i++) {
		vector_container.push_back(container[i]);
	}

	return vector_container;
}


void Repository::remove(string title) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i].get_title() == title) {
			container.remove(i, 1);
			return;
		}
	}
}


Repository::~Repository() {
	//container.free_vector();
}


bool Repository::search(string title) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i].get_title() == title) {
			return true;
		}
	}

	return false;
}

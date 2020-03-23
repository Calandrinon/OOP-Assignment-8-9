#include "repository.h"
#include "dynamicvector.h"

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


DynamicVector<Recording> Repository::get_container() {
	return container;
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
	container.free();
}


bool Repository::search(string title) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i].get_title() == title) {
			return true;
		}
	}

	return false;
}

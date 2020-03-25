#include "repository.h"
#include "dynamicvector.h"
#include "myexceptions.h"

Repository::Repository() {
	selected_recording = 0;
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
	watch_list.free();
}


bool Repository::search(string title) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i].get_title() == title) {
			return true;
		}
	}

	return false;
}


string Repository::next() {
	if (selected_recording + 1 < container.size()) {
		selected_recording++;
	} else {
		selected_recording = 0;
	}

	return container[selected_recording].get_as_string();	
}


void Repository::save() {
	if (selected_recording >= container.size()) {
		IndexError ie("IndexError: You haven't added any recordings!\n");
		throw ie;
	}
	watch_list.push_back(container[selected_recording]);
}


DynamicVector<Recording> Repository::get_watchlist() {
	return watch_list;
}
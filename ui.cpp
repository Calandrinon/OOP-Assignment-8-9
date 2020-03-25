#include "ui.h"
#include <string>
#include <exception>
#include "myexceptions.h"
#include "dynamicvector.h"
using namespace std;

UI::UI(Service* service) {
	running = true;
	this->service = service;
	this->security_clearance_mode = 'A';
}


void UI::exit() {
	running = false;
}


DynamicVector<string> UI::tokenize(string line, char delimiter) {
	return service->tokenize(line, delimiter);
}


string UI::get_command_name(string full_command) {
	DynamicVector<string> tokens = tokenize(full_command, ' ');

	if (tokens.size() == 0) {
		tokens.free();
		return "-1";
	}

	string command_name = tokens[0];
	tokens.free();
	return command_name; 
}


void UI::add() {
	DynamicVector<string> tokens = tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command add takes 5 parameters: add title, location, timeOfCreation, timesAccessed, footagePreview\n";
		tokens.free();	
		return;
	}

	for (int i = 0; i < tokens.size(); i++) 
		tokens[i] = service->strip(tokens[i]);

	tokens[0].erase(0, 4);  // the title without the 'add' command name
	service->add(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
	tokens.free();
}


void UI::list() {
	DynamicVector<Recording> container = service->get_repository_container();

	for (int i = 0; i < container.size(); i++) {
		cout << container[i].get_as_string() << "\n";
	}
}


void UI::remove() {
	DynamicVector<string> tokens = tokenize(this->last_command, ' ');

	if (!service->search(tokens[1])) {
		cout << "The element doesn't exist!\n";
		tokens.free();
		return;
	}

	string title = tokens[1];
	service->remove(title);

	tokens.free();
}


void UI::update() {
	DynamicVector<string> tokens = service->tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command update takes 5 parameters: add title, new_location, new_timeOfCreation, new_timesAccessed, new_footagePreview\n";
		tokens.free();
		return;
	}

	for (int i = 0; i < tokens.size(); i++) 
		tokens[i] = service->strip(tokens[i]);

	tokens[0].erase(0, 7);  // the title without the 'add' command name

	if (!service->search(tokens[0])) {
		cout << "The element doesn't exist!\n";
		tokens.free();
		return;
	}

	service->update(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);	

	tokens.free();
}


void UI::change_mode() {
	DynamicVector<string> tokens = tokenize(this->last_command, ' ');

	if (tokens.size() != 2 || tokens[1].size() > 1 || !(tokens[1][0] == 'A' || tokens[1][0] == 'B')) {
		cout << "The command mode takes only one parameter with the values A or B!\n";
		tokens.free();
		return;
	}

	this->security_clearance_mode = tokens[1][0];
	tokens.free();
}


void UI::help() {
	cout << "\nAvailable commands:\n";
	cout << " - mode X (e.g. mode A) Note: mode B is the user mode without admin permissions, which permits only the \"list\" and \"exit\" commands.\n"
    " - add title, location, timeOfCreation, timesAccessed, footagePreview (eg. add anomaly, deck D sector X1423, 01-13-3248, 5, prev123.mp15)\n"
    " - update title, newLocation, newTimeOfCreation, newTimesAccessed, newFootagePreview (eg. update anomaly, deck E sector X1423, 01-14-3248, 14, prev124.mp15)\n"
    " - delete title (eg. delete anomaly)\n"
    " - list\n"
	" - help\n"
    " - exit\n\n";
}


void UI::next() {
	service->next();
}


void UI::save() {
	service->save();
} 


void UI::mylist() {
	DynamicVector<Recording> watch_list = service->get_watchlist();

	for (int i = 0; i < watch_list.size(); i++) {
		cout << watch_list[i].get_as_string() << "\n";
	}
}


void UI::run() {
	string commands[] = {"exit", "add", "list", "delete", "update", "mode", "help", "next", "save", "mylist"};
	string permissions[] = {"all", "admin", "all", "admin", "admin", "admin", "all", "all", "all", "all"};
	void (UI::*func[])() = {&UI::exit, &UI::add, &UI::list, &UI::remove, &UI::update, &UI::change_mode, &UI::help, &UI::next, &UI::save, &UI::mylist};
	int number_of_commands = sizeof(commands)/sizeof(commands[0]);
	string command;

	//service->add("anomaly", "deck D sector x1423", "01-10-2000", "5", "prev123.mp4");
	//service->add("anomaly2", "deck E sector x20", "01-10-2000", "2", "prev124.mp4");
	//service->add("anomaly3", "deck F sector x1422", "02-10-2000", "3", "prev125.mp4");

	help();	

	while (running) {
		cout << ">>";
		getline(cin, command);

		this->last_command = command;	
		bool command_found = false;
		string command_name = get_command_name(command);

		for (int i = 0; i < number_of_commands && !command_found; i++) {
			if (commands[i] == command_name) {
				command_found = true;
				if (security_clearance_mode == 'B' && permissions[i] == "admin") {
					cout << "Permission denied!\n";
					continue;
				}

				try {
					(this->*func[i])();
				} catch (CommandFormatException cfe) {
					cout << cfe.message;
				} catch(invalid_argument ie) {
					cout << "InvalidArgumentException: stoi can't convert string with letters into an int!\n";
				} catch(RepositoryException re) {
					cout << re.message;
				} catch(IndexError ie) {
					cout << ie.message;
				}
			}
		}

		if (!command_found) {
			cout << "Command not found!\n";
		}
	}

}

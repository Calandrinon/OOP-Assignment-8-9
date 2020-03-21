#include "ui.h"
#include <string>
#include <exception>
#include "myexceptions.h"
using namespace std;

UI::UI(Service* service) {
	running = true;
	this->service = service;
	this->security_clearance_mode = 'A';
}


void UI::exit() {
	running = false;
}


vector<string> UI::tokenize(string line, char delimiter) {
	return service->tokenize(line, delimiter);
}


string UI::get_command_name(string full_command) {
	vector<string> tokens = tokenize(full_command, ' ');

	if (tokens.size() == 0)
		return "-1";

	return tokens[0]; 
}


void UI::add() {
	vector<string> tokens = tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command add takes 5 parameters: add title, location, timeOfCreation, timesAccessed, footagePreview\n";
		return;
	}

	for (int i = 0; i < tokens.size(); i++) 
		tokens[i] = service->strip(tokens[i]);

	tokens[0].erase(0, 4);  // the title without the 'add' command name
	service->add(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}


void UI::list() {
	vector<Recording> container = service->get_repository_container();

	for (int i = 0; i < container.size(); i++) {
		cout << container[i].get_as_string() << "\n";
	}
}


void UI::remove() {
	vector<string> tokens = tokenize(this->last_command, ' ');

	service->remove(tokens[1]);
}


void UI::update() {
	vector<string> tokens = tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command update takes 5 parameters: add title, new_location, new_timeOfCreation, new_timesAccessed, new_footagePreview\n";
		return;
	}

	for (int i = 0; i < tokens.size(); i++) 
		tokens[i] = service->strip(tokens[i]);

	tokens[0].erase(0, 7);  // the title without the 'add' command name
	service->update(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);	
}


void UI::change_mode() {
	vector<string> tokens = tokenize(this->last_command, ' ');

	if (tokens.size() != 2 || tokens[1].size() > 1 || !(tokens[1][0] == 'A' || tokens[1][0] == 'B')) {
		cout << "The command mode takes only one parameter with the values A or B!\n";
		return;
	}

	this->security_clearance_mode = tokens[1][0];
}


void UI::run() {
	string commands[] = {"exit", "add", "list", "delete", "update", "mode"};
	void (UI::*func[])() = {&UI::exit, &UI::add, &UI::list, &UI::remove, &UI::update, &UI::change_mode};
	int number_of_commands = sizeof(commands)/sizeof(commands[0]);
	string command;

	while (running) {
		cout << ">>";
		getline(cin, command);

		if (security_clearance_mode == 'B' && command != "list" && command != "exit") {
			cout << "Permission denied!\n";
			continue;
		}

		this->last_command = command;	
		bool command_found = false;
		string command_name = get_command_name(command);

		for (int i = 0; i < number_of_commands && !command_found; i++) {
			if (commands[i] == command_name) {
				command_found = true;
				try {
					(this->*func[i])();
				} catch (CommandFormatException cfe) {
					cout << cfe.message;
				} catch(invalid_argument ie) {
					cout << "InvalidArgumentException: stoi can't convert string with letters into an int!\n";
				} catch(RepositoryException re) {
					cout << re.message;
				}
			}
		}

		if (!command_found) {
			cout << "Command not found!\n";
		}
	}

}

#include "ui.h"
#include <string>
#include <bits/stdc++.h>
#include <exception>
#include "myexceptions.h"
using namespace std;

UI::UI(Service* service) {
	running = true;
	this->service = service;
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

	vector<string> location_tokens = tokenize(tokens[1], ' ');

	service->add(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}


void UI::list() {
	vector<Recording> container = service->get_repository_container();

	for (int i = 0; i < container.size(); i++) {
		cout << container[i].get_as_string() << "\n";
	}
}


void UI::run() {
	string commands[] = {"exit", "add", "list"};
	void (UI::*func[])() = {&UI::exit, &UI::add, &UI::list};
	int number_of_commands = sizeof(commands)/sizeof(commands[0]);
	string command;

	cout << "Enter the security clearance mode: ";
	cin >> security_clearance_mode;
	cin.ignore();

	while (running) {
		cout << ">>";
		getline(cin, command);
		this->last_command = command;	
		bool command_found = false;
		string command_name = get_command_name(command);

		for (int i = 0; i < number_of_commands && !command_found; i++) {
			if (commands[i] == command_name) {
				command_found = true;
				try {
					(this->*func[i])();
				} catch (CommandFormatException cfe) {
					cout << "Your command is not correctly formatted!\n";
				} catch(invalid_argument ie) {
					cout << "InvalidArgumentException: stoi can't convert string with letters into an int!\n";
				}
			}
		}

		if (!command_found) {
			cout << "Command not found!\n";
		}
	}

}

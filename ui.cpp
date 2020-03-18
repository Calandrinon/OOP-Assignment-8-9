#include "ui.h"
#include <string>
#include <bits/stdc++.h>
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

	for (int i = 0; i < tokens.size(); i++)
		cout << service->strip(tokens[i]) << "\n";
}


void UI::run() {
	string commands[] = {"exit", "add"};
	void (UI::*func[])() = {&UI::exit, &UI::add};
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
				(this->*func[i])();
			}
		}

		cout << command_found << "\n";
	}

}

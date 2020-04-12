#include "ui.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "myexceptions.h"
//#include "dynamicvector.h"
#include <vector>
#include <algorithm>

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

	if (tokens.size() == 0) {
		return "-1";
	}

	string command_name = tokens[0];
	return command_name;
}


void UI::add() {
	vector<string> tokens = tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command add takes 5 parameters: add title, location, timeOfCreation, timesAccessed, footagePreview\n";
		return;
	}

	for (string& token: tokens)
		token = service->strip(token);

	tokens[0].erase(0, 4);  // the title without the 'add' command name
	service->add(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}


void UI::list() {
    if (service->does_service_have_file_repository()) {
        ifstream in(service->get_file_repository_filename());
        string element;

        while (getline(in, element)) {
            cout << element << "\n";
        }

        return;
    }

	vector<Recording> container = service->get_repository_container();
	vector<string> tokens = tokenize(this->last_command, ',');
	string location;
	int times_accessed;

	if (tokens.size() == 2) {
		for (string& token: tokens)
			token = service->strip(token);

		tokens[0].erase(0, 5);

		location = tokens[0];
		try {
			times_accessed = stoi(tokens[1]);
		} catch (invalid_argument& ie) {
			throw ie;
		}

		auto display_recordings = [location, times_accessed](Recording recording){
		    if (recording.get_location() == location && recording.get_times_accessed() < times_accessed) cout << recording.get_as_string() << "\n";};
		for_each(container.begin(), container.end(), display_recordings);

		return;
	} else if (tokens.size() != 1) {
		cout << "The command list should take no parameters or 2 parameters. Check help\n";
		return;
	}

	for (Recording& recording: container)
		cout << recording.get_as_string() << "\n";
}


void UI::remove() {
	vector<string> tokens = tokenize(this->last_command, ' ');

	if (!service->search(tokens[1])) {
		cout << "The element doesn't exist!\n";
		return;
	}

	string title = tokens[1];
	service->remove(title);
}


void UI::update() {
	vector<string> tokens = service->tokenize(this->last_command, ',');

	if (tokens.size() != 5) {
		cout << "The command update takes 5 parameters: add title, new_location, new_timeOfCreation, new_timesAccessed, new_footagePreview\n";
		return;
	}

	for (string& token: tokens)
		token = service->strip(token);

	tokens[0].erase(0, 7);  // the title without the 'add' command name

	if (!service->search(tokens[0])) {
		cout << "The element doesn't exist!\n";
		return;
	}

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


void UI::help() {
	cout << "\nAvailable commands:\n";
	cout << " - mode X (e.g. mode A) Note: mode B is the user mode without admin permissions, which permits only the \"list\", \"next\", \"save\", \"mylist\" and \"exit\" commands.\n"
    " - add title, location, timeOfCreation, timesAccessed, footagePreview (eg. add anomaly, deck D sector X1423, 01-13-3248, 5, prev123.mp15)\n"
    " - update title, newLocation, newTimeOfCreation, newTimesAccessed, newFootagePreview (eg. update anomaly, deck E sector X1423, 01-14-3248, 14, prev124.mp15)\n"
    " - delete title (eg. delete anomaly)\n"
    " - list\n"
	" - help\n"
	" - next - When the user selects this option by selecting next, the data of the first selected recording is displayed and the preview is played back on a holo-screen, at any given security terminal."
	" - save - Saves the currently selected recording"
	" - list location, timesAccessed -> Displays the recordings for a given location having the number of times accessed smaller than the second given amount."
	" - mylist - displays the playlist of recordings.\n"
    " - exit\n\n";
}


void UI::next() {
	cout << service->next() << "\n";
}


void UI::save() {
	service->save();
} 


void UI::mylist() {
	vector<Recording> watch_list = service->get_watchlist();

	for (Recording& recording: watch_list)
		cout << recording.get_as_string() << "\n";
}


void UI::set_file_location() {
    string command_name = this->last_command.substr(0, this->last_command.find(" "));
    string file_path = this->last_command.substr(this->last_command.find(" ")+1, this->last_command.size()-1);
    //file_path = service->strip(file_path);

    service->set_file_repository_filename(file_path);
    cout << service->get_file_repository_filename() << "\n";
}


void UI::run() {
	string commands[] = {"exit", "add", "list", "delete", "update", "mode", "help", "next", "save", "mylist", "fileLocation"};
	string permissions[] = {"all", "admin", "all", "admin", "admin", "admin", "all", "all", "all", "all", "admin"};
	void (UI::*func[])() = {&UI::exit, &UI::add, &UI::list, &UI::remove, &UI::update, &UI::change_mode, &UI::help, &UI::next, &UI::save, &UI::mylist, &UI::set_file_location};
	int number_of_commands = sizeof(commands)/sizeof(commands[0]);
	string command;

	service->add("anomaly", "deck D sector x1423", "01-10-2000", "5", "prev123.mp4");
	service->add("anomaly4", "deck D sector x1423", "01-10-2000", "12", "prev654.mp4");
	service->add("anomaly2", "deck E sector x20", "01-10-2000", "2", "prev124.mp4");
	service->add("anomaly3", "deck F sector x1422", "02-10-2000", "3", "prev125.mp4");
	service->add("1", "deck D sector x1423", "01-10-2000", "5", "prev1.mp4");
	service->add("4", "deck D sector x1423", "01-10-2000", "12", "prev4.mp4");
	service->add("3", "deck E sector x20", "01-10-2000", "2", "prev3.mp4");
	service->add("17", "deck F sector x1422", "02-10-2000", "3", "prev17.mp4");
	service->add("13", "deck D sector x1423", "01-10-2000", "12", "prev13.mp4");
	service->add("20", "deck E sector x20", "01-10-2000", "2", "prev20.mp4");
	service->add("5", "deck F sector x1422", "02-10-2000", "3", "prev5.mp4");
	help();

	while (running) {
		cout << ">>";
		getline(cin, command);

		this->last_command = command;	
		bool command_found = false;
		string command_name = get_command_name(command);

		int i = 0;
		while (i < number_of_commands && !command_found) {
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
				}
			}
			i++;
		}

		if (!command_found) {
			cout << "Command not found!\n";
		}
	}

}

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dynamicvector.h"
#include "recording.h"
using namespace std;


class Repository {
    protected:
        vector<Recording> watch_list;
        unsigned int selected_recording;

    public:
        virtual void add(Recording r) = 0;
        virtual void remove(string title) = 0;
        virtual vector<Recording> get_watchlist() = 0;
        virtual string next() = 0;
        virtual void save() = 0;
        virtual ~Repository() {}
};


class MemoryRepository: public Repository {
	private:
		vector<Recording> container;

	public:
		MemoryRepository();
		void add(Recording r);
		vector<Recording> get_container();
		void remove(string title);
		string next();
		void save();
		vector<Recording> get_watchlist();
		bool search(string title);
		~MemoryRepository();
};


class FileRepository: public Repository {
    private:
        string filename;
        ofstream out;
        unsigned int number_of_elements;

    public:
        FileRepository(string filename);
        void add(Recording r);
        void remove(string title);
        string next();
        void save();
        vector<Recording> get_watchlist();
        bool search(string title);
        string get_filename();
        void set_filename(string new_filename);
        vector<string> tokenize(string line, char delimiter);
        std::string strip(std::string str);
        int get_number_of_elements();
        ~FileRepository();
};

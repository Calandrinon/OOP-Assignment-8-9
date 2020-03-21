#include <exception>
using namespace std;

class CommandFormatException: public exception {
    public:
        string message;

    public:
        CommandFormatException(string message) {
            this->message = message; 
        }

};


class RepositoryException: public exception {
    public:
        string message;

    public:
        RepositoryException(string message) {
            this->message = message;
        }


}; 
#include "repository.h"

Repository::Repository() {

}


Repository::~Repository() {
	vector.free_vector();
}

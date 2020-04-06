#include <iostream>
#include "tests.h"
#include "ui.h"
//#include <crtdbg.h>

int main() {
	Tests();

	Repository* repository = new Repository();
	Service* service = new Service(repository);
	UI ui = UI(service);	
	ui.run();
	
	delete repository;
	delete service;
	//_CrtDumpMemoryLeaks();
	return 0;
}

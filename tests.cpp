#include "tests.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
using namespace std;


Tests::Tests() {
	test_dynamic_vector_creation();
	test_dynamic_vector_get_element_from_index();
	test_dynamic_vector_push_back();
	test_dynamic_vector_deletion();
	test_recording_getters();
	test_recording_setters();
	test_repository_add();
	test_service_add();
	test_repository_delete();
	test_service_delete();
	test_repository_search();
	test_service_update();
	test_dynamic_vector_assignment_operator();
	test_dynamic_vector_overloaded_subscript();
    testRepositoryAdd__duplicateElement__doesntAddElement();
    testRepositoryNext__averageCase__incrementsToNextElement();
    testRepositorySave__averageCase__elementAddedToWatchlist();
}


void Tests::testRepositorySave__averageCase__elementAddedToWatchlist() {
    Repository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    repository.save();

    vector<Recording> watchlist = repository.get_watchlist();
    Recording watchlist_element = watchlist[0];
    assert(watchlist_element.get_title() == recording.get_title());

    cout << "Repository save operation test passed!\n";
}


void Tests::testRepositoryNext__averageCase__incrementsToNextElement() {
    Repository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    string element = repository.next();

    assert(element == "anomaly2, 1, 01-13-3248, 5, prev124.mp15");

    cout << "Repository next operation test passed!\n";
}


void Tests::testRepositoryAdd__duplicateElement__doesntAddElement() {
    Repository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    try {
        repository.add(recording);
    } catch(RepositoryException re) {

    }

    vector<Recording> container = repository.get_container();
    assert(container.size() == 1);

    cout << "Repository duplicate element test passed!\n";
}


void Tests::test_dynamic_vector_creation() {
	DynamicVector<char> vector;

	std::cout << "Dynamic vector creation test passed!\n";
	vector.free();
}


void Tests::test_dynamic_vector_get_element_from_index() {
	DynamicVector<int> vector;
	
	vector.push_back(5);
	vector.push_back(24);
	vector.push_back(187);
	vector.push_back(876);
	
	assert(vector.element(0) == 5);
	assert(vector.element(1) == 24);
	assert(vector.element(2) == 187);
	assert(vector.element(3) == 876);

	assert(vector.element(4) == vector[0]);

	std::cout << "Dynamic vector element extraction test passed!\n";
	vector.free();
}


void Tests::test_dynamic_vector_push_back() {
	DynamicVector<const char*> vector;
	
	vector.push_back("abc");
	vector.push_back("def");
	vector.push_back("zzz");	

	assert(strcmp(vector.element(1), "def") == 0);
	assert(vector.size() == 3);

	std::cout << "Dynamic vector push_back method test passed!\n";
	vector.free();
}


void Tests::test_dynamic_vector_deletion() {
	DynamicVector<int> vector;
	
	vector.push_back(5);
	vector.push_back(24);
	vector.push_back(777);
	vector.push_back(555);
	vector.push_back(333);
	vector.push_back(111);
	vector.remove(1,4);

	assert(vector.size() == 2);

	std::cout << "Dynamic vector element deletion test passed!\n";
	vector.free();
}


void Tests::test_recording_getters() {
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	

	assert(recording.get_title() == "anomaly");	
	assert(recording.get_location() == "deck D sector X1423");
	assert(recording.get_time_of_creation() == "01-13-3248");
	assert(recording.get_times_accessed() == 5);
	assert(recording.get_footage_preview() == "prev123.mp15");

	std::cout << "Recording getters tests passed!\n";
}


void Tests::test_recording_setters() {
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	

	recording.set_title("sometitle");
	assert(recording.get_title() == "sometitle");	

	std::cout << "Recording setters tests passed!\n";
}


void Tests::test_repository_add() {
	Repository repository;		

	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	vector<Recording> container = repository.get_container();
	assert(container[0].get_title() == recording.get_title());

	cout << "Repository add operation test passed!\n";
}


void Tests::test_service_add() {
	Repository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");

	vector<Recording> container = repository.get_container();
	assert(container.size() == 1);

	cout << "Service add operation test passed!\n";
}


void Tests::test_repository_delete() {
	Repository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);
	assert(repository.get_container().size() == 1);

	repository.remove("anomaly");
	assert(repository.get_container().size() == 0);

	cout << "Repository delete operation test passed!\n";
}


void Tests::test_service_delete() {
	Repository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");
	assert(repository.get_container().size() == 1);

	service.remove("anomaly");
	assert(repository.get_container().size() == 0);
	
	cout << "Service delete operation test passed!\n";
}


void Tests::test_repository_search() {
	Repository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	assert(repository.search("anomaly"));

	cout << "Repository search operation test passed!\n";
}


void Tests::test_service_update() {
	Repository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");
	assert(repository.get_container().size() == 1);

	service.update("anomaly", "deck X sector X200","01-13-3500","1","abc.mp4");
	vector<Recording> container = repository.get_container();
	assert(container[0].get_footage_preview() == "abc.mp4");
	cout << "Service update operation test passed!\n";
}


void Tests::test_dynamic_vector_assignment_operator() {
	DynamicVector<int> vector;
	vector.push_back(5);
	vector.push_back(2);
	assert(vector.size() == 2);
	
	DynamicVector<int> vector2;
	vector2 = vector;
	assert(vector2.size() == 2);
	assert(vector2.element(0) == vector.element(0));
	assert(vector2.element(1) == vector.element(1));
	vector.free();
	vector2.free();
	cout << "Dynamic vector assignment operator test passed!\n";
}


void Tests::test_dynamic_vector_overloaded_subscript() {
	DynamicVector<int> vector;
	vector.push_back(17);

	assert(vector[0] == 17);
	vector.free();

	cout << "Dynamic vector overloaded subscript test passed!\n";
}
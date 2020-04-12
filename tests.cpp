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
    testFileRepository__addingAnElement__success();
    testFileRepository__addingADuplicateElement__success();
    testFileRepository__removingAnElement__success();
    testFileRepository__searchingAnElement__success();
    testFileRepository__searchingAnNonexistentElement__returnsFalse();
    testFileRepository__removingANonexistingElement__fails();
    testFileRepository__getNextElement__success();
    testFileRepository__saveElement__success();
    testFileRepository__getFilename__success();
    testRepositorySearch__searchingNonexistentElement__fails();
    testServiceGetFileRepoFilename__getsFilename__success();
    testRepositorySetFileRepoFilename__setsFilename__success();
    testServiceSetFileRepoFilename__setsFilename__success();
    testRepositoryGetFileRepoFilename__getsFilename__success();
}


void Tests::testRepositorySave__averageCase__elementAddedToWatchlist() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    repository.save();

    vector<Recording> watchlist = repository.get_watchlist();
    Recording watchlist_element = watchlist[0];
    assert(watchlist_element.get_title() == recording.get_title());

    cout << "MemoryRepository save operation test passed!\n";
}


void Tests::testRepositoryNext__averageCase__incrementsToNextElement() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    string element = repository.next();

    assert(element == "anomaly2, 1, 01-13-3248, 5, prev124.mp15");

    cout << "MemoryRepository next operation test passed!\n";
}


void Tests::testRepositoryAdd__duplicateElement__doesntAddElement() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    try {
        repository.add(recording);
    } catch(RepositoryException re) {

    }

    vector<Recording> container = repository.get_container();
    assert(container.size() == 1);

    cout << "MemoryRepository duplicate element test passed!\n";
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
	MemoryRepository repository;		

	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	vector<Recording> container = repository.get_container();
	assert(container[0].get_title() == recording.get_title());

	cout << "MemoryRepository add operation test passed!\n";
}


void Tests::test_service_add() {
	MemoryRepository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");

	vector<Recording> container = repository.get_container();
	assert(container.size() == 1);

	cout << "Service add operation test passed!\n";
}


void Tests::test_repository_delete() {
	MemoryRepository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);
	assert(repository.get_container().size() == 1);

	repository.remove("anomaly");
	assert(repository.get_container().size() == 0);

	cout << "MemoryRepository delete operation test passed!\n";
}


void Tests::test_service_delete() {
	MemoryRepository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");
	assert(repository.get_container().size() == 1);

	service.remove("anomaly");
	assert(repository.get_container().size() == 0);
	
	cout << "Service delete operation test passed!\n";
}


void Tests::test_repository_search() {
	MemoryRepository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	assert(repository.search("anomaly"));

	cout << "MemoryRepository search operation test passed!\n";
}


void Tests::test_service_update() {
	MemoryRepository repository;
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


void Tests::testFileRepository__searchingAnElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository searching operation test passed!\n";
}


void Tests::testFileRepository__addingAnElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository add operation test passed!\n";
}


void Tests::testFileRepository__removingAnElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->remove("1");
    assert(repository->get_number_of_elements() == 1);

    delete repository;
    cout << "File repository remove operation test passed!\n";
}


void Tests::testFileRepository__addingADuplicateElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    try {
        repository->add(recording2);
    } catch (std::exception& exc) {

    }

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository duplicate element addition test passed!\n";
}



void Tests::testFileRepository__searchingAnNonexistentElement__returnsFalse() {
    FileRepository* repository = new FileRepository("test.in");

    assert(repository->search("5") == false);

    delete repository;
    cout << "File repository unexistent searched element test passed!\n";
}


void Tests::testFileRepository__removingANonexistingElement__fails() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->remove("abc");
    assert(repository->get_number_of_elements() == 2);

    delete repository;
    cout << "File repository unexisting element removal test passed!\n";
}


void Tests::testFileRepository__getNextElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    assert(repository->next() == "2, 2, 02-02-2002, 2, 2.mp1");
    assert(repository->next() == "1, 1, 01-01-2001, 1, 1.mp1");
    assert(repository->next() == "2, 2, 02-02-2002, 2, 2.mp1");

    delete repository;
    cout << "File repository next operation test passed!\n";
}


void Tests::testFileRepository__saveElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    try {
        repository->save();
    } catch (std::exception& exc) {}

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");

    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->save();
    vector<Recording> watchlist = repository->get_watchlist();
    assert(watchlist.size() == 1);

    delete repository;
    cout << "File repository save operation test passed!\n";
}


void Tests::testFileRepository__getFilename__success() {
    FileRepository* repository = new FileRepository("test.in");

    assert(repository->get_filename() == "test.in");

    delete repository;
    cout << "File repository save operation test passed!\n";
}


void Tests::testRepositorySearch__searchingNonexistentElement__fails() {
    MemoryRepository* repository = new MemoryRepository();

    assert(repository->search("abc") == false);

    delete repository;
    cout << "File repository nonexistent element search test passed!\n";
}


void Tests::testServiceGetFileRepoFilename__getsFilename__success() {
    FileRepository* repository = new FileRepository("test.in");
    Service* service = new Service(repository);

    assert(service->get_file_repository_filename() == "test.in");

    delete repository;
    delete service;
    cout << "Service&fileRepo get filename test passed!\n";
}


void Tests::testServiceSetFileRepoFilename__setsFilename__success() {
    FileRepository* repository = new FileRepository("test.in");
    Service* service = new Service(repository);

    assert(service->get_file_repository_filename() == "test.in");
    service->set_file_repository_filename("test2.in");
    assert(service->get_file_repository_filename() == "test2.in");

    delete repository;
    delete service;
    cout << "Service&fileRepo set filename test passed!\n";
}


void Tests::testRepositorySetFileRepoFilename__setsFilename__success() {
    FileRepository* repository = new FileRepository("test.in");

    repository->set_filename("test2.in");
    assert(repository->get_filename() == "test2.in");

    delete repository;
    cout << "FileRepo set filename test passed!\n";
}


void Tests::testRepositoryGetFileRepoFilename__getsFilename__success() {
    FileRepository* repository = new FileRepository("test.in");

    assert(repository->get_filename() == "test.in");

    delete repository;
    cout << "FileRepo get filename test passed!\n";
}

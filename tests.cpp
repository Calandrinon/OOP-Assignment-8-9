#include "tests.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

Tests::Tests() {
	test_dynamic_vector_creation();
	test_dynamic_vector_get_element_from_index();
	test_dynamic_vector_push_back();
	test_dynamic_vector_deletion();
}


void Tests::test_dynamic_vector_creation() {
	DynamicVector<char> vector;
	vector.free_vector();

	std::cout << "Dynamic vector creation test passed!\n";
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
	
	try {
		assert(vector.element(4) == 99999);
		assert(false);
	} catch(...) {}

	vector.free_vector();
	std::cout << "Dynamic vector element extraction test passed!\n";
}


void Tests::test_dynamic_vector_push_back() {
	DynamicVector<const char*> vector;
	
	vector.push_back("abc");
	vector.push_back("def");
	vector.push_back("zzz");	

	assert(strcmp(vector.element(1), "def") == 0);
	assert(vector.size() == 3);

	vector.free_vector();
	std::cout << "Dynamic vector push_back method test passed!\n";
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

	vector.free_vector();
	std::cout << "Dynamic vector element deletion test passed!\n";
}

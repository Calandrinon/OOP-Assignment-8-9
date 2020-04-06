#ifndef __TESTS_H__
#define __TESTS_H__
#include "dynamicvector.h"
#include "repository.h"
#include "service.h"

class Tests {
	public:
		Tests();
		void test_dynamic_vector_creation();
		void test_dynamic_vector_push_back();
		void test_dynamic_vector_get_element_from_index();
		void test_dynamic_vector_deletion();
		void test_recording_getters();
		void test_recording_setters();
		void test_repository_add();
		void test_service_add();
		void test_repository_delete();
		void test_service_delete();
		void test_repository_search();
		void test_service_update();
		void test_dynamic_vector_assignment_operator();
		void test_dynamic_vector_overloaded_subscript();
        void testRepositoryAdd__duplicateElement__doesntAddElement();
        void testRepositoryNext__averageCase__incrementsToNextElement();
        void testRepositorySave__averageCase__elementAddedToWatchlist();
        void testDynamicVectorSubscript__outOfRange__throwsException();
};

#endif

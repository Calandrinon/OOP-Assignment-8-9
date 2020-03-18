#pragma once
#include <iostream>
#include "dynamicvector.h"
#include "recording.h"

class Repository {
	private:
		DynamicVector<Recording> vector;	
	
	public:
		Repository();
		~Repository();
};

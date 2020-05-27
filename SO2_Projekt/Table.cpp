#pragma once
#include <time.h>
#include <cstdlib>
#include "Student.cpp"

struct Table {
	int id;
	Student man;
	Student woman;

	Table(int id) {
		srand(time(NULL));
		this->id = id;
	}

	int getConvTime() {
		return rand() % 10 + 1;
	}
};
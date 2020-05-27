#pragma once
#include <time.h>
#include <cstdlib>
#include "Student.cpp"

struct Table {
	int id;
	Student *man;
	Student *woman;

	Table(int id) {
		srand(time(NULL));
		this->id = id;
		this->man = NULL;
		this->woman = NULL;
	}

	bool isManSpotFree() {
		return man == NULL;
	}

	bool isWomanSpotFree() {
		return woman == NULL;
	}

	int getConvTime() {
		return rand() % 10 + 1;
	}

	bool compareWooers() {
		if (man == NULL || woman == NULL)
			return false;
		if (man->pair_estimation >= woman->self_estimation && woman->pair_estimation >= man->self_estimation)
			return true;
		return false;
	}
};
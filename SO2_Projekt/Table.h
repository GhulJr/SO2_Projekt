#pragma once
#include <time.h>
#include <cstdlib>

#include "Student.h"
struct Student;

struct Table {
	int id;
	Student* man;
	Student* woman;

	Table(int id);

	bool isManSpotFree();

	bool isWomanSpotFree();

	int getConvTime();

	bool compareWooers();
};
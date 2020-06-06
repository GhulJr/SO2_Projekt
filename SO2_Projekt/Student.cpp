#pragma once
#include <time.h>
#include <cstdlib>
#include <vector>
#include <thread>

struct Student {
	int index;
	int self_estimation;
	int pair_estimation;
	bool gender; //True - studentka, false - student.

	Student(bool gender) {
		srand(time(NULL));
		this->gender = gender;
		if (gender) {
			moduloFactor = 3;
			moduloAddjustment = 7;
		}
		else {
			moduloFactor = 10;
			moduloAddjustment = 1;
		}
		self_estimation = rand() % moduloFactor + moduloAddjustment;
		pair_estimation = rand() % moduloFactor + moduloAddjustment;
	}

private:
	int moduloFactor;
	int moduloAddjustment;
};
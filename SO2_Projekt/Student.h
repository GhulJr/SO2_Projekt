#pragma once
#include <time.h>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include "Table.h"
struct Table;

struct Student {
	bool tableAssigned;
	int self_estimation;
	int pair_estimation;
	bool gender;			//true - studentka, false - student.
	bool* running;
	bool waitingForPerson;

	Table* currentTable;
	std::vector<Table>* tables;
	//std::mutex mtx;
	std::mutex* _myMutex;

	Student(bool gender, bool * running, std::vector<Table>* tables, std::mutex* mutex);

	void run();

	void sendInvitation();
	void acceptInvitation();


private:
	int moduloFactor;
	int moduloAddjustment;
};
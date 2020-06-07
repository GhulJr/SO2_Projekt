#pragma once
#include <time.h>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include "Table.h"
struct Table;

struct Student {
	int index;

	bool tableAssigned;
	int self_estimation;
	int pair_estimation;
	bool gender;			//true - studentka, false - student.
	bool* running;
	bool waitingForPerson;

	bool dateFinshed;

	Table* currentTable;
	std::vector<Table>* tables;
	std::mutex* _myMutex;
	std::thread* thread;

	Student(int index, bool gender, bool * running, std::vector<Table>* tables, std::mutex* mutex);

	void run();

	//void sendInvitation();
//	void acceptInvitation();
	void startThread();


private:
	int moduloFactor;
	int moduloAddjustment;
};
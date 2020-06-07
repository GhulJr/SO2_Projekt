#pragma once
#include "Table.h"

Table::Table(int id){
	srand(time(NULL));
	this->id = id;
	this->man = nullptr;
	this->woman = nullptr;
}

bool Table::isManSpotFree()
{
	return man == nullptr;
}

bool Table::isWomanSpotFree()
{
	return woman == nullptr;
}

int Table::getConvTime()
{
	return rand() % 10 + 1;
}

bool Table::compareWooers()
{
	if (man == nullptr || woman == nullptr)
		return false;
	if (man->pair_estimation >= woman->self_estimation && woman->pair_estimation >= man->self_estimation)
		return true;
	return false;
}

void Table::takeSeat(Student* student) {
	if (student->gender) {
		woman = student;
	}
	else {
		man = student;
	}
	student->tableAssigned = true;
	student->waitingForPerson = true;
	if (man != nullptr && woman != nullptr) {
		woman->waitingForPerson = false;
		man->waitingForPerson = false;		
	}
}

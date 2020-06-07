#pragma once
#include <vector>
#include "Student.h"


Student::Student(bool gender, bool * running, std::vector<Table>* tables, std::mutex* mutex) {
	srand(time(NULL));
	this->gender = gender;
	this->running = running;
	this->tables = tables;
	this->_myMutex = mutex;
	this->tableAssigned = false;
	this->waitingForPerson = false;
	this->currentTable = nullptr;

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


void Student::run()
{
	while (true) {
		if (!this->running) {
			break;
		}
		
		if (!this->tableAssigned) {
			for (int i = 0; i < this->tables->size(); i++)
			{
				try
				{
					std::lock_guard<std::mutex> lock(*this->_myMutex);

					if (this->gender) {
						if (this->tables->at(i).isWomanSpotFree()) {
						//	std::lock_guard<std::mutex> lock(*this->_myMutex);
							this->tables->at(i).takeSeat(this);
							this->currentTable = &this->tables->at(i);
							break;
						}
					}
					else {
						if (this->tables->at(i).isManSpotFree()) {
						//	std::lock_guard<std::mutex> lock(*this->_myMutex);
							this->tables->at(i).takeSeat(this);
							this->currentTable = &this->tables->at(i);
							break;
						}
					}
				}
				catch (const std::exception& e)
				{

				}
			}
		} 
		else if (!this->waitingForPerson) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			//TODO: clear student from table.
			if (this->gender) {
				this->currentTable->woman = nullptr;
			}
			else {
				this->currentTable->man = nullptr;
			}
			break;
		}
	}
}

void Student::sendInvitation()
{
	this->waitingForPerson = true;
}

void Student::acceptInvitation()
{
	this->waitingForPerson = false;
}

void Student::startThread() {
	this->thread = new std::thread(&Student::run, this);
}

#pragma once
#include <vector>
#include "Student.h"

void Student::run()
{
	while (this->currentTable == nullptr) {
		if (!this->running) {
			break;
		}

		for (int i = 0; i < this->tables->size(); i++)
		{
			try
			{
				std::lock_guard<std::mutex> lock(*_myMutex);
				if (this->gender) {
					if (this->tables->at(i).isWomanSpotFree()) {
						this->tables->at(i).woman = this;

						// ktos juz jest przy stoliku
						if (!this->tables->at(i).isManSpotFree()) {
							int time = this->tables->at(i).getConvTime();

							// wyslij wiadomosc do czekajcej drugiej osoby 
							this->tables->at(i).man->acceptInvitation();

							// wait
							std::this_thread::sleep_for(std::chrono::seconds(5));

							// clear table
							this->tables->at(i).woman = nullptr;

							// kill this thread
							break;
						}

						// czekamy na drug¹ osobê
						else {
							this->sendInvitation();
							while (this->waiting) {};

							//rozpoczyna sie konwersacja 
							std::this_thread::sleep_for(std::chrono::seconds(5));
							this->tables->at(i).woman = nullptr;

							break;
						}
					}
				}
				else {
					if (this->tables->at(i).isManSpotFree()) {
						this->tables->at(i).man = this;
						if (!this->tables->at(i).isWomanSpotFree()) {
							int time = this->tables->at(i).getConvTime();

							// wyslij wiadomosc do czekajcej drugiej osoby 
							this->tables->at(i).woman->acceptInvitation();

							// wait
							std::this_thread::sleep_for(std::chrono::seconds(5));

							// clear table
							this->tables->at(i).man = nullptr;

							// kill this thread
							break;
						}

						// czekamy na drug¹ osobê
						else {
							this->sendInvitation();
							while (this->waiting) {};

							//rozpoczyna sie konwersacja 
							std::this_thread::sleep_for(std::chrono::seconds(5));
							this->tables->at(i).man = nullptr;
							break;
						}
					}
				}
			}
			catch (const std::exception & e)
			{

			}
		}


	}
}

Student::Student(bool gender, bool * runnning, std::vector<Table>* tables, std::mutex* mutex) {
	srand(time(NULL));
	this->gender = gender;
	this->running = running;
	this->tables = tables;
	this->_myMutex = mutex;

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
	
	std::thread t1 = std::thread(&Student::run, this);
}


void Student::sendInvitation()
{
	*this->waiting = true;
}

void Student::acceptInvitation()
{
	*this->waiting = false;
}

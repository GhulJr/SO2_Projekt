#pragma once
#include <vector>
#include <thread>
#include <mutex>

#include "Table.cpp"
#include "Student.cpp"
struct Finder {
	
	std::thread thread;
	Student* man; 
	Student* woman;
	std::vector<Table>* tables;

	Finder(std::vector<Table>* tables, Student* man, Student* woman) {
		this->tables = tables;
		this->man = man;
		this->woman = woman;
	}

	void findFreeSpot() {
		
	}
};
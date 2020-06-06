#pragma once
#include "Table.h"

Table::Table(int id){
	srand(time(NULL));
	this->id = id;
	this->man = NULL;
	this->woman = NULL;
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
	if (man == NULL || woman == NULL)
		return false;
	if (man->pair_estimation >= woman->self_estimation && woman->pair_estimation >= man->self_estimation)
		return true;
	return false;
}

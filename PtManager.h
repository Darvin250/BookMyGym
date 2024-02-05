#pragma once
#include "PT.h"

#ifndef PtManager_H
#define PtManager_H

class PtManager
{
public:
	int addPersonalTrainer(PT* pt);
	int updatePersonalTrainer(PT* pt);
	int deletePersonalTrainer(PT* pt);
	int displayPersonalTrainer();
	bool validatePersonalTrainer(int ptID);
	static double getTrainerRate(int ptID);
	PT* getTrainer(int ptID);
	bool hasBookings(int ptID);
};

#endif
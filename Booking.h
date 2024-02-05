#pragma once
#ifndef Booking_H
#define Booking_H
#include <string>

class Booking
{
public:
	int bookID, slotID, custID, ptID;
	std::string bookSlot;
	std::string time;
	double bookFee;
};

#endif
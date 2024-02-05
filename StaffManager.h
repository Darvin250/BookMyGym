#pragma once
#include "Staff.h"

#ifndef StaffManager_H
#define StaffManager_H

class StaffManager
{
public:
	bool checkCredentials(std::string staffEmail, std::string staffPass, Staff& loggedInStaff);
	Staff* displayAllCustomer();
};

#endif
#pragma once
#include "Customer.h"

#ifndef CustomerManager_H
#define CustomerManager_H

class CustomerManager
{
public:
	int addCustomer(Customer* customer);
	int updateCustomer(Customer* customer);
	int deleteCustomer(Customer* customer);
	void displayAllCustomer();
	Customer* getCustomer(int custID);
	bool checkCredentials(std::string custEmail, std::string custPass, Customer& loggedInCustomer);
	bool isChar(char c);
	bool is_valid(std::string custEmail);
	bool passwordCheck(std::string custPass);
	bool emailExists(std::string custEmail);
};

#endif
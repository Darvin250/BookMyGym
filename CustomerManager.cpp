#include "CustomerManager.h"
#include "DBConnection.h"
#include <iomanip>

int CustomerManager::addCustomer(Customer* customer)
{
	if (emailExists(customer->custEmail))
	{
		std::cout << "****************| Email already exists |*****************\n";
		return 0;
	}

	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("INSERT INTO customer (custEmail, custName, custPass, custDOB, custNum) VALUES (?, ?, ?, ?, ?)");
	ps->setString(1, customer->custEmail);
	ps->setString(2, customer->custName);
	ps->setString(3, customer->custPass);
	ps->setInt(4, customer->custDOB);
	ps->setString(5, customer->custNum);
	
	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int CustomerManager::updateCustomer(Customer* customer)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("UPDATE customer SET custEmail = ?, custName = ?, custPass = ?, custDOB = ?, custNum = ? WHERE custID =  ?");
	ps->setString(1, customer->custEmail);
	ps->setString(2, customer->custName);
	ps->setString(3, customer->custPass);
	ps->setInt(4, customer->custDOB);
	ps->setString(5, customer->custNum);
	ps->setInt(6, customer->custID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int CustomerManager::deleteCustomer(Customer* customer)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("DELETE FROM customer WHERE custID =  ?");
	ps->setInt(1, customer->custID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

void CustomerManager::displayAllCustomer()
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM customer");

	sql::ResultSet* res;
	res = ps->executeQuery();

	std::cout << "|*********************************** All Customer **********************************|\n";
	std::cout << "=====================================================================================\n";
	std::cout << "| Customer ID |   Customer Email   | Customer Name | Customer DOB | Customer Number |\n";
	std::cout << "=====================================================================================\n";

	while (res->next())
	{
		try
		{
			std::cout << "| " << std::setw(11) << res->getInt("custID") << " | " << std::setw(18) << res->getString("custEmail")
				<< " | " << std::setw(13) << res->getString("custName") << " | " << std::setw(12) << res->getString("custDOB")
				<< " | " << std::setw(15) << res->getString("custNum") << " |\n";
		}
		catch (const sql::SQLException& e)
		{
			std::cerr << "SQL Exception: " << e.what() << std::endl;
		}
		
	}
	std::cout << "=====================================================================================\n";

	res->close();
	delete res;
	delete ps;
}

Customer* CustomerManager::getCustomer(int custID)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("SELECT * FROM customer WHERE custID =  ?");
		ps->setInt(1, custID);

		sql::ResultSet* res;
		res = ps->executeQuery();
		Customer* customer = NULL;

		if (res->next())
		{
			customer = new Customer();
			customer->custID = res->getInt("custID");
			customer->custEmail = res->getString("custEmail");
			customer->custName = res->getString("custName");
			customer->custDOB = res->getInt("custDOB");
			customer->custNum = res->getString("custNum");
		}
		res->close();
		delete res;
		delete ps;

		return customer;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return nullptr;
	}
}

bool CustomerManager::checkCredentials(std::string custEmail, std::string custPass, Customer& loggedInCustomer)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM customer WHERE custEmail = ? AND custPass = ?");
	ps->setString(1, custEmail);
	ps->setString(2, custPass);

	sql::ResultSet* res;
	res = ps->executeQuery();

	if (res->next())
	{
		if (res->getString("custPass") == custPass)
		{
			loggedInCustomer.custID = res->getInt("custID");
			loggedInCustomer.custEmail = res->getString("custEmail");
			loggedInCustomer.custName = res->getString("custName");
			loggedInCustomer.custPass = res->getString("custPass");
			loggedInCustomer.custDOB = res->getInt("custDOB");
			loggedInCustomer.custNum = res->getString("custNum");

			res->close();
			delete ps;
			delete res;

			return true;
		}
	}
	res->close();
	delete  ps;
	delete res;

	return false;
}

bool CustomerManager::isChar(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

bool CustomerManager::is_valid(std::string custEmail)
{
	if (!isChar(custEmail[0])) 
	{
		return 0;
	}

	int At = -1, Dot = -1;

	for (int i = 0;i < custEmail.length(); i++) 
	{
 
		if (custEmail[i] == '@') 
		{
			At = i;
		}

		else if (custEmail[i] == '.') 
		{
			Dot = i;
		}
	}

	if (At == -1 || Dot == -1)
	{
		return 0;
	}
		
	if (At > Dot)
	{
		return 0;
	}
		
	return !(Dot >= (custEmail.length() - 1));
}

bool CustomerManager::passwordCheck(std::string custPass)
{
	if(custPass.length() < 8) {
		std::cout << "\nPassword must be at least 8 characters long.\n";
		return false;
	}

	bool containSymbol = false;
	for (char ch : custPass)
	{
		if (!isalnum(ch)) {
			containSymbol = true;
			break;
		}
	}

	if (!containSymbol) {
		std::cout << "Password must contain at least one symbol.\n";
		return false;
	}

	return true;
}

bool CustomerManager::emailExists(std::string custEmail)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("SELECT * FROM customer WHERE custEmail = ?");
		ps->setString(1, custEmail);

		sql::ResultSet* res;
		res = ps->executeQuery();

		bool emailExists = res->next();

		res->close();
		delete res;
		delete ps;

		return emailExists;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return false;
	}
}
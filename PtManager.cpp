#include "PtManager.h"
#include "DBConnection.h"
#include <iomanip>

int PtManager::addPersonalTrainer(PT* pt)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("INSERT INTO personaltrainer (ptName, ptNum, yearsExperience, ptRate) VALUES (?, ?, ?, ?)");
	ps->setString(1, pt->ptName);
	ps->setString(2, pt->ptNum);
	ps->setInt(3, pt->yearsExperience);
	ps->setDouble(4, pt->ptRate);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int PtManager::updatePersonalTrainer(PT* pt)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("UPDATE personaltrainer SET ptName = ?, ptNum = ?, yearsExperience = ?, ptRate = ? WHERE ptID =  ?");
	ps->setString(1, pt->ptName);
	ps->setString(2, pt->ptNum);
	ps->setInt(3, pt->yearsExperience);
	ps->setDouble(4, pt->ptRate);
	ps->setInt(5, pt->ptID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int PtManager::deletePersonalTrainer(PT* pt)
{
	if (hasBookings(pt->ptID))
	{
		std::cout << "\n********| Trainer has bookings, cannot be deleted |***********";
		return 0;
	}

	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("DELETE FROM personaltrainer WHERE ptID =  ?");
	ps->setInt(1, pt->ptID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int PtManager::displayPersonalTrainer()
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM personaltrainer");

	sql::ResultSet* res;
	res = ps->executeQuery();

	std::cout << "|********************************* All Personal Trainer **********************************|\n";
	std::cout << "===========================================================================================\n";
	std::cout << "| Trainer ID |     Trainer Name     | Trainer Number | Years of Experience | Trainer Rate |\n";
	std::cout << "===========================================================================================\n";

	while (res->next())
	{
		try
		{
			std::cout << "| " << std::setw(10) << res->getInt("ptID") << " | " << std::setw(20) << res->getString("ptName")
				<< " | " << std::setw(14) << res->getString("ptNum") << " | " << std::setw(19) << res->getInt("yearsExperience")
				<< " | " << std::setw(6) << "RM " << std::setw(6) << std::fixed << std::setprecision(2) << res->getDouble("ptRate") << " |\n";
		}
		catch (const sql::SQLException& e)
		{
			std::cerr << "SQL Exception: " << e.what() << std::endl;
		}
	}
	std::cout << "===========================================================================================\n";

	res->close();
	delete ps;
}

bool PtManager::validatePersonalTrainer(int ptID)
{
	DBConnection con;

	sql::PreparedStatement* psCheck;
	psCheck = con.prepareStatement("SELECT * FROM personaltrainer WHERE ptID = ?");
	psCheck->setInt(1, ptID);

	sql::ResultSet* resCheck;
	resCheck = psCheck->executeQuery();

	bool isValid = resCheck->next();

	psCheck->close();
	delete psCheck;

	return isValid;
}

double PtManager::getTrainerRate(int ptID)
{
	DBConnection con;

	sql::PreparedStatement* psTrainerRate;
	psTrainerRate = con.prepareStatement("SELECT ptRate FROM personaltrainer WHERE ptID = ?");
	psTrainerRate->setInt(1, ptID);

	sql::ResultSet* res = psTrainerRate->executeQuery();

	double ptRate;

	if (res->next()) {
		ptRate = res->getDouble("ptRate");
	}

	psTrainerRate->close();
	delete psTrainerRate;

	return ptRate;
}

PT* PtManager::getTrainer(int ptID)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("SELECT * FROM personaltrainer WHERE ptID =  ?");
		ps->setInt(1, ptID);

		sql::ResultSet* res;
		res = ps->executeQuery();
		PT* pt = NULL;

		if (res->next())
		{
			pt = new PT();
			pt->ptID = res->getInt("ptID");
			pt->ptName = res->getString("ptName");
			pt->ptNum = res->getString("ptNum");
			pt->yearsExperience = res->getInt("yearsExperience");
			pt->ptRate = res->getDouble("ptRate");
		}
		res->close();
		delete res;
		delete ps;

		return pt;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return nullptr;
	}
}

bool PtManager::hasBookings(int ptID)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("SELECT COUNT(*) AS count FROM bookings WHERE ptID = ?");
		ps->setInt(1, ptID);

		sql::ResultSet* res;
		res = ps->executeQuery();

		if (res->next())
		{
			int count = res->getInt("count");
			return count > 0;
		}

		res->close();
		delete res;
		delete ps;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}

	return false;
}
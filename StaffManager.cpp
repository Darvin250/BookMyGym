#include "StaffManager.h"
#include "DBConnection.h"

bool StaffManager::checkCredentials(std::string staffEmail, std::string staffPass, Staff& loggedInStaff)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM staff WHERE staffEmail = ? AND staffPass = ?");
	ps->setString(1, staffEmail);
	ps->setString(2, staffPass);

	sql::ResultSet* res;
	res = ps->executeQuery();

	if (res->next())
	{
		if (res->getString("staffPass") == staffPass)
		{
			loggedInStaff.staffID = res->getInt("staffID");
			loggedInStaff.staffEmail = res->getString("staffEmail");
			loggedInStaff.staffName = res->getString("staffName");
			loggedInStaff.staffPass = res->getString("staffPass");

			res->close();
			delete ps;
			delete res;

			return true;
		}
	}
	res->close();
	delete ps;
	delete res;

	return false;
}
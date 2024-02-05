#include <mysql/jdbc.h>

#ifndef DBConnection_H
#define DBConnection_H

class DBConnection
{
private:
	sql::Connection* con;

public:
	DBConnection();
	~DBConnection();
	sql::PreparedStatement* prepareStatement(std::string query);
};

#endif
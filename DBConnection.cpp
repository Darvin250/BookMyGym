#include "DBConnection.h"

DBConnection::DBConnection()
{
	sql::mysql::MySQL_Driver* driver;

	try
	{
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://localhost:3306", "root", "");

		con->setSchema("dbbookmygym");
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}

	
}

DBConnection::~DBConnection()
{
	con->close();
}

sql::PreparedStatement* DBConnection::prepareStatement(std::string query)
{
	if(con) 
	{
		try 
		{
			return con->prepareStatement(query);
		}
		catch (sql::SQLException& e) 
		{
			std::cerr << "SQL Exception during prepareStatement: " << e.what() << std::endl;
		}
	}
 else {
	 std::cerr << "Connection is not properly initialized." << std::endl;
	}

	return nullptr;
}
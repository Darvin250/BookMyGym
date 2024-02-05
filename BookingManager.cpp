#include "BookingManager.h"
#include "DBConnection.h"
#include "PtManager.h"
#include "CustomerManager.h"
#include <iomanip>

int BookingManager::addBooking(Booking* booking)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("INSERT INTO bookings (slotID, bookSlot, custID, ptID, bookFee) VALUES (?, ?, ?, ?, ?)");
		ps->setInt(1, booking->slotID);
		ps->setString(2, booking->bookSlot);
		ps->setInt(3, booking->custID);
		ps->setInt(4, booking->ptID);
		ps->setDouble(5, booking->bookFee);

		int numRowsAffected = ps->executeUpdate();

		ps->close();
		delete ps;

		return numRowsAffected;
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return -1;  
	}
}

int BookingManager::updateBooking(Booking* booking)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("UPDATE bookings SET slotID = ?, bookSlot = ?, custID = ?, ptID = ?, bookFee = ? WHERE bookID =  ?");
	ps->setInt(1, booking->slotID);
	ps->setString(2, booking->bookSlot);
	ps->setInt(3, booking->custID);
	ps->setInt(4, booking->ptID);
	ps->setDouble(5, booking->bookFee);
	ps->setInt(6, booking->bookID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int BookingManager::deleteBooking(Booking* booking)
{
	DBConnection con;

	sql::PreparedStatement* psRetrieveTime;
	psRetrieveTime = con.prepareStatement("SELECT slotID FROM bookings WHERE bookID = ?");
	psRetrieveTime->setInt(1, booking->bookID);

	sql::ResultSet* resRetrieveTime = psRetrieveTime->executeQuery();

	int deletedSlotID = -1;
	try
	{
		if (resRetrieveTime->next())
		{
			deletedSlotID = resRetrieveTime->getInt("slotID");
		}
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}
	psRetrieveTime->close();
	delete psRetrieveTime;

	sql::PreparedStatement* psUpdateStatus;
	psUpdateStatus = con.prepareStatement("UPDATE bookingslots SET status = 0 WHERE slotID = ?");
	psUpdateStatus->setInt(1, deletedSlotID);

	int numRowsAffectedStatus = psUpdateStatus->executeUpdate();

	psUpdateStatus->close();
	delete psUpdateStatus;

	sql::PreparedStatement* psDeleteBooking;
	psDeleteBooking = con.prepareStatement("DELETE FROM bookings WHERE bookID =  ?");
	psDeleteBooking->setInt(1, booking->bookID);

	int numRowsAffectedDelete = psDeleteBooking->executeUpdate();

	psDeleteBooking->close();
	delete psDeleteBooking;

	if (numRowsAffectedStatus > 0 && numRowsAffectedDelete > 0)
	{
		return deletedSlotID;
	}
	else
	{
		return -1;
	}
}

void BookingManager::displayAllBooking()
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM bookings");

	sql::ResultSet* res = ps->executeQuery();

	std::cout << "|***************************** All Bookings ******************************|\n";
	std::cout << "===========================================================================\n";
	std::cout << "| Booking ID | Slot ID | Booking Slot | Customer ID | PT ID | Booking Fee |\n";
	std::cout << "===========================================================================\n";

	while (res->next())
	{
		std::cout	<< "| " << std::setw(10) << res->getInt("bookID") << " | " << std::setw(7) << res->getInt("slotID")
					<< " | " << std::setw(12) << res->getString("bookSlot") << " | " << std::setw(11) << res->getInt("custID")
					<< " | " << std::setw(5) << res->getInt("ptID") << " | " << std::setw(11) << res->getDouble("bookFee") << " |\n";
	}
	std::cout << "===========================================================================\n";

	res->close();
	delete res;
	delete ps;
}

Booking* BookingManager::getBooking(int bookID)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM bookings WHERE bookID =  ?");
	ps->setInt(1, bookID);

	sql::ResultSet* res = ps->executeQuery();
	Booking* booking = NULL;

	if (res->next())
	{
		booking = new Booking();
		booking->bookID = res->getInt("bookID");
		booking->slotID = res->getInt("slotID");
		booking->bookSlot = res->getString("bookSlot");
		booking->custID = res->getInt("custID");
		booking->ptID = res->getInt("ptID");
		booking->bookFee = res->getDouble("bookFee");
	}
	res->close();
	delete res;
	delete ps;

	return booking;
}

Booking* BookingManager::displayAllBookingSlots()
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM bookingSlots");

	sql::ResultSet* res = ps->executeQuery();

	std::cout << "|***** All Booking Slots *****|\n";
	std::cout << "===============================\n";
	std::cout << "| Slot ID |   Time   | Status |\n";
	std::cout << "===============================\n";

	while (res->next())
	{
		std::cout << "| " << std::setw(7) << res->getInt("slotID") << " | " << std::setw(8) << res->getString("time")
			<< " | " << std::setw(6) << res->getString("status") << " |\n";
	}
	std::cout << "===============================\n";

	res->close();
	delete res;
	delete ps;
}

int BookingManager::displayAvailableSlots()
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT * FROM bookingslots WHERE status = 0");

	sql::ResultSet* res;
	res = ps->executeQuery();

	std::cout << "|***** Available Booking Slots ******|\n";
	std::cout << "======================================\n";
	std::cout << "|  Slot ID  |    Time    |  Status   |\n";
	std::cout << "======================================\n";
	
	while (res->next())
	{
		std::cout << "| " << std::setw(9) << res->getInt("slotID") << " | " << std::setw(10) << res->getString("time")
			<< " | " << std::setw(6) << "AVAILABLE |\n";
	}
	std::cout << "======================================\n";

	res->close();
	delete ps;
}

bool BookingManager::bookSlot(int slotID, int custID, int ptID, double totalFee)
{
	DBConnection con;

	sql::PreparedStatement* psCheck;
	psCheck = con.prepareStatement("SELECT * FROM bookingslots WHERE slotID = ? AND status = 0");
	psCheck->setInt(1, slotID);

	sql::ResultSet* resCheck;
	resCheck = psCheck->executeQuery();

	if (resCheck->next())
	{
		sql::PreparedStatement* psBook;
		psBook = con.prepareStatement("UPDATE bookingslots SET status = 1 WHERE slotID = ? AND status = 0");
		psBook->setInt(1, slotID);

		int numRowsAffected = psBook->executeUpdate();

		psCheck->close();
		delete psCheck;
		psBook->close();
		delete psBook;

		if (numRowsAffected > 0)
		{
			Booking* booking = new Booking();
			booking->slotID = slotID;
			booking->bookSlot = getTimeSlot(slotID);
			booking->custID = custID;
			booking->ptID = ptID;
			booking->bookFee = totalFee;

			int addBookingResult = addBooking(booking);

			delete booking;

			return addBookingResult > 0;
		}
	}
	psCheck->close();
	delete psCheck;

	return false;
}

bool BookingManager::updateBookSlot(int bookingID, int newSlotID, int newPtID, double totalFee)
{
	DBConnection con;

	if (!validateSlot(newSlotID))
	{
		std::cerr << "Invalid slot ID." << std::endl;
		return false;
	}

	PtManager ptManager;
	if (!ptManager.validatePersonalTrainer(newPtID))
	{
		std::cerr << "Invalid personal trainer ID." << std::endl;
		return false;
	}

	if (!clearPreviousBookingStatus(bookingID))
	{
		std::cerr << "Failed to clear previous booking status." << std::endl;
		return false;
	}

	Booking* existingBooking = getBooking(bookingID);

	if (!existingBooking)
	{
		std::cerr << "Invalid booking ID." << std::endl;
		return false;
	}

	existingBooking->slotID = newSlotID;
	existingBooking->bookSlot = getTimeSlot(newSlotID);
	existingBooking->ptID = newPtID;
	existingBooking->bookFee = totalFee;

	int updateResult = updateBooking(existingBooking);

	if (updateResult <= 0)
	{
		std::cerr << "Failed to update the booking." << std::endl;
		delete existingBooking;
		return false;
	}

	sql::PreparedStatement* psUpdateSlot;
	psUpdateSlot = con.prepareStatement("UPDATE bookingslots SET status = 1 WHERE slotID = ?");
	psUpdateSlot->setInt(1, newSlotID);

	int numRowsAffected = psUpdateSlot->executeUpdate();

	psUpdateSlot->close();
	delete psUpdateSlot;

	if (numRowsAffected <= 0)
	{
		std::cerr << "Failed to update the status of the new slot." << std::endl;
		delete existingBooking;
		return false;
	}

	delete existingBooking;
	return true;
}

bool BookingManager::validateSlot(int slotID)
{
	DBConnection con;

	sql::PreparedStatement* psCheck;
	psCheck = con.prepareStatement("SELECT * FROM bookingslots WHERE slotID = ? AND status = 0");
	psCheck->setInt(1, slotID);

	sql::ResultSet* resCheck;
	resCheck = psCheck->executeQuery();

	bool isValid = resCheck->next();

	psCheck->close();
	delete psCheck;

	return isValid;
}

int BookingManager::displayCustomerBookings(int custID)
{
	DBConnection con;

	sql::PreparedStatement* ps;
	ps = con.prepareStatement("SELECT b.bookID, b.bookSlot, p.ptName, b.bookFee FROM bookings b "
								"JOIN personaltrainer p ON b.ptID = p.ptID "
								"WHERE b.custID = ?");
	ps->setInt(1, custID);

	sql::ResultSet* res;
	res = ps->executeQuery();

	std::cout << "| ****************************** Your Bookings ****************************** |\n";
	std::cout << "===============================================================================\n";
	std::cout << "|  Booking ID  |  Booking Slot  |    Trainer Name    |   Total   |   Status   |\n";
	std::cout << "===============================================================================\n";

	while (res->next())
	{
		std::cout << "| " << std::setw(12) << res->getInt("bookID") << " | " << std::setw(14) << res->getString("bookSlot")
			<< " | " << std::setw(18) << res->getString("ptName") << " | " << std::setw(4) << "RM " << std::setw(4) 
			<< std::fixed << std::setprecision(2) << res->getDouble("bookFee") << " |  CONFIRMED |\n";
	}
	std::cout << "===============================================================================\n";
	res->close();
	delete ps;

	return 0;
}

std::string BookingManager::getTimeSlot(int slotID)
{
	DBConnection con;

	sql::PreparedStatement* psGetTime;
	psGetTime = con.prepareStatement("SELECT time FROM bookingslots WHERE slotID = ?");
	psGetTime->setInt(1, slotID);

	sql::ResultSet* resTime = psGetTime->executeQuery();

	std::string time;

	if (resTime->next()) {
		time = resTime->getString("time");
	}
	psGetTime->close();
	delete psGetTime;

	return time;
}

bool BookingManager::clearPreviousBookingStatus(int bookingID)
{
	DBConnection con;

	sql::PreparedStatement* psFindPreviousBooking;
	psFindPreviousBooking = con.prepareStatement("SELECT * FROM bookings WHERE bookID = ?");
	psFindPreviousBooking->setInt(1, bookingID);

	sql::ResultSet* resPreviousBooking = psFindPreviousBooking->executeQuery();

	if (resPreviousBooking->next())
	{
		int previousSlotID = resPreviousBooking->getInt("slotID");

		sql::PreparedStatement* psClearPreviousBookingStatus;
		psClearPreviousBookingStatus = con.prepareStatement("UPDATE bookingslots SET status = 0 WHERE slotID = ?");
		psClearPreviousBookingStatus->setInt(1, previousSlotID);

		int numRowsAffected = psClearPreviousBookingStatus->executeUpdate();

		psFindPreviousBooking->close();
		delete psFindPreviousBooking;
		resPreviousBooking->close();
		delete resPreviousBooking;
		psClearPreviousBookingStatus->close();
		delete psClearPreviousBookingStatus;

		return numRowsAffected > 0;
	}
	psFindPreviousBooking->close();
	delete psFindPreviousBooking;
	resPreviousBooking->close();
	delete resPreviousBooking;

	return true;
}

bool BookingManager::hasBooking(int custID)
{
	DBConnection con;

	try
	{
		sql::PreparedStatement* ps;
		ps = con.prepareStatement("SELECT * FROM bookings WHERE custID = ?");
		ps->setInt(1, custID);

		sql::ResultSet* res;
		res = ps->executeQuery();

		bool hasBooking = res->next();

		res->close();
		delete res;
		delete ps;

		return hasBooking;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return false;
	}
}

double BookingManager::calculateTotal(int slotID, int ptID)
{
	const double flatRate = 6.0;
	double ptRate = PtManager::getTrainerRate(ptID);

	double totalFee = flatRate + ptRate;
	return totalFee;	
}
#include "Booking.h"
#include "DBConnection.h"

#ifndef BookingManager_H
#define BookingManager_H

class BookingManager
{
private:
	DBConnection dbConnection;

public:
	int addBooking(Booking* booking);
	int updateBooking(Booking* booking);
	int deleteBooking(Booking* booking);
	void displayAllBooking();
	Booking* getBooking(int bookID);
	Booking* displayAllBookingSlots();
	int displayAvailableSlots();
	bool bookSlot(int slotID, int custID, int ptID, double bookFee);
	bool updateBookSlot(int bookingID, int newSlotID, int newPtID, double totalFee);
	bool validateSlot(int slotID);
	int displayCustomerBookings(int custID);
	std::string getTimeSlot(int slotID);
	bool clearPreviousBookingStatus(int bookingID);
	bool hasBooking(int custID);
	double calculateTotal(int slotID, int ptID);
};

#endif
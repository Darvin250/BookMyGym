/*	Name		: Darvin Ravichandran
*	Matric No	: B032310776
*	Workshop 1	
*/

//Header Files used
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
using namespace std;

//Custom Header Files
#include "CustomerManager.h"
#include "BookingManager.h"
#include "StaffManager.h"
#include "PtManager.h"

//Function Declaration
void adminLogin();
void adminMenu(Staff loggedInStaff);
void adminBooking(Staff loggedInStaff);
void adminBookingDelete(Staff loggedInStaff);
void adminCustomer(Staff loggedInStaff);
void adminCustomerDelete(Staff loggedInStaff);
void adminPersonalTrainer(Staff loggedInStaff);
void adminPersonalTrainerAdd(Staff loggedInStaff);
void adminPersonalTrainerUpdate(Staff loggedInStaff);
void adminPersonalTrainerDelete(Staff loggedInStaff);

void userLogin();
void userSignUp();

void bookingMenu(Customer loggedInCustomer);
void bookingNew(Customer loggedInCustomer);
void bookingUpdate(Customer loggedInCustomer);
void bookingDelete(Customer loggedInCustomer);


int main()
{
	system("cls");
	CustomerManager customerManager;
	int loginOption;

	std::cout << "============================================================\n";
	std::cout << "|*****************| Welcome to BookMyGym |*****************|\n";
	std::cout << "|*****************|  Be Fit Be Healthy   |*****************|\n";
	std::cout << "============================================================\n";
	std::cout << "|******************** Login   (1) *************************|\n";
	std::cout << "|******************** Sign Up (2) *************************|\n";
	std::cout << "|******************** Admin   (3) *************************|\n";
	std::cout << "|******************** Exit    (0) *************************|\n";
	std::cout << "|******************** Input : ";

	if (std::cin >> loginOption)
	{
		if (loginOption == 1)
		{
			userLogin();
		}
		else if (loginOption == 2)
		{
			userSignUp();
		}
		else if (loginOption == 3)
		{
			adminLogin();
		}
		else if (loginOption == 0)
		{
			std::cout << "|***************| Thank you for using BookMyGym |***************|\n";
			exit(0);
		}
		else
		{
			std::cout << "\n*********************| Invalid Input |**********************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			main();
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		main();
	}

	return 0;
}

void adminLogin()
{
	system("cls");
	Staff* staff = new Staff();
	StaffManager staffManager;
	Staff loggedInStaff;

	std::cout << "\n============================================================\n";
	std::cout << "*********************| Welcome Admin |**********************\n";
	std::cout << "*************************| Login |**************************\n";
	std::cout << "|****** Admin Email : ";
	std::cin >> staff->staffEmail;
	std::cout << "|****** Password    : ";
	char ch;
	while (true)
	{
		ch = _getch();
		if (ch == 13) //ASCII Code for Enter
		{
			break;
		}
		else if (ch == 8) //ASCII Code for Backspace
		{
			if (!staff->staffPass.empty()) {
				staff->staffPass.pop_back();
				std::cout << "\b \b";
			}
		}
		else {
			staff->staffPass += ch;
			std::cout << '*';
		}
	}

	if (staffManager.checkCredentials(staff->staffEmail, staff->staffPass, loggedInStaff))
	{
		std::cout << "\n*******************| Login Successfull |*******************\n";
		std::cout << "\n*******************| Welcome Admin |*******************\n";
		adminMenu(loggedInStaff);
	}
	else
	{
		std::cout << "\n******************| Login Unsuccessfull |******************\n";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminLogin();
	}
}

void adminMenu(Staff loggedInStaff)
{
	system("cls");
	int adminOption;

	std::cout << "|********************| Welcome " << loggedInStaff.staffName << "|*********************|\n";
	std::cout << "===============================================================\n";
	std::cout << "|************** Manage Bookings          (1) *****************|\n";
	std::cout << "|************** Manage Customer          (2) *****************|\n";
	std::cout << "|************** Manage Personal Trainers (3) *****************|\n";
	std::cout << "|************** Sign Out                 (0) *****************|\n";
	std::cout << "|************** Input : ";

	if (std::cin >> adminOption)
	{
		if (adminOption == 1)
		{
			adminBooking(loggedInStaff);
		}

		else if (adminOption == 2)
		{
			adminCustomer(loggedInStaff);
		}

		else if (adminOption == 3)
		{
			adminPersonalTrainer(loggedInStaff);
		}
		else if (adminOption == 0)
		{
			main();
		}
		else
		{
			std::cout << "\n********************| Invalid Selection |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminMenu(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminMenu(loggedInStaff);
	}
}

void adminBooking(Staff loggedInStaff)
{
	system("cls");
	Booking* booking = new Booking();
	BookingManager bookingManager;

	int bookingOption;

	std::cout << "============================================================\n";
	std::cout << "*********************| Manage Booking |*********************\n";
	std::cout << "============================================================\n\n";

	std::cout << "========================================================\n";
	std::cout << "|********* View All Booking       (1) *****************|\n";
	std::cout << "|********* Delete Booking         (2) *****************|\n";
	std::cout << "|********* View All Booking Slots (3) *****************|\n";
	std::cout << "|********* Back                   (0) *****************|\n";
	std::cout << "|********* Input : ";

	if (std::cin >> bookingOption)
	{
		if (bookingOption == 1)
		{
			system("cls");
			bookingManager.displayAllBooking();
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminBooking(loggedInStaff);
		}

		else if (bookingOption == 2)
		{
			adminBookingDelete(loggedInStaff);
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminBooking(loggedInStaff);
		}

		else if (bookingOption == 3)
		{
			system("cls");
			bookingManager.displayAllBookingSlots();
			std::cout << "\n***| Press Enter to Go Back |***";
			_getch();
			adminBooking(loggedInStaff);
		}
		else if (bookingOption == 0)
		{
			adminMenu(loggedInStaff);
		}
		else
		{
			std::cout << "\n********************| Invalid Selection |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminBooking(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminBooking(loggedInStaff);
	}
}

void adminBookingDelete(Staff loggedInStaff)
{
	system("cls");
	Booking* booking = new Booking();
	BookingManager bookingManager;

	std::cout << "============================================================\n";
	std::cout << "*********************| Delete Booking |**********************\n";
	std::cout << "============================================================\n";

	bookingManager.displayAllBooking();

	int bookingID;
	std::cout << "\nEnter the Booking ID you want to delete: ";

	if (std::cin >> bookingID)
	{
		Booking* existingBooking = bookingManager.getBooking(bookingID);

		if (existingBooking)
		{
			int deletedSlotID = bookingManager.deleteBooking(existingBooking);

			if (deletedSlotID > 0)
			{

				if (bookingManager.clearPreviousBookingStatus(deletedSlotID))
				{
					system("cls");
					std::cout << "============================================================\n";
					std::cout << "***************| Booking Deleted Successfull |**************\n";
					std::cout << "============================================================\n";
					std::cout << "\n***************| Press Enter to Go Back |******************";
					_getch();
					adminBooking(loggedInStaff);
				}
				else
				{
					std::cout << "\n************| Failed to Reset Previous Booking |************";
					std::cout << "\n******************| Press Enter to retry |******************";
					_getch();
					adminBookingDelete(loggedInStaff);
				}
			}
			else
			{
				std::cout << "\n****************| Failed to Delete Booking |****************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				adminBookingDelete(loggedInStaff);
			}
			delete existingBooking;
		}
		else
		{
			std::cout << "\n*******************| Invalid Booking ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminBookingDelete(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminBookingDelete(loggedInStaff);
	}
}

void adminCustomer(Staff loggedInStaff)
{
	system("cls");
	Customer* customer = new Customer();
	CustomerManager customerManager;

	int customerOption;

	std::cout << "============================================================\n";
	std::cout << "*********************| Manage Customer |********************\n";
	std::cout << "============================================================\n";

	std::cout << "========================================================\n";
	std::cout << "|********* View All Customer      (1) *****************|\n";
	std::cout << "|********* Delete Customer        (2) *****************|\n";
	std::cout << "|********* Back                   (0) *****************|\n";
	std::cout << "|********* Input : ";

	if (std::cin >> customerOption)
	{
		if (customerOption == 1)
		{
			system("cls");
			customerManager.displayAllCustomer();
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminCustomer(loggedInStaff);
		}

		else if (customerOption == 2)
		{
			adminCustomerDelete(loggedInStaff);
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminCustomer(loggedInStaff);
		}
		else if (customerOption == 0)
		{
			adminMenu(loggedInStaff);
		}
		else
		{
			std::cout << "\n********************| Invalid Selection |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminCustomer(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminCustomer(loggedInStaff);
	}
}

void adminCustomerDelete(Staff loggedInStaff)
{
	system("cls");
	CustomerManager customerManager;

	std::cout << "============================================================\n";
	std::cout << "********************| Delete Customer |*********************\n";
	std::cout << "============================================================\n";

	customerManager.displayAllCustomer();

	int custID;
	std::cout << "\nEnter the Customer ID you want to delete: ";

	if (std::cin >> custID)
	{
		Customer* existingCustomer = customerManager.getCustomer(custID);

		if (existingCustomer)
		{
			int numRowsAffected = customerManager.deleteCustomer(existingCustomer);

			if (numRowsAffected > 0)
			{
				system("cls");
				std::cout << "============================================================\n";
				std::cout << "**************| Customer Deleted Successfully |*************\n";
				std::cout << "============================================================\n";
				std::cout << "\n***************| Press Enter to Go Back |******************";
				_getch();
				adminCustomer(loggedInStaff);
			}
			else
			{
				std::cout << "\n***************| Failed to Delete Customer |****************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				adminCustomerDelete(loggedInStaff);
			}
			delete existingCustomer;
		}
		else
		{
			std::cout << "\n******************| Invalid Customer ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminCustomerDelete(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminCustomerDelete(loggedInStaff);
	}
}

void adminPersonalTrainer(Staff loggedInStaff)
{
	system("cls");
	PtManager ptManager;

	int trainerOption;

	std::cout << "============================================================\n";
	std::cout << "*****************| Manage Personal Trainer |****************\n";
	std::cout << "============================================================\n";

	std::cout << "===========================================================\n";
	std::cout << "|********* View All Personal Trainer (1) *****************|\n";
	std::cout << "|********* Add Personal Trainer      (2) *****************|\n";
	std::cout << "|********* Update Personal Trainer   (3) *****************|\n";
	std::cout << "|********* Delete Personal Trainer   (4) *****************|\n";
	std::cout << "|********* Back                      (0) *****************|\n";
	std::cout << "|********* Input : ";

	if (std::cin >> trainerOption)
	{
		if (trainerOption == 1)
		{
			system("cls");
			ptManager.displayPersonalTrainer();
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminPersonalTrainer(loggedInStaff);
		}
		else if (trainerOption == 2)
		{
			adminPersonalTrainerAdd(loggedInStaff);
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminPersonalTrainer(loggedInStaff);
		}
		else if (trainerOption == 3)
		{
			system("cls");
			adminPersonalTrainerUpdate(loggedInStaff);
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminPersonalTrainer(loggedInStaff);
		}
		else if (trainerOption == 4)
		{
			system("cls");
			adminPersonalTrainerDelete(loggedInStaff);
			std::cout << "\n******************| Press Enter to Go Back |******************";
			_getch();
			adminPersonalTrainer(loggedInStaff);
		}
		else if (trainerOption == 0)
		{
			adminMenu(loggedInStaff);
		}
		else
		{
			std::cout << "\n********************| Invalid Selection |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminBooking(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminBooking(loggedInStaff);
	}
}

void adminPersonalTrainerAdd(Staff loggedInStaff)
{
	system("cls");
	PT* pt = new PT();
	PtManager ptManager;

	std::cout << "\n============================================================\n";
	std::cout << "*******************| Add Personal Trainer |*******************\n";
	std::cout << "|***** Trainer Name : ";
	std::cin >> pt->ptName;
	std::cout << "|***** Trainer Number : ";
	std::cin >> pt->ptNum;
	std::cout << "|***** Years of Experience : ";
	std::cin >> pt->yearsExperience;

	const double flatRate = 6.0;
	double total = flatRate * pt->yearsExperience;

	pt->ptRate = total;

	int numRowsAffedted = ptManager.addPersonalTrainer(pt);

	if (numRowsAffedted > 0)
	{
		std::cout << "\n*********| Succefully Added Personal Trainer |*********\n";
		std::cout << "\n*************| Press Enter to Go Back |****************";
		_getch();
		adminPersonalTrainer(loggedInStaff);
	}
	else
	{
		std::cout << "\n*******************| Unsuccessful |********************\n";
		std::cout << "\n***************| Press Enter to retry |****************";
		_getch();
		adminPersonalTrainerAdd(loggedInStaff);
	}
}

void adminPersonalTrainerUpdate(Staff loggedInStaff)
{
	system("cls");
	PtManager ptManager;

	std::cout << "============================================================\n";
	std::cout << "*****************| Update Personal Trainer |****************\n";
	std::cout << "============================================================\n";

	ptManager.displayPersonalTrainer();
	int ptID;
	std::cout << "\nEnter the Trainer ID you want to update: ";

	if (std::cin >> ptID)
	{
		PT* existingTrainer = ptManager.getTrainer(ptID);

		if (existingTrainer)
		{
			std::cout << "|***** Trainer Name : ";
			std::cin >> existingTrainer->ptName;
			std::cout << "|***** Trainer Number : ";
			std::cin >> existingTrainer->ptNum;
			std::cout << "|***** Years of Experience : ";
			std::cin >> existingTrainer->yearsExperience;

			const double flatRate = 6.0;
			existingTrainer->ptRate = flatRate * existingTrainer->yearsExperience;

			int numRowsAffected = ptManager.updatePersonalTrainer(existingTrainer);

			if (numRowsAffected > 0)
			{
				system("cls");
				std::cout << "============================================================\n";
				std::cout << "**************| Trainer Updated Successfully |**************\n";
				std::cout << "============================================================\n";
				std::cout << "\n***************| Press Enter to Go Back |******************";
				_getch();
				adminPersonalTrainer(loggedInStaff);
			}
			else
			{
				std::cout << "\n****************| Failed to Update Trainer |****************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				adminPersonalTrainerUpdate(loggedInStaff);
			}
			delete existingTrainer;
		}
		else
		{
			std::cout << "\n*******************| Invalid Trainer ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminPersonalTrainerUpdate(loggedInStaff);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminPersonalTrainerUpdate(loggedInStaff);
	}
}

void adminPersonalTrainerDelete(Staff loggedInStaff)
{
	system("cls");
	PtManager ptManager;

	std::cout << "============================================================\n";
	std::cout << "****************| Delete Personal Trainer |*****************\n";
	std::cout << "============================================================\n";

	ptManager.displayPersonalTrainer();

	int ptID;
	std::cout << "\nEnter the Trainer ID you want to delete: ";

	if (std::cin >> ptID)
	{
		PT* existingTrainer = ptManager.getTrainer(ptID);

		if (existingTrainer)
		{
			int numRowsAffected = ptManager.deletePersonalTrainer(existingTrainer);

			if (numRowsAffected > 0)
			{
				system("cls");
				std::cout << "============================================================\n";
				std::cout << "**************| Trainer Deleted Successfully |**************\n";
				std::cout << "============================================================\n";
				std::cout << "\n***************| Press Enter to Go Back |******************";
				_getch();
				adminPersonalTrainer(loggedInStaff);


			}
			else
			{
				std::cout << "\n************| Failed to Delete Personal Trainer |*************";
				std::cout << "\n*******************| Press Enter to retry |*******************";
				_getch();
				adminPersonalTrainerDelete(loggedInStaff);
			}					
		}
		else
		{
			std::cout << "\n*******************| Invalid Trainer ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			adminPersonalTrainerDelete(loggedInStaff);
		}
		delete existingTrainer;
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		adminPersonalTrainerDelete(loggedInStaff);
	}
	
}

void userLogin()
{
	system("cls");
	Customer* customer = new Customer();
	CustomerManager customerManager;
	Customer loggedInCustomer;

	std::cout << "\n============================================================\n";
	std::cout << "|************************| Login |*************************|\n";
	std::cout << "|****** Username : ";
	std::cin >> customer->custEmail;

	if (customerManager.is_valid(customer->custEmail))
	{
		std::cout << "|****** Password : ";
		char ch;
		while (true)
		{
			ch = _getch();
			if (ch == 13) //ASCII Code for Enter
			{
				break;
			}
			else if (ch == 8) //ASCII Code for Backspace
			{         
				if (!customer->custPass.empty()) {
					customer->custPass.pop_back();
					std::cout << "\b \b";        
				}
			}
			else {
				customer->custPass += ch;
				std::cout << '*';
			}
		}
	
		if (customerManager.checkCredentials(customer->custEmail, customer->custPass, loggedInCustomer))
		{
			system("cls");
			std::cout << "\n========================================================";
			std::cout << "\n|****************| Login Successfull |*****************|";
			std::cout << "\n========================================================";
			
			bookingMenu(loggedInCustomer);
		}
		else
		{
			std::cout << "\n******************| Login Unsuccessfull |******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			userLogin();
		}
	}
	else
	{
		std::cout << "\n******************| Invalid Email Format |******************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		userLogin();
	}
	delete customer;
	
}

void userSignUp()
{
	system("cls");
	Customer* customer = new Customer();
	CustomerManager customerManager;

	std::cout << "\n============================================================\n";
	std::cout << "************************| Sign Up |*************************\n";
	std::cout << "|***** Email : ";
	std::cin >> customer->custEmail;
	if (customerManager.is_valid(customer->custEmail))
	{
		std::cout << "|*****	Name : ";
		std::cin >> customer->custName;
		std::cout << "|*****	Pass : ";
		char ch;
		while (true)
		{
			ch = _getch();
			if (ch == 13) //ASCII Code for Enter
			{
				break;
			}
			else if (ch == 8) //ASCII Code for Backspace
			{
				if (!customer->custPass.empty()) {
					customer->custPass.pop_back();
					std::cout << "\b \b";
				}
			}
			else {
				customer->custPass += ch;
				std::cout << '*';
			}
		}

		while (!customerManager.passwordCheck(customer->custPass))
		{
			std::cout << "Invalid password. Please try again:\n";
			std::cout << "|***** Pass : ";
			std::cin >> customer->custPass;
		}
		std::cout << "\n|*****	Year of Birth : ";
		std::cin >> customer->custDOB;
		std::cout << "|*****	Phone Number : ";
		std::cin >> customer->custNum;

		int numRowsAffedted = customerManager.addCustomer(customer);

		if (numRowsAffedted > 0)
		{
			std::cout << "\n***********| You Have Succefully Signed Up |**************\n";
			std::cout << "\n****************| Press Enter to Login |******************";
			_getch();
			userLogin();
		}
		else
		{
			std::cout << "\n*******************| Unsuccessful Sign |********************\n";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			userSignUp();
		}
	}
	else
	{
		std::cout << "\n******************| Invalid Email Format |******************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		userSignUp();
	}
}

void bookingMenu(Customer loggedInCustomer)
{
	system("cls");
	int bookingOption;

	std::cout << "\n|******************| Welcome " << loggedInCustomer.custName << "|*******************|";
	std::cout << "\n========================================================\n";
	std::cout << "|***************** New Booking    (1) *****************|\n";
	std::cout << "|***************** Update Booking (2) *****************|\n";
	std::cout << "|***************** Delete Booking (3) *****************|\n";
	std::cout << "|***************** Sign Out       (0) *****************|\n";
	std::cout << "|***************** Input : ";

	if (std::cin >> bookingOption)
	{
		if (bookingOption == 1)
		{
			bookingNew(loggedInCustomer);
		}

		else if (bookingOption == 2)
		{
			bookingUpdate(loggedInCustomer);
		}

		else if (bookingOption == 3)
		{
			bookingDelete(loggedInCustomer);
		}
		else if (bookingOption == 0)
		{
			main();
		}
		else
		{
			std::cout << "\n********************| Invalid Selection |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			bookingMenu(loggedInCustomer);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		bookingMenu(loggedInCustomer);
	}
}

void bookingNew(Customer loggedInCustomer)
{
	system("cls");
	BookingManager bookingManager;

	std::cout << "============================================================\n";
	std::cout << "**********************| New Booking |***********************\n";
	std::cout << "============================================================\n\n";

	bookingManager.displayAvailableSlots();

	int selectedSlotID;
	std::cout << "\nEnter the Slot ID you want to book: ";

	if (std::cin >> selectedSlotID)
	{
		if (bookingManager.validateSlot(selectedSlotID))
		{
			system("cls");

			PtManager ptManager;
			ptManager.displayPersonalTrainer();

			int selectedPtID;
			std::cout << "\nEnter the Trainer ID you want to book: ";

			if (std::cin >> selectedPtID)
			{
				if (ptManager.validatePersonalTrainer(selectedPtID))
				{
					double totalFee = bookingManager.calculateTotal(selectedSlotID, selectedPtID);

					if (bookingManager.bookSlot(selectedSlotID, loggedInCustomer.custID, selectedPtID, totalFee))
					{
						system("cls");
						std::cout << "============================================================\n";
						std::cout << "******************| Booking Successfull |*******************\n";
						std::cout << "============================================================\n\n";

						bookingManager.displayCustomerBookings(loggedInCustomer.custID);
						std::cout << "\n***************| Press Enter to Go Back |******************";
						_getch();
						bookingMenu(loggedInCustomer);
					}
					else
					{
						std::cout << "\n********| Failed to book the slot or personal trainer |************";
						std::cout << "\n*********************| Press Enter to retry |**********************";
						_getch();
						bookingNew(loggedInCustomer);
					}
				}
				else
				{
					std::cout << "\n******************| Invalid Personal Trainer ID |******************";
					std::cout << "\n*********************| Press Enter to retry |**********************";
					_getch();
					bookingNew(loggedInCustomer);
				}
			}
			else
			{
				std::cout << "\n*********************| Invalid Input |**********************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				bookingNew(loggedInCustomer);
			}
		}
		else
		{
			std::cout << "\n********************| Invalid Slot ID |*********************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			bookingNew(loggedInCustomer);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		bookingNew(loggedInCustomer);
	}
}

void bookingUpdate(Customer loggedInCustomer)
{
	system("cls");
	BookingManager bookingManager;

	if (!bookingManager.hasBooking(loggedInCustomer.custID))
	{
		std::cout << "*******************| No Existing Booking |********************\n";
		std::cout << "******************| Press Enter to go back |******************";
		_getch();
		bookingMenu(loggedInCustomer);
	}

	std::cout << "============================================================\n";
	std::cout << "*********************| Update Booking |*********************\n";
	std::cout << "============================================================\n\n";

	bookingManager.displayCustomerBookings(loggedInCustomer.custID);

	int bookingID;
	std::cout << "\nEnter the Booking ID you want to update: ";

	if (std::cin >> bookingID)
	{
		Booking* existingBooking = bookingManager.getBooking(bookingID);

		if (existingBooking && existingBooking->custID == loggedInCustomer.custID)
		{
			system("cls");

			bookingManager.displayAvailableSlots();

			int selectedSlotID;
			std::cout << "\nEnter the new Slot ID: ";

			if (std::cin >> selectedSlotID)
			{
				if (bookingManager.validateSlot(selectedSlotID))
				{
					system("cls");

					PtManager ptManager;
					ptManager.displayPersonalTrainer();

					int selectedPtID;
					std::cout << "\nEnter the new Trainer ID: ";

					if (std::cin >> selectedPtID)
					{
						if (ptManager.validatePersonalTrainer(selectedPtID))
						{
							double totalFee = bookingManager.calculateTotal(selectedSlotID, selectedPtID);
							existingBooking->bookSlot = bookingManager.getTimeSlot(selectedSlotID);
							existingBooking->ptID = selectedPtID;

							bool updateResult = bookingManager.updateBookSlot(existingBooking->bookID, selectedSlotID, selectedPtID, totalFee);

							if (updateResult > 0)
							{
								system("cls");
								std::cout << "============================================================\n";
								std::cout << "***************| Booking Updated Successfull |**************\n";
								std::cout << "============================================================\n";
								std::cout << "\n***************| Press Enter to Go Back |******************";
								_getch();
								bookingMenu(loggedInCustomer);
							}
							else
							{
								std::cout << "\n********************| Failed to Update |********************";
								std::cout << "\n******************| Press Enter to retry |******************";
								_getch();
								bookingUpdate(loggedInCustomer);
							}
						}
						else
						{
							std::cout << "\n***************| Invaid Personal Trainer ID |***************";
							std::cout << "\n******************| Press Enter to retry |******************";
							_getch();
							bookingUpdate(loggedInCustomer);
						}
					}
					else
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

						std::cout << "\n*********************| Invalid Input |**********************";
						std::cout << "\n******************| Press Enter to retry |******************";
						_getch();
						bookingUpdate(loggedInCustomer);
					}
					
				}
				else
				{
					std::cout << "\n***************| Invaid Personal Trainer ID |***************";
					std::cout << "\n******************| Press Enter to retry |******************";
					_getch();
					bookingUpdate(loggedInCustomer);
				}
				delete existingBooking;
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

				std::cout << "\n*********************| Invalid Input |**********************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				bookingUpdate(loggedInCustomer);
			}
		}
		else
		{
			std::cout << "\n*******************| Invalid Booking ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			bookingUpdate(loggedInCustomer);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		bookingUpdate(loggedInCustomer);
	}
}

void bookingDelete(Customer loggedInCustomer)
{
	system("cls");
	BookingManager bookingManager;

	if (!bookingManager.hasBooking(loggedInCustomer.custID))
	{
		std::cout << "*******************| No Existing Booking |********************\n";
		std::cout << "******************| Press Enter to go back |******************";
		_getch();
		bookingMenu(loggedInCustomer);
	}

	std::cout << "============================================================\n";
	std::cout << "*********************| Delete Booking |**********************\n";
	std::cout << "============================================================\n";

	bookingManager.displayCustomerBookings(loggedInCustomer.custID);

	int bookingID;
	std::cout << "\nEnter the Booking ID you want to delete: ";

	if (std::cin >> bookingID)
	{
		Booking* existingBooking = bookingManager.getBooking(bookingID);

		if (existingBooking && existingBooking->custID == loggedInCustomer.custID)
		{
			int deletedSlotID = bookingManager.deleteBooking(existingBooking);

			if (deletedSlotID > 0)
			{

				if (bookingManager.clearPreviousBookingStatus(deletedSlotID))
				{
					system("cls");
					std::cout << "============================================================\n";
					std::cout << "***************| Booking Deleted Successfull |**************\n";
					std::cout << "============================================================\n";
					std::cout << "\n***************| Press Enter to Go Back |******************";
					_getch();
					bookingMenu(loggedInCustomer);
				}
				else
				{
					std::cout << "\n************| Failed to Reset Previous Booking |************";
					std::cout << "\n******************| Press Enter to retry |******************";
					_getch();
					bookingDelete(loggedInCustomer);
				}
			}
			else
			{
				std::cout << "\n****************| Failed to Delete Booking |****************";
				std::cout << "\n******************| Press Enter to retry |******************";
				_getch();
				bookingDelete(loggedInCustomer);
			}
			delete existingBooking;
		}
		else
		{
			std::cout << "\n*******************| Invalid Booking ID |*******************";
			std::cout << "\n******************| Press Enter to retry |******************";
			_getch();
			bookingDelete(loggedInCustomer);
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

		std::cout << "\n*********************| Invalid Input |**********************";
		std::cout << "\n******************| Press Enter to retry |******************";
		_getch();
		bookingDelete(loggedInCustomer);
	}
}
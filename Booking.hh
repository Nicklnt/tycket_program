/**
 * @brief File that contain the class Booking
 * 
 */

#ifndef CLASS_BOOKING
#define CLAS_BOOKING
#include <string>
#include <iostream>
using std::string;

class Booking
{
public:
        string bookingN, bDate, bTime, bDepar, bDestiny, bClass, firstN, secondN, bFnumber;
        int seatB, seatF, seatE, rowB, rowF, rowE, bType;
        void showInformation(){std::cout << bookingN << "," << bDepar << "," << bDestiny << "," << bDate << "," << bTime << "," <<bClass << "," << firstN << ","<< secondN << std::endl;}

};

#endif
/**
 * @brief File that contain the class Flight
 * 
 */

#ifndef CLASS_FLIGHT
#define CLASS_FLIGHT
#include <string>
#include <iostream>
using std::string;

class Flight
{
public:
        string fDepar, fDestiny, fDate, fTime, flightN, fSeatsF, fSeatsE, fSeatsB;
        int fType;
        bool cancelF; // flag for cancel flight

        void showInformation (){std::cout << flightN << "," << fDepar << "," << fDestiny << "," << fDate << "," << fTime << "," << fSeatsF << "," << fSeatsB << "," << fSeatsE << "," << fType << std::endl;}
};

#endif
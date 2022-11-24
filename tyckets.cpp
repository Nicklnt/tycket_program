/**
 * @file tyckets.cpp
 * @author Nicolas Munoz (you@domain.com)
 * @brief This program read first a file with information of flights and bookings.
 * Second create a document for each booking and finally show those seats that still available.
 * @version 0.1
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string.h>
#include <iterator>
#include <sstream>
#include <list>
#include "Flight.hh"
#include "Booking.hh"
#include <getopt.h>

using namespace std;
using std::getline;

// functions heads
template <class T>
void showList(T tL);
void createFlightList(list<Flight *> &fLa, string fN);
void createBookList(list<Booking *> &bLa, list<Flight *> &fLa, string fN);
void printTyckets(list<Booking *> &bLa);
void cancelFlight(list<Booking *> &bla, list<Flight *> &fla);
void seatingMap(list<Booking *> &bla, list<Flight *> &fla);

// main function
int main(int argc, char **argv)
{

        list<Flight *> fL;
        list<Flight *> &fLa = fL; // alias to fligt list

        list<Booking *> bL;
        list<Booking *> &bLa = bL; // alias to booking list

        int control = 0;
        bool listF = false, listB = false, cancelF = false;
        try
        {
                if (argc > 2)
                {
                        while ((control = getopt(argc, argv, "f:b:pcm")) != -1)
                        {

                                switch (control)
                                {
                                case 'f':
                                {
                                        // Create a flight list
                                        createFlightList(fLa, optarg);
                                        cout << "Showing list of flights:" << endl;

                                        // Show list av flights
                                        showList(fLa);
                                        cout << "Flight list created" << endl;
                                        listF = true;
                                }
                                break;
                                case 'b':
                                {
                                        // Create a booking list
                                        createBookList(bLa, fLa, optarg);
                                        cout << "Booking list created" << endl;

                                        // Show list av bookings
                                        showList(bLa);
                                        listB = true;
                                }
                                break;
                                case 'p':
                                {
                                        if (listF && listB)
                                        {
                                                // Print tyckets
                                                printTyckets(bLa);
                                        }
                                        else
                                        {
                                                cerr << "Error! missing som argument" << endl;
                                                cout << "Try: [fileName.exe] [-f] text.txt [-b] text.txt [-p]" << endl;
                                        }
                                }
                                break;
                                case 'c':
                                {
                                        if (listF && listB)
                                        {
                                                // Cancel those flights without any booking
                                                cancelFlight(bLa, fLa);
                                                cancelF = true;
                                        }
                                        else
                                        {
                                                cerr << "Error! missing som argument" << endl;
                                                cout << "Try: [fileName.exe] [-f] text.txt [-b] text.txt [-c]" << endl;
                                        }
                                }
                                break;

                                case 'm':
                                {
                                        if (listF && listB && cancelF)
                                        {

                                                // Show the seats avaleable in the flights that are not canceled

                                                seatingMap(bLa, fLa);
                                                cout << "Files with seating report have been created" << endl;
                                        }
                                        else
                                        {
                                                cerr << "Error! missing som argument" << endl;
                                                cout << "Try: [fileName.exe] [-f] text.txt [-b] text.txt [-c]-[-m]" << endl;
                                        }
                                }
                                break;

                                default:
                                        cerr << "Error!" << endl;
                                        cout << "Try: [fileName.exe] [-f] file.txt [-b] file.txt [-p] [-c] [-m]" << endl;
                                        break;
                                }
                        }
                }
                else
                {
                        cerr << "Error. Not enought arguments" << endl;
                        cout << "Try: [fileName.exe] [-f] file.txt [-b] file.txt [-p] [-c] [-m]" << endl;
                }
        }
        catch (...)
        {
                cout<< "unknown error"<<endl;
        }

        return 0;
}

/**
 * @brief function that show a standar list of pointers to objects type Flight
 *
 * @param fL alias till list of pointers type Flight
 */

template <class T>
void showList(T tL)
{
        for (auto it : tL)
        {
                it->showInformation();
        }
}

/**
 * @brief Function that create a List of pointers to object type Flight
 *
 * @param fLa alias till list of pointers type Flight
 */

void createFlightList(list<Flight *> &fLa, string fileName)
{

        Flight *pF;
        int flightNumber = 0;

        string s;

        ifstream myFile(fileName);

        if (myFile.is_open())
        {
                while (getline(myFile, s))
                {
                        pF = new Flight;
                        flightNumber++;

                        fLa.insert(fLa.begin(), pF);

                        stringstream ss(s);
                        while (!ss.eof())
                        {
                                getline(ss, pF->flightN, ',');
                                getline(ss, pF->fDepar, ',');
                                getline(ss, pF->fDestiny, ',');
                                getline(ss, pF->fDate, ',');
                                getline(ss, pF->fTime, ',');
                                getline(ss, pF->fSeatsF, ',');
                                getline(ss, pF->fSeatsB, ',');
                                getline(ss, pF->fSeatsE, ',');
                        }
                        pF->fType = flightNumber;
                        pF->cancelF = false;
                }
                myFile.close();
        }
        else
        {
                cerr << "unable to open file" << endl;
        }
}

/**
 * @brief Function that create a List of pointers to object type Booking
 *
 * @param bLa alias till list of pointers type Booking
 * @param fLa alias till list of pointers type Flight
 */

void createBookList(list<Booking *> &bLa, list<Flight *> &fLa, string fileName)
{
        string s;
        Booking *pB;
        int totalF, totalE, totalB;

        ifstream myFile(fileName);

        if (myFile.is_open())
        {
                // read the file and save the information in each variable of the class Booking
                while (getline(myFile, s))
                {
                        stringstream ss(s);

                        pB = new Booking;
                        bLa.insert(bLa.begin(), pB);

                        while (!ss.eof())
                        {
                                getline(ss, pB->bookingN, ',');
                                getline(ss, pB->bDate, ',');
                                getline(ss, pB->bTime, ',');
                                getline(ss, pB->bDepar, ',');
                                getline(ss, pB->bDestiny, ',');
                                getline(ss, pB->bClass, ',');
                                getline(ss, pB->firstN, ',');
                                getline(ss, pB->secondN, ',');
                        }

                        // iniciate seatB, seatE, seatF and rows
                        pB->seatB = 0;
                        pB->seatE = 0;
                        pB->seatF = 0;
                        pB->rowB = 1;
                        pB->rowE = 1;
                        pB->rowF = 1;
                }

                // iniciate bType, row, total seats bussines, first and economy that every booking has
                list<Flight *>::iterator itf;
                list<Booking *>::iterator itb;

                for (itf = fLa.begin(); itf != fLa.end(); ++itf)
                {
                        totalB = 1;
                        totalE = 1;
                        totalF = 1;
                        for (itb = bLa.begin(); itb != bLa.end(); ++itb)
                        {
                                if ((*itb)->bTime == (*itf)->fTime && (*itb)->bDepar == (*itf)->fDepar && (*itb)->bDestiny == (*itf)->fDestiny)
                                {
                                        (*itb)->bType = (*itf)->fType;
                                        if ((*itb)->bClass == "first")
                                        {
                                                (*itb)->seatF += totalF;
                                                totalF++;
                                                (*itb)->rowF = ((*itb)->seatF + 6) / 7;
                                        }
                                        else if ((*itb)->bClass == "business")
                                        {
                                                (*itb)->seatB += totalB;
                                                totalB++;
                                                (*itb)->rowB = ((*itb)->seatB + 6) / 7;
                                        }
                                        else if ((*itb)->bClass == "economy")
                                        {
                                                (*itb)->seatE += totalE;
                                                totalE++;
                                                (*itb)->rowE = ((*itb)->seatE + 6) / 7;
                                        }

                                        // iniciate variabel that has the value flight number in booking list.
                                        (*itb)->bFnumber = (*itf)->flightN;
                                        // iniciate variabel booking type with flight type.
                                        (*itb)->bType = (*itf)->fType;
                                }
                        }
                }

                myFile.close();
        }
        else
        {
                cerr << "file not open" << endl;
        }
}

/**
 * @brief Funktion that go genom a list av bookings and print out tyckets for each booking
 *
 * @param bLa alias till list of pointers type Flight
 */

void printTyckets(list<Booking *> &bLa)
{
        list<Booking *>::iterator iTb;
        for (iTb = bLa.begin(); iTb != bLa.end(); iTb++)
        {
                string tycketName = "ticket-" + (*iTb)->bookingN + ".txt";
                ofstream myFile(tycketName);

                if (myFile.is_open())
                {
                        // tyckets form
                        myFile << "Booking: " << (*iTb)->bookingN << endl;
                        myFile << "FLIGHT: " << (*iTb)->bFnumber << " DEPARTURE: " << (*iTb)->bDepar << " DESTINATION: " << (*iTb)->bDestiny << "  " << (*iTb)->bDate << "  " << (*iTb)->bTime << endl;
                        myFile << "PASSENGER: " << (*iTb)->firstN << " " << (*iTb)->secondN << endl;
                        myFile << "CLASS: " << (*iTb)->bClass << endl;

                        if ((*iTb)->bClass == "first")
                        {
                                myFile << "ROW: " << (*iTb)->rowF << " SEAT: " << (*iTb)->seatF << endl;
                        }
                        else if ((*iTb)->bClass == "business")
                        {
                                myFile << "ROW: " << (*iTb)->rowB << " SEAT: " << (*iTb)->seatB << endl;
                        }
                        else if ((*iTb)->bClass == "economy")
                        {
                                myFile << "ROW: " << (*iTb)->rowE << " SEAT: " << (*iTb)->seatE << endl;
                        }

                        myFile << "***************" << endl;
                        myFile.close();
                }
                else
                {
                        cerr << "The file could not open" << endl;
                }
        }
}

/**
 * @brief Function that cancel those fligths that doesn't have a booking and create a file with a report
 *
 * @param bla alias till list of pointers type Booking
 * @param fla alias till list of pointers type Flight
 */

void cancelFlight(list<Booking *> &bla, list<Flight *> &fla)
{
        list<Booking *>::iterator itb;
        list<Flight *>::iterator itf;
        int bCounter; // booking counter

        // Find those flights that has a booking
        for (itf = fla.begin(); itf != fla.end(); itf++)
        {
                bCounter = 0;

                for (itb = bla.begin(); itb != bla.end(); itb++)
                {

                        if ((*itf)->fType == (*itb)->bType) // if there is a booking bCounter is gonna increase
                        {

                                bCounter++;

                                break;
                        }
                }

                // if the flight doesn't have a booking
                if (bCounter == 0)
                {
                        ofstream cancelFile;

                        cancelFile.open("cancelFlights.txt", ios::out | ios::app);
                        if (cancelFile.is_open())
                        {
                                cancelFile << "Flight number " << (*itf)->flightN << " whit destiny to " << (*itf)->fDestiny << " att " << (*itf)->fTime << " has been canceleted." << endl;
                                cancelFile.close();
                        }
                        else
                        {
                                cerr << "The file could not be open." << endl;
                        }

                        (*itf)->cancelF = true; // if there is not a booking set cancelF to true
                }
        }
}

/**
 * @brief Function that show the seats map of each flight
 *
 * @param bla alias till list of pointers type Booking
 * @param fla alias till list of pointers type Flight
 */

void seatingMap(list<Booking *> &bla, list<Flight *> &fla)
{
        list<Flight *>::iterator itf;
        list<Booking *>::iterator itb;
        int totalB, totalE, totalF, counter; // variables that help to know the total seats and if a seat is empty or not

        for (itf = fla.begin(); itf != fla.end(); itf++)
        {
                totalB = 0;
                totalE = 0;
                totalF = 0;

                for (itb = bla.begin(); itb != bla.end(); itb++)
                {
                        // if the booking and the fly type is the same total get the value of seat if seat is differente av 0
                        if ((*itf)->fType == (*itb)->bType)
                        {
                                if ((*itb)->seatB > 0)
                                {
                                        totalB = (*itb)->seatB;
                                }
                                if ((*itb)->seatE > 0)
                                {
                                        totalE = (*itb)->seatE;
                                }
                                if ((*itb)->seatF > 0)
                                {
                                        totalF = (*itb)->seatF;
                                }
                        }
                }

                // print out information of flight

                if ((*itf)->cancelF == false)
                {
                        string fileName = to_string((*itf)->fType) + "-seating-report.txt";
                        ofstream myMapFile;
                        myMapFile.open(fileName, ios::out);

                        myMapFile << "Flight " << (*itf)->flightN << ", Departure " << (*itf)->fDepar << ", Destination " << (*itf)->fDestiny << ", Date " << (*itf)->fDate << ", Time " << (*itf)->fTime << endl;
                        myMapFile << "first class" << endl;

                        // print out 1 if the first seat is occupied other wise 0
                        counter = 0;
                        for (int i = 0; i < 2; i++)
                        {
                                for (int j = 0; j < 7; j++)
                                {
                                        if (counter < totalF)
                                        {
                                                myMapFile << "[1]";
                                                counter++;
                                        }
                                        else
                                        {
                                                myMapFile << "[0]";
                                        }
                                        if (j == 1 || j == 4)
                                        {
                                                myMapFile << " ";
                                        }
                                }
                                myMapFile << endl;
                        }
                        // print out 1 if the bussines seat is occupeid other wise 0
                        myMapFile << "business class" << endl;
                        counter = 0;
                        for (int i = 0; i < 3; i++)
                        {
                                for (int j = 0; j < 7; j++)
                                {

                                        if (counter < totalB)
                                        {
                                                myMapFile << "[1]";
                                                counter++;
                                        }
                                        else
                                        {
                                                myMapFile << "[0]";
                                        }
                                        if (j == 1 || j == 4)
                                        {
                                                myMapFile << " ";
                                        }
                                }
                                myMapFile << endl;
                        }
                        // print out 1 if the economy seat is occupeid other wise 0
                        myMapFile << "economy class" << endl;
                        counter = 0;
                        for (int i = 0; i < 4; i++)
                        {
                                for (int j = 0; j < 7; j++)
                                {
                                        if (counter < totalE)
                                        {
                                                myMapFile << "[1]";
                                                counter++;
                                        }
                                        else
                                        {
                                                myMapFile << "[0]";
                                        }
                                        if (j == 1 || j == 4)
                                        {
                                                myMapFile << " ";
                                        }
                                }
                                myMapFile << endl;
                        }
                        myMapFile << "*********************" << endl;
                }
        }
}

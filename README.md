# Tycket_program
The program read the information in two files and print out tyckets base in that information.

To run the program you will need to introduce a convination of the information bellow:
```
.\tyckets.cpp -f fInformation.txt -b booking.txt -p -c -m
```
If you don't add flags a error message its gonna appear.

## -f: create a list of flights fron the file .txt 
### It is necessary to indicate the name of the file.  

Will create a list of flights with the following information: flightnumber,departure,destination,date,time,fseats,bseats,eseats
Example:
```
304,GOT,CPH,2022-10-27,06:30,28,70,112
304,GOT,CPH,2022-10-27,07:30,28,70,112
304,GOT,CPH,2022-10-27,08:30,28,70,112
304,GOT,CPH,2022-10-27,09:30,28,70,112
306,CPH,LHR,2022-10-27,06:30,14,28,70
308,GOT,LGW,2022-10-27,06:30,28,70,112
310,GOT,ARN,2022-10-27,06:30,14,28,70
310,GOT,ARN,2022-10-27,07:30,14,28,70
310,GOT,ARN,2022-10-27,08:30,14,28,70
312,STO,HEL,2022-10-27,06:30,28,70,112
312,STO,HEL,2022-10-27,07:30,28,70,112
312,STO,HEL,2022-10-27,08:30,28,70,112
```


## -b: create a list of flights fron the file .txt  
### It is necessary to indicate the name of the file.

Will create a booking list with the following information: bookingnumber,date,time,departure,destination,seatclass,firstname,surname
Example:
```


1000,2022-10-27,06:30,GOT,LGW,first,Kalle,Kula
1001,2022-10-27,06:30,GOT,LGW,first,Moa,Kula
1002,2022-10-27,06:30,GOT,LGW,first,Johan,Kula
1003,2022-10-27,06:30,GOT,LGW,first,Kalle,Anka
1004,2022-10-27,06:30,GOT,LGW,first,Knatte,Anka
1005,2022-10-27,06:30,GOT,LGW,first,Fnatte,Anka
1006,2022-10-27,06:30,GOT,LGW,first,Tjatte,Anka
1007,2022-10-27,06:30,GOT,LGW,economy,Kajsa,Stinasson
1008,2022-10-27,06:30,GOT,LGW,business,Maja,Johansson
1009,2022-10-27,06:30,GOT,LGW,business,Stefan,Svensson
1010,2022-10-27,06:30,GOT,LGW,business,Maria,Svensson
1011,2022-10-27,06:30,GOT,LGW,business,Ulf,Johansson
1012,2022-10-27,06:30,GOT,LGW,economy,Lisa,Johansson
1013,2022-10-27,06:30,GOT,LGW,economy,Per,Johansson
1014,2022-10-27,06:30,GOT,LGW,economy,Conny,Johansson
1015,2022-10-27,06:30,GOT,LGW,economy,Maja,Johansson
2000,2022-10-27,06:30,GOT,ARN,first,Kalle,Kula
2001,2022-10-27,06:30,GOT,ARN,first,Moa,Kula
2002,2022-10-27,06:30,GOT,ARN,first,Johan,Kula
2003,2022-10-27,06:30,GOT,ARN,first,Kalle,Anka
2004,2022-10-27,06:30,GOT,ARN,first,Knatte,Anka
2005,2022-10-27,06:30,GOT,ARN,first,Fnatte,Anka
2006,2022-10-27,06:30,GOT,ARN,first,Tjatte,Anka
2007,2022-10-27,08:30,STO,HEL,economy,Kajsa,Stinasson
2008,2022-10-27,08:30,STO,HEL,business,Maja,Johansson
2009,2022-10-27,08:30,GOT,ARN,business,Stefan,Svensson
2010,2022-10-27,06:30,GOT,ARN,business,Maria,Svensson
2011,2022-10-27,06:30,GOT,ARN,business,Ulf,Johansson
2012,2022-10-27,08:30,GOT,ARN,economy,Lisa,Johansson
2013,2022-10-27,08:30,GOT,ARN,economy,Per,Johansson
2014,2022-10-27,06:30,STO,HEL,economy,Conny,Johansson
2015,2022-10-27,06:30,STO,HEL,economy,Maja,Johansson
```

## -p: print tyckets for each element in the booking list.
### It is necessary to add the two first parameters.

Will produce the files (ticket-{bookingnumber}.txt):
```
ticket-1001.txt ticket-1002.txt ticket-1003.txt ticket-1004.txt
ticket-1005.txt ticket-1006.txt ticket-1007.txt ticket-1008.txt
... etc
```
### The tickets are created with this format:

```
BOOKING:{bookingnumber} 
FLIGHT:{flight} DEPARTURE:{dep} DESTINATION: {dest} {date} {time}
PASSENGER {firstname} {surname}
CLASS: {seatclass}
ROW {row} SEAT {seatnumber}

```

## -c: cancel fligths that doesn't have a booking, create a file wtih the information.
### It is necessary to add the two first parameters.

## -m: create a file that show the seats maps of each flight.
### It is necessary to add the parameters -f -b -c;
```
Will print a map seats that show those that are free (0) and those that are not (1). 
Row seating is 2-3-2 the all flights
Seats row 1 [  1][  2] -  [  3][  4][  5] - [  6][  7]
Seats row 2 [  8][  9] -  [ 10][ 11][ 12] - [ 13][ 14]
Seats row 3 [ 15][ 16] -  [ 17][ 18][ 19] - [ 20][ 21]
Seats row 4 [ 22][ 23] -  [ 24][ 25][ 26] - [ 27][ 28]
etc .....
```






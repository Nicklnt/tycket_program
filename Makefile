target:
	echo "Running target"
	g++ tyckets.cpp getopt.h Flight.hh Booking.hh -o tyckets
	./tyckets

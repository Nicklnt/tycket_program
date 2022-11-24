target:
	echo "Running target"
	g++ tyckets.cpp Flight.hh Booking.hh -o tyckets
	./tyckets

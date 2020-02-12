#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 

	long lhours = seconds % 60;
	long lminutes = (seconds / 60) % 60;
	long lseconds = seconds % 3600;

	std::stringstream ssresult;
	ssresult << std::setfill('0') << std::setw(2) << lhours << ":";
	ssresult << std::setfill('0') << std::setw(2) << lminutes << ":";
	ssresult << std::setfill('0') << std::setw(2) << lseconds;

	return ssresult.str();
 }
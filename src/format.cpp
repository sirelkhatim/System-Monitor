#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS

string Format::ElapsedTime(long seconds) { 

	long lhours = seconds % 60;
	long lminutes = (seconds / 60) % 60;
	long lseconds = seconds / 3600;

	std::stringstream ssresult;
	//format hours, minutes, and seconds to HH:MM:SS
	ssresult << std::setfill('0') << std::setw(2) << lseconds << ":";
	ssresult << std::setfill('0') << std::setw(2) << lminutes << ":";
	ssresult << std::setfill('0') << std::setw(2) << lhours;


	return ssresult.str();
 }
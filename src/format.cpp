#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    int hrs, mins;
    string elapsed_time;

    hrs = seconds / 3600;
    seconds -= hrs * 3600;

    mins = seconds / 60;
    seconds -= mins * 60;

    elapsed_time = std::to_string(hrs) + ":" + std::to_string(mins) + ":" + std::to_string(seconds);

    return elapsed_time; 
    
    }

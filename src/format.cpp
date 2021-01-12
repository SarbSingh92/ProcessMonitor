#include <string>
#include <iomanip>
#include "format.h"
#include <sstream>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    long Uptime = seconds;
    int HH = (Uptime/60/60)%12;
    Uptime %= 3600; 
    int MM = Uptime / 60; 
    Uptime %= 60; 
    int SS = Uptime; 
    //std::string time = std::to_string(HH)+":"+std::to_string(MM)+":"+std::to_string(SS);
    std::stringstream time; 
    time <<std::setw(2)<<std::setfill('0')<<std::to_string(HH)<<":"<<std::setw(2)<<std::setfill('0')<<std::to_string(MM)<<":"<<std::setw(2)<<std::setfill('0')<<std::to_string(SS);
    //std::cout<<time<<"\n";
    return time.str(); 
}
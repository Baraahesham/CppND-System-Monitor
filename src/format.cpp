#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    string result;
    int hours=0;
    int sec=0;
    int min=0;
    
     //min=(seconds/60);
     sec=seconds%60;
     hours=seconds/3600;
     min=(seconds/60)-(hours*60);
    
    result =std::to_string(hours)+":"+std::to_string(min)+":"+std::to_string(sec);


    return result; }
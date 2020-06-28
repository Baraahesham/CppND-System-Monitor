#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include<string>
using std::string;
using std::vector;
using std::stof;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float usertime,nicetime,idealtime,systemtime,virtaltime,totaltime;
    vector <string> out=LinuxParser::CpuUtilization();
    usertime=stof(out[0])-stof(out[8]);
    nicetime=stof(out[1])-stof(out[9]);
    idealtime=stof(out[3])+stof(out[4]);
    systemtime=stof(out[2])+stof(out[5])+stof(out[6]);
    virtaltime=stof(out[8])+stof(out[9]);

    totaltime=usertime+nicetime+idealtime+systemtime+virtaltime;
    
    return (totaltime-idealtime)/totaltime; }
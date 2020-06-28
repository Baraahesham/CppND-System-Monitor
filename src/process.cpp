#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//Constructor 
 Process::Process(int pid) : pid_(pid){}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long totaltime=LinuxParser::ActiveJiffies(pid_);
  long seconds=(LinuxParser::UpTime())-(LinuxParser::UpTime(pid_));
  float cpususage = ((float)totaltime/sysconf(_SC_CLK_TCK))/(float)seconds;
    return cpususage;}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    long ram = stol(LinuxParser::Ram(pid_));
	long ram_a = stol(LinuxParser::Ram(a.pid_));

	if (ram > ram_a) {
       
    }
		
    
     return false; }
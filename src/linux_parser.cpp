#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
   string line,MemTotal,MemFree,total,temp,value;
   std::ifstream stream(kProcDirectory+kMeminfoFilename);
   if(stream.is_open()){
     while(std::getline(stream,line)){
       std::istringstream linestream(line);
       linestream >> temp >> value;
       if(temp=="MemTotal:"){
         MemTotal=value;
       }else if(temp=="MemFree:"){
         MemFree=value;
         break ;
       }
     }
     return(((std::stof(MemTotal)-std::stof(MemFree))/(std::stof(MemTotal))));
   }
  return 0.0; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line,temp;
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestreamer(line);
    linestreamer >> temp;
    if(line!=""){
    return std::stol(line);
    }
  }

  return 0;
   }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
   
  return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
   string line,value;
   long result=0;
  int count=0;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  std::getline(stream,line);
  std::istringstream linestream(line);

  if(stream.is_open()){

   while(linestream>>value){
      count++;
      if(count==14 && value!=""){
        result+=std::stol(value);
      }
      else if(count==15 && value!=""){
        result+=std::stol(value);
      }
      else if(count==16 && value!=""){
        result+=std::stol(value);
      }
      else if(count==17 && value!=""){
        result+=std::stol(value);
        break ;
      }
      }

  }

   return result; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
 
  return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> result;
  string line,value;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
   std::getline(stream, line);
   std::istringstream linestream(line);
   linestream >> value;
   for(int i=0;i<10;i++){
     linestream >> value;
     result.push_back(value); 
   }

  } 
  return result ; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string process,line,tot;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    while (std::getline(stream, line)){
     std::istringstream linestream(line);
     linestream >> process >>tot;
     if(process == "processes"){
       linestream >> process >>tot;
       return std::stoi(tot);
     }     
    }
  }
  return 0; 
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string process,line,tot;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    while (std::getline(stream, line)){
    std::istringstream linestream(line);
     linestream >> process >>tot;
     if(process == "procs_running"){
       linestream >> process >>tot;
       return std::stoi(tot);
     }     
    }
  }
  
  return 0; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  if(stream.is_open()){
    std::getline(stream, line); 
    }
  return line; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line,key,value;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
   if(stream.is_open())
  {
    while (std::getline(stream, line)){
     std::istringstream linestream(line);
     linestream >> key >>value;
     if(key == "VmSize:"){
       if(value!=""){
         return std::to_string(std::stol(value)/1000);
       }
       
     }     
    }
   
  }
  
   return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line,uid,value;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(stream.is_open())
  {
    while (std::getline(stream, line)){
     std::istringstream linestream(line);
     linestream >> uid >>value;
     if(uid == "Uid:"){
       return value;
     }     
    }
   
  }
  return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
string line,key,value,temp;
std::ifstream stream(kPasswordPath);
if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> temp >>value;
        if (value == LinuxParser::Uid(pid)) {
          return key;
        }
      
    }
  }
  return string();
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string value,line;
  int count=0;
  long result=0;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  std::getline(stream,line);
  //std::getline(stream,line);
  std::istringstream linestream(line);
  while(linestream >> value){
    count++;
    if(count==22) {
      break;
    }
  }
  if(value !=""){
   result=std::stol(value)/sysconf(_SC_CLK_TCK);
  }
  return  result;
  }
/*
int main (){
  //int x=LinuxParser::TotalProcesses();
  //int y=LinuxParser::RunningProcesses();
  //float f=LinuxParser::MemoryUtilization();
  long test=LinuxParser::UpTime(8);
  //std::cout<<test<<"\n";
  //vector<string >test;
  //test=LinuxParser :: CpuUtilization();

}*/

#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "format.h"

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
string line;
string key;
string value;


string memTotal;
string memFree;
string memAvailable;
string buffers;

std::ifstream filestream(kProcDirectory + kMeminfoFilename);
if(filestream.is_open()){

  while(std::getline(filestream, line)){
  std::istringstream linestream(line);
  while(linestream>>key>>value){
    if(key == "MemTotal:"){
      memTotal = value;
    }
    else if(key == "MemFree:"){
      memFree = value;
    }
    else if(key == "MemAvailable:"){
      memAvailable = value;
      
    }else if(key == "Buffers:"){
      buffers = value;
    }
  }

 }

}

return ((std::stof(memTotal) - std::stof(memFree))/std::stof(memTotal));
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
string uptime;
string idle;
string line;
std::ifstream filestream(kProcDirectory + kUptimeFilename);
if(filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream >> uptime>>idle;
 }
return std::stol(uptime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  string cpu;
  string sUser;
  string sNice;
  string sSystem;
  string sIdle;
  string sIOwait;
  string sIRQ;
  string sSoftIRQ;
  string sSteal;
  string sGuest;
  string sGuestNice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu>>sUser>>sNice>>sSystem>>sIdle>>
    sIOwait>>sIRQ>>sSoftIRQ>>sSteal>>sGuest>>sGuestNice;

  }
  return (std::stol(sUser) + std::stol(sNice) + 
  std::stol(sSystem) + std::stol(sIdle) + std::stol(sIOwait) + 
  std::stol(sIRQ) + std::stol(sSteal) + std::stol(sGuest) + std::stol(sGuestNice));

}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string shlp;
  string sUtime;
  string sStime;
  string sCUtime;
  string sCStime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i= 1; i < 14; i++){
      linestream>> shlp;

  }
    linestream >> sUtime >> sStime >> sCUtime >> sCStime;
  }

  return (std::stol(sUtime) + std::stol(sStime) + 
    std::stol(sCUtime) + std::stol(sCStime));

 }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string cpu;
  string sUser;
  string sNice;
  string sSystem;
  string sIdle;
  string sIOwait;
  string sIRQ;
  string sSoftIRQ;
  string sSteal;
  string sGuest;
  string sGuestNice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu>>sUser>>sNice>>sSystem>>sIdle>>
    sIOwait>>sIRQ>>sSoftIRQ>>sSteal>>sGuest>>sGuestNice;
  }
  return ( std::stol(sUser) + std::stol(sNice) + 
  std::stol(sSystem)  + std::stol(sIRQ) + std::stol(sSteal) + std::stol(sGuest) + std::stol(sGuestNice));
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line;
  string cpu;
  string sUser;
  string sNice;
  string sSystem;
  string sIdle;
  string sIOwait;
  string sIRQ;
  string sSoftIRQ;
  string sSteal;
  string sGuest;
  string sGuestNice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu>>sUser>>sNice>>sSystem>>sIdle>>
    sIOwait>>sIRQ>>sSoftIRQ>>sSteal>>sGuest>>sGuestNice;
  }
  std::cout<<std::stol(sIdle);
  return std::stol(sIdle) + std::stol(sIOwait);

 }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  long oldActiveJiffies = ActiveJiffies();
  long oldIdleJiffies = IdleJiffies();
  sleep(10);
  long newActiveJiffies = ActiveJiffies();
  long newIdleJiffies = IdleJiffies();
  string shlp = Format::ElapsedTime(
    ((newActiveJiffies - oldActiveJiffies) - (newIdleJiffies - oldActiveJiffies))/(newActiveJiffies - oldActiveJiffies));
  vector<string> vResult;
  vResult.push_back(shlp);
  return vResult;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
string line;
string key;
string value;
std::ifstream filestream(kProcDirectory + kStatFilename);
if(filestream.is_open()){
  
  while (std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
    if (key == "processes"){
      return std::stoi(value);
    }
  }

}
return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
string line;
string key;
string value;
std::ifstream filestream(kProcDirectory + kStatFilename);

if(filestream.is_open()){
  
  while (std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
    if (key == "procs_running"){
      return std::stoi(value);

    }

  }

}
return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()){
    std::getline(filestream, line);
    return line;
  }
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
string line;
string key;
string value;
std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
if(filestream.is_open()){
  while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
    if(key == "VmData:"){
      int tmp = (100 * std::stof(value)/1024 + 0.5);
      return to_string(tmp/100);
    }
  }
}
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
string line;
string key;
string value;
std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
if(filestream.is_open()){
  while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
    if(key == "Uid:"){
      return value;
    }
  }
}}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 

string line;
string search_token = "x:" + to_string(pid);
std::ifstream filestream(kPasswordPath);
if(filestream.is_open()){
  while(std::getline(filestream, line)){
    auto pos = line.find(search_token);
    if(pos != string::npos){
      return line.substr(0, pos -1);
    }

  }

}
return "root";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
string line;
string hlp;
std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
if(filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  for(int i = 0; i<14; i++){
    linestream >> hlp;
    
  }
  return stol(hlp);
}
return 0;
}
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() {
  return pid;
}

// TODO: Return this process's CPU utilization
/*
#define UTIME 0
#define STIME 1
#define CUTIME 2
#define CSTIME 3
#define STARTTIME 4
*/
float Process::CpuUtilization() { 
  string line;
  string key;
  
  float total_time, seconds;
  int count = 0;
  
  vector<int> process_util;  
    
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (count == 13 || count == 14 || count == 15 || count == 16 || count == 21) {
          process_util.push_back(stoi(key));
        }
        count++;
      }
  }
  
  total_time = process_util[UTIME] + process_util[STIME] + process_util[CUTIME] + process_util[CSTIME];

  seconds = LinuxParser::UpTime() - (process_util[STARTTIME] / sysconf(_SC_CLK_TCK) );

  cpu_usage = 100 * ((total_time / sysconf(_SC_CLK_TCK) ) / seconds);
  
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
	return LinuxParser::Command(pid);
}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return (cpu_usage > a.cpu_usage); 
}

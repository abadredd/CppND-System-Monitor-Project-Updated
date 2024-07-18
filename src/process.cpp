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
// float Process::CpuUtilization() { 
//   string line;
//   string key;
  
//   float total_time, seconds;
//   int count = 1;
  
//   vector<int> process_util{vector<int>(10,0)};  
    
//   std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename);
//   if (filestream.is_open()) {
//     while (std::getline(filestream, line)) {
//       std::istringstream linestream(line);
//       while (linestream >> key) {
//         if (count == 14 || count == 15 || count == 16 || count == 17 || count == 22) {
//           this->process_util.push_back(stoi(key));
//         }
//         count++;
//       }
//     }
//   }
  
//   total_time = this->process_util[UTIME] + this->process_util[STIME] + this->process_util[CUTIME] + this->process_util[CSTIME];

//   seconds = LinuxParser::UpTime() - (this->process_util[STARTTIME] / sysconf(_SC_CLK_TCK) );

//   cpu_usage = 100 * ((total_time / sysconf(_SC_CLK_TCK) ) / seconds);
  
//   return cpu_usage;
// }

float Process::CpuUtilization() { 
  float uptime = (float)LinuxParser::UpTime();
  float hertz_value = (float)sysconf(_SC_CLK_TCK);
  float totalTime = 0.0, seconds = 0.0, cpu_usage = 0.0;
  string line, key, value;
  vector<string> processorStat;
  std::ifstream fileStream(LinuxParser::kProcDirectory + std::to_string(pid) + "/stat");
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream linestream(line);
    while(linestream >> value){
      //std::cout << "value: " << value << std::endl;
      processorStat.emplace_back(value);
    }
  }
  
  if (processorStat.size() > 21) {
    totalTime = std::stof(processorStat[13]) + stof(processorStat[14]) + std::stof(processorStat[15]) + std::stof(processorStat[16]);
    
    seconds = uptime - (std::stof(processorStat[21]) / hertz_value);
    if (seconds > 0) {
      cpu_usage = ( ( totalTime / hertz_value ) / seconds );
    }
  }
  
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

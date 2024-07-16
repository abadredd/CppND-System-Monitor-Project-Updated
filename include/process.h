#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

using std::vector;

#define UTIME 0
#define STIME 1
#define CUTIME 2
#define CSTIME 3
#define STARTTIME 4

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int& pid) : pid(pid) {};

  // TODO: Declare any necessary private members
 private:
  int pid;
  vector<int> process_util{vector<int>(10,0)};
};

#endif

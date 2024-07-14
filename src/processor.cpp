#include "processor.h"
#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

const std::string kProcDirectory{"/proc/"};
const std::string kStatFilename{"/stat"};

// TODO: Return the aggregate CPU utilization
/*
     user    nice   system  idle      iowait irq   softirq  steal  guest  guest_nice
cpu  74608   2520   24433   1117073   6176   4054  0        0      0      0

*/
float Processor::Utilization() {
  vector<int> cpu_util = LinuxParser::CpuUtilization();
  float PrevIdle, Idle, PrevNonIdle, NonIdle, PrevTotal, Total, totald, idled, CPU_Percentage;
  
  PrevIdle = this->prev_cpu_util[IDLE] + this->prev_cpu_util[IOWAIT];
  Idle = cpu_util[IDLE] + cpu_util[IOWAIT];

  PrevNonIdle = this->prev_cpu_util[USER] + this->prev_cpu_util[NICE] + this->prev_cpu_util[SYSTEM] + this->prev_cpu_util[IRQ] + this->prev_cpu_util[SOFTIRQ] + this->prev_cpu_util[STEAL];
  NonIdle = cpu_util[USER] + cpu_util[NICE] + cpu_util[SYSTEM] + cpu_util[IRQ] + prev_cpu_util[SOFTIRQ] + prev_cpu_util[STEAL];
  
  PrevTotal = PrevIdle + PrevNonIdle;
  Total = Idle + NonIdle;

  totald = Total - PrevTotal;
  idled = Idle - PrevIdle;

  CPU_Percentage = (totald - idled)/totald;
  
  this->prev_cpu_util = cpu_util;
  
  return CPU_Percentage;
}

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
using std::vector;

#define USER 0
#define NICE 1
#define SYSTEM 2
#define IDLE 3
#define IOWAIT 4
#define IRQ 5
#define SOFTIRQ 6
#define STEAL 7
#define GUEST 8
#define GUEST_NICE 9

/*
     user    nice   system  idle      iowait irq   softirq  steal  guest  guest_nice
cpu  74608   2520   24433   1117073   6176   4054  0        0      0      0

*/
class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
  
 private:
    std::vector<int> prev_cpu_util{std::vector<int>(10, 0)};
};

#endif

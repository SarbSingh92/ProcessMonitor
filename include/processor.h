#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
 float prev_total = 0; //previous total CPU time 
 float prev_idle = 0; //previous total CPU idle time 
};

#endif
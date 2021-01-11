#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
using std::stof;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(); 
  Process(int p); 
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp


  // DONE: Declare any necessary private members
 private:
 
std::string user = "";
  int process_ID; //stores the PID for passing the methods 
  int ram_; //stores the RAM usuge for sorting 
  float proc_usuage; //stores the Processor Usage for sorting


 
  

};

#endif
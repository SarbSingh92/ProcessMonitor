#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::to_string; 

// DONE: Return the system's CPU
Processor& System::Cpu() 
{ 
    return cpu_; 
}

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();
    int size = pids.size(); 
 
    for (int i = 0; i<size;i++)
    {
        Process p(pids[i]); //create process and assign PID
        p.CpuUtilization(); //set the Processir Usage variable, so that vector can be sorted later
        processes_.push_back(p); //push process into vector 
        //debugging code
        //std::ofstream debug("/home/help.txt",std::ios_base::app); 
        //debug<<"PID: "<<to_string(pids[i])<<"\n";
        //debug.close();
    }

    //sort from largest to smallest cpu utilization 
    
    for(int i=0; i<size-1;i++)
    {
        bool swapped = false; 
        for (int j=0;j<size-1;j++)
        {
            if(processes_[j]<processes_[j+1])
            {
                swapped = true; 
                Process temp = processes_[j];
                processes_[j] = processes_[j+1];
                processes_[j+1] = temp; 
            }
        }
        if(swapped == false){break;}
    }
   
    return processes_; 
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() 
{ 
    if(kernel_ver==""){kernel_ver = LinuxParser::Kernel();} //read kernal version and store it in local memory
    return kernel_ver; 
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization() 
{ 
    //std::cout<<"Frm System, the Mem Util is "<<LinuxParser::MemoryUtilization()<<"\n";
    return LinuxParser::MemoryUtilization();
}

// DONE: Return the operating system name
std::string System::OperatingSystem() 
{ 
    if(OS_ver==""){OS_ver = LinuxParser::OperatingSystem();} //read OS version and store it in local memory
    return OS_ver; 
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() 
{ 
    return LinuxParser::UpTime(); 
}
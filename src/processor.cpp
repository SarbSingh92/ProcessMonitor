#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
using std::vector; 
using std::stof;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    /* Attempt at dynamic processor utilization - still in progress
    
   float idle_total = LinuxParser::IdleJiffies();
   float cpu_util_total = LinuxParser::Jiffies(); 
   
 
    float total_diff = cpu_util_total - prev_total; 
    float idle_diff = idle_total - prev_idle;
    //set current totals to previous for next calculation
    prev_total = cpu_util_total; 
    prev_idle = idle_total; 
    float cpu_util_percent = (total_diff - idle_diff)/total_diff; 
    */
   //average CPU utilization
    long uptime = LinuxParser::UpTime();
    float cpu_util_percent = (LinuxParser::ActiveJiffies()/sysconf(_SC_CLK_TCK))/uptime;
    //debugging 
    //std::ofstream debug("/home/help.txt",std::ios_base::app);
    //debug<<"CPU: "<<cpu_util_percent<<" Active Jiffs = "<<LinuxParser::ActiveJiffies()<<" Clock Freq: "<<sysconf(_SC_CLK_TCK)<<" UpTime: "<<uptime<<"\n";
    //debug.close();
    
    return cpu_util_percent; 
}
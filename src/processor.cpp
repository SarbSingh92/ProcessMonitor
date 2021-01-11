#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <iostream>
using std::vector; 
using std::stof;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    std::vector<std::string>cpu_param = LinuxParser::CpuUtilization(); //create vector of strings to store CPU Time values 
    //total cpu time is calculated utilization definition discussed at 
    //https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    float usertime = stof(cpu_param[LinuxParser::CPUStates::kUser_]) -stof(cpu_param[LinuxParser::CPUStates::kGuest_]); 
    float nicetime = stof(cpu_param[LinuxParser::CPUStates::kNice_]) - stof(cpu_param[LinuxParser::CPUStates::kGuestNice_]);

    float idle_total = stof(cpu_param[LinuxParser::CPUStates::kIdle_])+stof(cpu_param[LinuxParser::CPUStates::kIOwait_]);
    float system_total = stof(cpu_param[LinuxParser::CPUStates::kSystem_])+stof(cpu_param[LinuxParser::CPUStates::kIRQ_])+stof(cpu_param[LinuxParser::CPUStates::kSoftIRQ_]);
    float guest_total = stof(cpu_param[LinuxParser::CPUStates::kGuest_])+stof(cpu_param[LinuxParser::CPUStates::kGuestNice_]);
    float cpu_util_total = usertime+nicetime+idle_total+system_total+guest_total+stof(cpu_param[LinuxParser::CPUStates::kSteal_]);
 
    float total_diff = cpu_util_total - prev_total; 
    float idle_diff = idle_total - prev_idle;
    //set current totals to previous for next calculation
    prev_total = cpu_util_total; 
    prev_idle = idle_total; 
    float cpu_util_percent = (total_diff - idle_diff)/total_diff; 

    return cpu_util_percent; 
}
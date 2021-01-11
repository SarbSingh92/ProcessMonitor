#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>


#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;
using std::stoi;

//Constructor
Process::Process(){}
Process::Process(int p){process_ID = p;}
// DONE: Return this process's ID
int Process::Pid() { return process_ID; }

//DONE: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    //return (LinuxParser::ActiveJiffies(process_ID)/LinuxParser::UpTime(process_ID))*100;
    float total_proc_time = LinuxParser::UpTime(process_ID); 
    float process_time = LinuxParser::ActiveJiffies(process_ID);
    if(total_proc_time>0) //total time the process has been running must be greater than 0
    {
        proc_usuage = (process_time/total_proc_time)*100; //set private variable
        return (process_time/total_proc_time);
    }
    return 0;
}

// DONE: Return the command that generated this process
string Process::Command() 
{ 
    return LinuxParser::Command(process_ID); 
}

// DONE: Return this process's memory utilization
string Process::Ram() 
{
    string r = LinuxParser::Ram(process_ID);
    ram_ = std::stoi(r)/1000; //divide by 1000 to get MB
    return to_string(ram_); 
}

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(process_ID); }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(process_ID); }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{
    if(proc_usuage<a.proc_usuage)
    {
        return true;
    }
    return false;
}
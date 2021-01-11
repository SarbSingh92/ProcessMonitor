#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
 

#include "linux_parser.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os,version,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>version>> kernel;
  }
  //std::cout<<kernel<<"/n";
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  string value, line, variable; 
  float MemUtil, MemFree, MemTotal, MemAvailable; 
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line); 
      linestream>>variable>>value;
      if(variable == "MemTotal:"){MemTotal = stof(value);}
      if(variable== "MemFree:"){MemFree = stof(value);}
      if(variable== "MemAvailable:"){MemAvailable = stof(value);}
    } 
  }

  MemUtil =(MemTotal-MemAvailable)/MemTotal;
  
  return MemUtil; 
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  string value, line; 
  std::ifstream file(kProcDirectory+kUptimeFilename);
  if(file.is_open())
  {
    std::getline(file, line);
    std::istringstream linestream(line);
    linestream>>value; 
  }
  return stof(value); 
}

// NOT USED: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{ 
   return 0; 
}

// DONE: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) 
{
  string line, parameter, data;
  long utime, stime, cutime, cstime;   
  std::ifstream file(kProcDirectory+to_string(pid)+kStatFilename); 
  if(file.is_open())
  {
    getline(file, line); 
    
    std::istringstream linestream(line);
     
    for (int i =0;i<13;i++) //skip the first 13 data points 
    {
      linestream>>data; 
    }
    linestream>>utime>>stime>>cutime>>cstime; 
  }
  
  long seconds = (utime+stime)/sysconf(_SC_CLK_TCK); 

  return seconds;   
}

// NOT USED: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{ 
  return 0; 
}

// NOT USED: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{ 
  return 0; 
}

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
   string line, var; 
   vector<string> cpu_temp={"0","0","0","0","0","0","0","0","0","0"};
   std::ifstream filestream(kProcDirectory+kStatFilename);
   if(filestream.is_open())
   {
      std::getline(filestream,line);
      std::istringstream linestream(line); 
      linestream>>var>>cpu_temp[kUser_]>>cpu_temp[kNice_]>>cpu_temp[kSystem_]>>cpu_temp[kIdle_]>>cpu_temp[kIOwait_]>>cpu_temp[kIRQ_]>>cpu_temp[kSoftIRQ_]>>cpu_temp[kSteal_]>>cpu_temp[kNice_]>>cpu_temp[kGuestNice_];
   }
  return cpu_temp; 
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  string line,parameter, value; 
  int total_proc =0;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open())
  {
    while(getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream>>parameter>>value; 
      if(parameter == "processes"){total_proc = stof(value);}
    }

  }
  return total_proc; 
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string line,parameter, value; 
  int numproc =0;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open())
  {
    while(getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream>>parameter>>value; 
      if(parameter == "procs_running"){numproc = stof(value);}
    }

  }
  return numproc; 
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{ 
  string line; 
  std::ifstream file(kProcDirectory+to_string(pid)+kCmdlineFilename); 
  if(file.is_open())
  {
    getline(file, line); //command is stored as one line
  }
  return line; 
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
  string line, parameter, data, memory;  
  std::ifstream file(kProcDirectory+to_string(pid)+kStatusFilename); 
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::istringstream linestream(line);
      linestream>>parameter>>data; 
      if(parameter == "VmSize:")
      {
        memory = data; 
      }

    }
  }
  return memory; 
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) 
{ 
  string line, parameter, data;  
  std::ifstream file(kProcDirectory+to_string(pid)+kStatusFilename); 
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::istringstream linestream(line);
      linestream>>parameter>>data;
 
      if(parameter == "Uid:")
      {
        return data; 
      }

    }
  }
  return "NID"; 
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) 
{ 
  string userID = LinuxParser::Uid(pid); 
  string line, parameter, username, val;  
  std::ifstream file(kPasswordPath); 
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::replace(line.begin(), line.end(),':', ' ');
      std::istringstream linestream(line);
      linestream>>username>>parameter>>val; 
      if(val == userID)
      {
        return username;  
      }

    }
  }
  return "No_User";  
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) 
{ 
  string line, parameter, data;  
  std::ifstream file(kProcDirectory+to_string(pid)+kStatFilename); 
  if(file.is_open())
  {
    getline(file, line); 
    
    std::istringstream linestream(line);
    //uptime is the 22nd value in the line; 
    for (int i =0;i<22;i++)
    {
      linestream>>data; 
    }
  }
 
  long seconds = LinuxParser::UpTime() - stof(data)/sysconf(_SC_CLK_TCK); //subtract the time the process started from the total time

  return seconds; 
}
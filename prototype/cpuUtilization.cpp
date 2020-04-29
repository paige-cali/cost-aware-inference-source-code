#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include<numeric>
using namespace std;

//This function reads from proc_stat, and saves all overall CPU values (first line of proc/stat) to a vector
vector<int> get_proc_stat() {

  string line;
  float util;
  vector<int> first; 
  ifstream proc_stat("/proc/stat");
  proc_stat.ignore(6, ' '); //skip 5 spaces for 'cpu  '

  //open proc stat file 
  if (proc_stat.is_open())
  {

    //get first line of proc stat only
    string firstLine; 
    getline(proc_stat, firstLine);
    cout << "Proc/Stat Values: " << firstLine <<endl;

    //convert proc stat string to array of ints (separated by spaces)
    string temp = "";
    for (char const c: firstLine) {

      if (c != ' ') {
        temp = temp + c;
      }

      else {
        //if it is a space - number is complete add to int array

          //convert string to integer
          int num =0;
          std::istringstream (temp) >> num;
          
          //add integer to vector
          first.push_back(num);

          // cout << "number: " << num<<endl;

          //empty temporary string 
          temp = ""; 

      }
    }

    proc_stat.close();
  }

  return first; 

}


//This function takes a vector of cpu times and applies the cpu calculation (1-idle time/overall time)
//Returns current CPU utilization % as a float
float calculate_cpu_load(vector<int> first) {
 

    int totalTime = accumulate(first.begin(),first.end(),0);
    cout<<"Total Time: "<< totalTime <<endl;


    //get forth value of vector - idle time = 4th column of proc stat 
    int idle = first[4];
    cout << "Idle: " << idle << endl;
    

    float util = 1 - float(idle)/ float(totalTime); 

    return util;

}



//This function gets the cpu utilization in a never ending loop and sleeps for the given pause time (in seconds)
float get_cumulative_cpu_load(int pause_interval) {

  
  float load;
  while (true) {

    
    vector<int> nums = get_proc_stat();
    load = calculate_cpu_load(nums);

    cout << "CPU Utilization: "<<load <<endl;
    sleep(pause_interval);

  }

   return load; //returns last cpu load value

}



//Main method run for example (20 second pause)
int main() {

  float cpu = get_cumulative_cpu_load(20);
  return 0;
}

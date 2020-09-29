/*****************************************************************************
PROJECT   : 1.
CLASS     : CSCI 480
INSTRUCTOR: JIE ZHOU
PROGRAMMER: IBRAHIM KHAN
DUE DATE: 09-15-2020
LOGIC:	THIS PROGRAM WILL READ PROC FILES AND EXTRACT CERTAIN INFORMATION
      	ABOUT THE PROCESSORS,USER MODE, IDLE MODE, NICE MODE, RUNNING AND
	IDLE TIMES,SIZES OF DIFFERENT ADDRESSES(PHYSICAL AND VIRTUAL),
	SWAP DEVICE SIZE.

LIMITATIONS: 1)PROGRAM MUST USE STRING CLASS MEMBER FUNCTIONS TO EXTRACT
	       INFORMATION FROM THE FILES.
	     2)PROGRAM MUST OUTPUT INFORMATION
	       IN A HUMAN READABLE MANNER.
NOTES: STAT TIMES ARE IN 1/100th OF A SECONDS CONVERT THEM INTO SECONDS.
       SIZE OF SWAP DEVICE IS IN KILOBYTES CONVERT IT INTO MEGABYTES
******************************************************************************
*/

/*PREPROCESSOR DIRECTIVES*/
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<limits>
#include<vector>
#include<iomanip>

/*USING STANDARD LIBRARY FUNCTIONS*/
using namespace std;

/*PROTOTYPES FOR THE METHODS USED*/
void file(string filename);
string find_string_btwn_delims(string& s, string start, string stop);

int main()
{
/*CHECKING IF FILES EXIST*/
file("/proc/cpuinfo");
file("/proc/uptime");
file("/proc/swaps");
file("/proc/stat");

/*VARIABLE DECLARATIONS*/
string vendorfind;
string ostype;
string host_name;
string os_release;
string os_version;
string line_from_file;
string temp = line_from_file;
int phy_chips = 0;
int cores     = 0;
string uptime_counter;
double uptime_decimal = 0.00;
double idle_decimal   = 0.00;
string vendor;
string model;
string physical_address_size;
string virtual_address_size;
string stat_array[13];
string stat_line;
string cpu0_line;
string cpu0_data;
int vector_array_counter = 0;
string user;
string nice;
string system;
string idle;
double user_seconds;
double idle_seconds;
double system_seconds;
double nice_seconds;
int user_nice = 0;
string swap_line;
string swap_word = "";
string swap_arr[5];
vector<string>filename;
vector<string>type;
vector<string>size;
vector<string>used;
vector<string>priority;
string swap_file;
string swap_type;
string swap_size;
string swap_used;
string swap_priority;
double MB_size = 0;

/*READING IN ALL THE FILES*/
ifstream cpuinfo("/proc/cpuinfo");
ifstream os("/proc/sys/kernel/ostype");
ifstream host("/proc/sys/kernel/hostname");
ifstream osrelease("/proc/sys/kernel/osrelease");
ifstream version("/proc/sys/kernel/version");
ifstream uptime("/proc/uptime");
ifstream stat("/proc/stat");
ifstream swap_file_info("/proc/swaps");

/*
GETLINE DECLARATIONS.
NOTE: WE DONT NEED TO GO THROUGH THE LINES IN THE FILE
      SINCE THE FILES ONLY CONTAIN THE RELATIVE INFORMATION.
*/
getline(os, ostype);
getline(host, host_name);
getline(osrelease, os_release);
getline(version, os_version);

/*READING IN FROM CPUINFO FILE*/
while(getline(cpuinfo, line_from_file))
   {
   if(line_from_file.find("physical id") != string::npos)
      {
      if(temp != line_from_file)  //using if statement to check if the physical id has changed.
         {                          //which only changed when there is another physical chip.
         temp = line_from_file;
         phy_chips += 1;
        }
      }
   else if (line_from_file.find("core id") != string::npos)
      {
      cores += 1;		//whenever core id is found it represents another core.
      }
   else if (line_from_file.find("vendor_id") != string::npos)
      {
      vendor = line_from_file.substr(line_from_file.find(":") + 1); //using substring to get only the vendor name
      }
   else if (line_from_file.find("model name") != string::npos)
      {
      model = line_from_file.substr(line_from_file.find(":") + 1); //using substring to get only the model name
      }
   else if (line_from_file.find("address sizes") != string::npos)
      {
      physical_address_size = find_string_btwn_delims(line_from_file, ":", ","); //using delimiters to get physical and virtual address separately
      virtual_address_size = line_from_file.substr(line_from_file.find(",") + 1); //using find_string_btwn_delims methods.
      }
   }

/*READING IN FROM UPTIME FILE*/
getline(uptime, uptime_counter, ' ');
int int_uptime_counter = stod(uptime_counter); //using stod to use string uptime as double uptime fpr calculations
uptime_decimal = stod(uptime_counter) - int_uptime_counter; //separating the decimal values for accuracy in seconds
int uptime_days = (int_uptime_counter / 86400.00); //converting seconds to days hours minutes and seconds.
int_uptime_counter = (int_uptime_counter % 86400);
int uptime_hours = (int_uptime_counter / 3600);
int_uptime_counter %= 3600;
int uptime_minutes = (int_uptime_counter / 60);
int_uptime_counter %= 60;
double uptime_seconds = int_uptime_counter;

/*READING DATA FROM STAT FILE*/
while (getline(stat, stat_line))
   {
   if(stat_line.find("cpu0") != string::npos)
      {
      cpu0_line = stat_line.substr(stat_line.find("cpu0") + 4); //cpu0_line will hold the line read from stat
      cpu0_data = find_string_btwn_delims(cpu0_line, "u0", "\n"); //cpu0_data will hold data between the two delimiters.
      string word = ""; 
      for(auto x : cpu0_data) //for loop to read characters one by one and store them in stat_array array for information
         {                    //extraction. 'x' here is just a temp variable for storing chars.
         if(x == ' ')
            {
            stat_array[vector_array_counter] = word;
            vector_array_counter++;
            word = "";
            }
         else
            {
            word = word + x;
            }
         }
/*extracting user mode nice mode system mode idle mode from the array*/
      user = stat_array[0];
      nice = stat_array[1];
      idle = stat_array[3];
      system = stat_array[2];
      user_seconds = stod(user) / 100; //since the time in file is by 1/100th of a seconds for accuracy we must
      nice_seconds = stod(nice) / 100; //we must convert that into seconds by dividing by 100 for this project.
      system_seconds = stod(system) / 100;
      idle_seconds = stod(idle) / 100;
      user_nice = user_seconds + nice_seconds; //user_nice includes times from both user and nice modes in seconds
      }
}

/*
GETTING INFORMATION FROM SWAP FILE
NOTE: USING VECTORS TO EXTRACT INFORMATION FROM THE SWAP FILE
*/
getline(swap_file_info, swap_line); //reading this line outside the while loop to ignore the title line.
while(!swap_file_info.eof())        //and get the title line out of the way.
   {
   getline(swap_file_info, swap_file, ' ');
   filename.push_back(swap_file);
   getline(swap_file_info, swap_type, '\t');
   type.push_back(swap_type);
   getline(swap_file_info, swap_size, '\t');
   size.push_back(swap_size);
   getline(swap_file_info, swap_used, '\t');
   used.push_back(swap_used);
   getline(swap_file_info, swap_priority, '\t');
   priority.push_back(swap_priority);
   }
MB_size = stod(size[0])/1000; //size is in kilobytes so we divide that by 1000 to convert it into megabytes.

/*CALCULATING TIME SPENT IDLE IN DAYS HOURS MINUTES AND SECONDS*/
int int_idle_counter = idle_seconds;
idle_decimal = idle_seconds - int_idle_counter;
int_idle_counter = int_idle_counter / 100;
int idle_days = (int_idle_counter / 86400.00);
int_idle_counter = (int_idle_counter % 86400);
int idle_hours = (int_idle_counter / 3600);
int_idle_counter %= 3600;
int idle_minutes = (int_idle_counter / 60);
int_idle_counter %= 60;
double idle_secs = int_idle_counter;

/*CLOSING ALL THE FILES*/
cpuinfo.close();
stat.close();
swap_file_info.close();
os.close();
host.close();
version.close();
osrelease.close();
uptime.close();


/*OUTPUT*/
cout << fixed << setprecision(1); //setting precision for the double values/
cout << "A:QUESTIONS ABOUT TURING's OPERATING SYSTEM " << endl << "-------------------------------------------" << endl;
cout << "Q:WHAT IS THE OS TYPE OF TURING?" << endl;
cout << "1.OS type of turing is " << ostype << endl;
cout << "Q:WHAT IS THE HOSTNAME OF TURING?" << endl;
cout << "2.Hostname is " << host_name << endl;
cout << "Q:WHAT IS THE OS RELEASE OF TURING?" << endl;
cout << "3.Operating system release of turing is " << os_release << endl;
cout << "Q:WHAT IS THE OS VERSION OF TURING?" << endl;
cout << "4.Operating system version of turing is " << os_version << endl << endl;
cout << "B:QUESTIONS ABOUT TURING's PROCESSORS" << endl <<"-------------------------------------------" << endl;
cout << "Q:HOW MANY PHYSICAL CHIPS DOES TURING HAVE?" << endl;
cout << "1.There are " << phy_chips << " physical chips in the system" << endl;
cout << "Q:HOW MANY CPU CORES DOES TURING HAVE?" << endl;
cout << "2.There are " << cores << " cores in the system" << endl;
cout << "Q:HOW LONG HAS IT BEEN UP IN SECONDS?" << endl;
cout << "3.The system has been up for " << uptime_counter  << " seconds." << endl;
cout << "Q:EXPRESS THE TIME IN DAYS HOURS MINUTES AND SECONDS." << endl;
cout << "4.In Days Hours Minutes and seconds it would be " << uptime_days << " Days, " << uptime_hours << " Hours, " << uptime_minutes << " Minutes, " << uptime_seconds + uptime_decimal << " Seconds " << endl << endl;
cout << "C:ABOUT PROCESSOR 0 OF TURING " << endl << "-------------------------------------------" << endl;
cout << "Q:WHO IS THE VENDOR OF PROCESSOR 0?" << endl;
cout << "1.For processor 0 the vendor is " << vendor << endl;
cout << "Q:WHAT IS THE MODEL OF PROCESSOR 0" << endl;
cout << "2.For processor 0 the model is " << model << endl;
cout << "Q:WHAT IS THE PHYSICAL ADDRESS SIZE OF PROCESSOR 0?" << endl;
cout << "3.Processor 0 has  " << physical_address_size << " address size "  << endl;
cout << "Q:WHAT IS THE VIRTUAL ADDRESS SIZE OF PROCESSOR 0?" << endl;
cout << "4.Processor 0 has " << virtual_address_size << " address size." << endl << endl;
cout << "D.QUESTIONS ABOUT STATISTICS OF CPU0 IN SYSTEM " << endl << "-------------------------------------------" << endl;
cout << "Q:HOW LONG HAS IT SPENT TIME IN USER MODE IN SECONDS(INCLUDING USER AND NICE MODE)?" << endl;
cout << "1.The system has spent " << user_nice << " seconds in user/nice mode." << endl;
cout << "Q:HOW LONG HAS IT SPENT TIME IN SYSTEM MODE IN SECONDS?" << endl;
cout << "2.The system has spent " << system_seconds  << " seconds in system mode." << endl;
cout << "Q:HOW LONG HAS IT SPENT TIME IN IDLE MODE IN SECONDS?" << endl;
cout << "3.The system has spent " << idle_seconds << " seconds in idle mode." << endl;
cout << "Q:EXPRESS THE TIME SPENT IN IDLE MODE IN DAYS HOURS MINUTES AND SECONDS?" << endl;
cout << "4.Idle mode time in Days, Hours, Minutes, Seconds would be " << idle_days << " Days, " << idle_hours << " Hours, " << idle_minutes << " Minutes, " << idle_secs + idle_decimal << " Seconds." << endl << endl; 
cout << "E:WHAT IS THE SIZE OF THE SWAPS DEVICE IN MBs?" << endl;
cout << "1.The size of swaps device in Megabytes would be " << MB_size <<" MBs" << endl;

return 0;
}

/*METHOD DECLARATIONS*/

/*
FUNCTION: file

FUNCTION DATA TYPE: void

USE: Checks if the file passed in as argument opens.

Arguments: 1.A string for the name of the file.

returns: nothing, but exits the program if file is not valid.
*/
void file(string filename)
   {
   ifstream ff;
   ff.open(filename); //opening file
   if(!ff.is_open()) //if file does not open or exist throw error and exit out.
      {
      cout << "could not open file" << endl;
      exit(-1);
      }
   }
/*
FUNCTION: find_string_btwn_delims.

FUNCTION DATA TYPE: string

USE: The function returns string between the two delimiters passed in as arguments.

ARGUMENTS: 1.A string to find get the substring from.
	   2.A string delimiter for start, this is where the returned string will start.
	   3.A string delimiter to stop, This is where the returned string ends.
RETURNS: This function returns a string.
*/
string find_string_btwn_delims(string& string_line, string start, string stop)
   {
   unsigned first_pos = string_line.find(start);
   unsigned end_of_first_delim = first_pos + start.length();
   unsigned last_delim_pos = string_line.find(stop);
   return string_line.substr(end_of_first_delim, last_delim_pos - end_of_first_delim);
   }

/* 
File name: kodalis_2122_HW01.cpp 
Created by: Surya Tej Kodali 
Created on: 1/10/2020
Synopsis: This program prompts the user to input a time between 
00:01 and 09:59; however, the digits 1,4, and 7 are not 
allowed. If the user input is not in between the desired
time, the user will be prompted to enter a new valid time.
If the user input contains these digits, a new time
with the next highest valid time will be displayed.
*/

#include <iostream>
using namespace std;

// check whether a given time is between 00:01 and 09:59
bool isValid(int hours, int minutes);
// check whether a given time contains digits 1, 4, or 7
void containsDigits(int hours, int minutes);
// print a given time in the format of hh:mm
void printTime(int hours, int minutes);

int main()
{
    int hours, minutes;
    char c; // to skip the ':'

    cout<<"Enter the desired time: ";
    cin >> hours >> c >> minutes;
    // check if the format is valid
    if(!isValid(hours, minutes)){
      cout << "The desired time is invalid.";
      return 0;
    }
    // check for 1,4,7 digits and increase to valid time
    containsDigits(hours, minutes);
      
    return 0;
}

bool isValid(int hours, int minutes){
  if(hours >= 0 && hours <= 9 && minutes >= 1 && minutes <= 59){
    return true;
  } else return false;
}

void containsDigits(int hours, int minutes){
  // true if time contains 1,4,7
  bool invalid = true;
  // temp variables to hold tens and singles digits of minutes
  int t,s;
  // increase hours if time has 1,4,7
  if(hours == 1 || hours == 4 || hours == 7){
    hours++;
  } 
  // increments minutes by +1 if time has 1,4,7
  while(invalid){
    t = minutes/10;
    s = minutes%10;
    if(!(t == 1 || t == 4 || t == 7 || s == 1 || s == 4 || s == 7)){
	invalid = false;
    }
    else minutes++;
  }
  // display new time 
  printTime(hours, minutes);
}

void printTime(int hours, int minutes){
  cout << "0" << hours << ":";
  // if single digit time adds extra '0'
  if(minutes/10 == 0) cout << "0";
  cout << minutes << endl;
}
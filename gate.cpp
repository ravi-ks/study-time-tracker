//author: Ravi
//read the Readme file first
//version 3
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
#include <stdio.h>
#include <termios.h>
#include <sys/select.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <string> 
#include <ctype.h>
using namespace std;

int hrs = 0;
int mins = 0;
int sec = 0;
string comment;
void err_invalid_syntax(){
	cout << "Syntax:\n\t./gate" << endl;
	exit(0);

}

int _kbhit(){
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int _getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDERR_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void showClk() {
   system("clear");
   cout << setfill(' ') << setw(55) << " GATE'2021 TIMER \n";
   cout << setfill(' ') << setw(66) << " --------------------------------------\n";
   cout << setfill(' ') << setw(29);
   cout << "| " << setfill('0') << setw(2) << hrs << " Hours | ";
   cout << setfill('0') << setw(2) << mins << " Minutes | ";
   cout << setfill('0') << setw(2) << sec << " Seconds |" << endl;
   cout << setfill(' ') << setw(66) << " --------------------------------------\n\n";
   if(hrs > 0)
        cout << "Woah," << hrs << " hours streak. " << comment << endl;
   cout << "Enter 'x' to stop session" <<  endl;
}

void timer(){
	int flag = 0;
	while(flag == 0){
	        showClk();
      		sleep(1);
      		sec++;
      		if(sec == 60){
        		mins++;
        		if(mins == 60){
        			hrs++;
           			mins = 0;
        		}
         		sec = 0;
      		}
      		//cout << hrs << ":" << mins << ":" << sec <<endl;
      		if(_kbhit()){
			char ch = _getch();
			if(ch == 'x' | ch == 'X')
			flag = 1;
		}
		switch(hrs){
		        case 1: comment = "Great work!";
		                break;
		        case 2: comment = "Awesome!";
		                break;
		        case 3: comment = "You Rock!";
		                break;
		        case 4: comment = "On Fire!";
		                break;
		        default : comment = "Towards IISc!";
		                  break;
		}
   	}
   	cout << endl;
}

int main(int argc, char** argv){
	if(argc != 1)
		err_invalid_syntax();
        
	bool is_newEntry = true;
	
	ofstream fout, fout2;
	ifstream fin;

	
	int time_hrs, time_mins, time_sec, day = 0, temp_day;
	
	time_t now = time(0);
   	tm *ltm = localtime(&now);
	
	//if log file is empty, by default we'll have a new entry
	char buff_temp[100];
	fin.open("study_logs.txt", ios::in);
	if(fin.getline(buff_temp, 100).fail() || (!isalpha(buff_temp[0]))) {
	           is_newEntry = true;
	}
	fin.close();
	        
	int tug1, tugset;
	string temp_char01, temp_char02, temp_char03;
	fin.open("study_logs.txt", ios::in);
	while(1){
		char buffer[100];
		char trash[100];
		if(fin.getline(buffer, 100).fail())
			break;
		sscanf(buffer, "%s %d", &trash, &day);
		
		fin.getline(buffer, 100); //for date
		//record date of the last entry
                tug1 = 0, tugset = 0;
                temp_char01 = ""; temp_char02 = ""; temp_char03 = "";
	        for(int i = 0; i < strlen(buffer); i++){
			if(tugset == 1){ //to denote if ':' has passed
                                if(buffer[i] == '-')
                                        tug1++;
                                else{
                                        if(tug1 == 0)
                                        temp_char01 += buffer[i];
                                        else if(tug1 == 1)
                                        temp_char02 += buffer[i];
                                        else if(tug1 == 2)
                                        temp_char03 += buffer[i];
                                }
                        }
                        if(buffer[i] == ':'){
                                tugset = 1;
                                i++;
                        }
                 }
                		
		fin.getline(buffer, 100);
		//sscanf(buffer, "%s %d:%d:%d", &trash, &time_hrs, &time_mins, &time_sec);
		
		fin.getline(buffer, 100); //for ---
	}
	fin.close();
	
        if(temp_char01.length() >= 1){ //check for valid stoi arguments incase of an empty log file
        if(stoi(temp_char01) == ltm->tm_mday && stoi(temp_char02) == (1+ltm->tm_mon) && stoi(temp_char03) == (1900 + ltm->tm_year))
                is_newEntry = false;
        }

	if(is_newEntry){
	        //timer starts
	        timer();
                //timer ends
		fout.open("study_logs.txt", ios::app);
		day += 1;
		fout << "day: " << day << "\ndate: " << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year  << "\nstudy time: " << hrs << ":" << mins << ":" << sec <<"\n--------------------------------------------\n";
		fout.close();
	}
	
	else{   
	        //timer starts
	        timer();
                //timer ends  
                
		fin.open("study_logs.txt", ios::in);
		fout2.open("study_logs_temp.txt", ios::out);
		while(1){
			char buffer[100];
			char trash[100];
			if(fin.getline(buffer, 100).fail())
				break;
			sscanf(buffer, "%s %d", &trash, &temp_day);
			fout2 << buffer << endl;
		
			fin.getline(buffer, 100); //for date
			fout2 << buffer << endl;
			
			fin.getline(buffer, 100);
			
			int tug = 0;
			string temp_char1, temp_char2, temp_char3;
			for(int i = 0; i < strlen(buffer); i++){
                                if(buffer[i] == ':')
                                        tug++;
                                else{
                                        if(tug == 1)
                                        temp_char1 += buffer[i];
                                        else if(tug == 2)
                                        temp_char2 += buffer[i];
                                        else if(tug == 3)
                                        temp_char3 += buffer[i];
                                }
                        }
                        time_hrs = stoi(temp_char1);
                        time_mins = stoi(temp_char2);
                        time_sec = stoi(temp_char3);
			//cout << "\nhere" << time_hrs << ":" << time_mins << ":" << time_sec;
			
			//if not the last entry write the same, if it is the last entry update time. 
			if(temp_day != day)
				fout2 << buffer << endl;
			else{
				sec=sec+time_sec;
				mins=mins+time_mins+(sec/60);
				hrs=hrs+time_hrs+(mins/60);
				mins=mins%60;
				sec=sec%60;
				fout2 << "study time: " << hrs << ":" << mins << ":" << sec << endl;
			}
			
			fin.getline(buffer, 100); //for ---
			fout2 << buffer << endl;
		}
		fout2.close();
		fin.close();
		remove("study_logs.txt");
		rename("study_logs_temp.txt", "study_logs.txt"); 
	}

}

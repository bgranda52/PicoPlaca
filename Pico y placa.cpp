/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOLIVAR GRANDA
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string>
using namespace std;

#define TAM 1000
char date[TAM];
char day[20];
char placa[20];

int eplaca(string plac);
int dayn(int tp);
int findday(int pos, int tp);

int main()
{
	//string placa;
	int hour, auxd,tp;
	cout<<"ENTER A PLACA:"<<endl;
	cin.getline(placa,19,'\n');
	cout<<endl<<"ENTER A DATE (EX: MONDAY 9 OCTOBER 2017):"<<endl;
	cin.getline(date,300,'\n');
	cout<<endl<<"ENTER AN HOUR:(0-24)"<<endl;
	cin>>hour;
	cout<<endl<<"__________________________________________"<<endl;
    int auxp = eplaca(placa);
    
	if ((hour >= 7) && (hour <=9) || (hour >= 16) && (hour <=19)){
	int contador=0, i=0, tam, a=0;
		if ((auxp < 3) || (auxp == 9) || (auxp == 0))
		{
			tp=6;
			dayn(tp);
		}
		if ((auxp = 3) || (auxp = 4))
		{
			tp=7;
			dayn(tp);
		}
		if ((auxp = 5) || (auxp = 6))
		{
			tp=9;
			dayn(tp);
		}
		if ((auxp = 7) || (auxp = 8))
		{
			tp=8;
			dayn(tp);
		}
	}
	else
	cout<<"YOU CAN DRIVE, BE CAREFULL"<<endl;
	
	
}

int eplaca(string plac)
{
	int l,d;
	l = plac.length();
	string uD = plac.substr(plac.length()-1);
	d = atoi(uD.c_str());	
	return d;
}

int dayn(int tp)
{
	 int contador=0, i=0, tam, a=0;
     
     tam=1000;
 
        for ( i=0; i< tam ; i++)
        {           
            return findday(i,tp);
        }
}

int findday(int pos, int tp) 
{
 char aux[20];
  int auxtam= pos+tp;
  int i, xi;
 
  for ( i= pos, xi=0; i<= auxtam  ; i++,xi++)
   {
       aux[xi]=date[i];
   }
 
  aux[tp]='\0';
 
      if (( strcmp( aux, "MONDAY")==0 ) || ( strcmp( aux, "Monday")==0 )||( strcmp( aux, "monday")==0 ))
      cout<<"ALERT! YOU CANT DRIVE! ITS MONDAY!";
      if (( strcmp( aux, "TUESDAY")==0 ) || ( strcmp( aux, "Tuesday")==0 ) ||( strcmp( aux, "tuesday")==0 ))
      cout<<"ALERT! YOU CANT DRIVE! ITS TUESDAY!";
      if (( strcmp( aux, "WEDNESDAY")==0 ) || ( strcmp( aux, "Wednesday")==0 ) || ( strcmp( aux, "wednesday")==0 ))
      cout<<"ALERT! YOU CANT DRIVE! ITS WEDNESDAY!";
      if (( strcmp( aux, "THURSDAY")==0 ) || ( strcmp( aux, "Thusrday")==0 ) || ( strcmp( aux, "thursday")==0 ))
      cout<<"ALERT! YOU CANT DRIVE! ITS THRSDAY!";
      if (( strcmp( aux, "FRIDAY")==0 ) || ( strcmp( aux, "Friday")==0 ) ||( strcmp( aux, "friday")==0 ))
      cout<<"ALERT! YOU CANT DRIVE! ITS FRIDAY!";
}



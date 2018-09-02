/*
** Roll Number: 2018201101
	Name: Suchismith Roy

*/





#include "normalmode.h"
void normalModeOn()
{
   

    tcgetattr(0, &initialsettings);
    memcpy(&newsettings, &initialsettings, sizeof(newsettings));
    newsettings.c_lflag &= ~(ICANON | ECHO);
    newsettings.c_cc[VMIN] = 1;
    newsettings.c_cc[VTIME] = 0;
    newsettings.c_lflag &= ~ISIG;
    tcsetattr(0, TCSANOW, &newsettings);
   
}

void normalModeOff()
{
  
    tcsetattr(0, TCSANOW, &initialsettings);
   
}

void textModeOn()
{
	tcgetattr(0, &newsettings);
	memcpy(&textsettings, &newsettings, sizeof(newsettings));
    textsettings.c_lflag &= ECHO;
    if(tcsetattr(0, TCSANOW, &textsettings)!=0)
    	cout<<"could not set attribute\n";

}

void textModeOff()
{
	tcsetattr(0, TCSANOW, &initialsettings);

}


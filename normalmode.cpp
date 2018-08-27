#include "normalmode.h"
void normalModeOn()
{
   

    tcgetattr(0, &initialsettings);
    memcpy(&newsettings, &initialsettings, sizeof(newsettings));
    newsettings.c_lflag &= ~(ICANON | ECHO);
    newsettings.c_cc[VMIN] = 1;
    newsettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newsettings);
    //handleKeys();
   
}

void normalModeOff()
{
  
    tcsetattr(0, TCSANOW, &initialsettings);
   
}



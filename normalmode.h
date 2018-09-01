

#ifndef NORMALMODE_H
#define NORMALMODE_H


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <limits.h>
using namespace std;
static struct termios initialsettings, newsettings,textsettings;



void normalModeOn();
void normalModeOff();
void textModeOn();
void textModeOff();

#endif
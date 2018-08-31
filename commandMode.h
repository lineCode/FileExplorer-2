

#ifndef COMMANDMODE_H
#define COMMANDMODE_H
#include <vector>
#include <stack>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <dirent.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <termios.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include<string.h>

void commandModeOn();
int fetchCommands(string command);
void commandModeOff();
int executeCommands(string command);
void createDir(string path);
void createFile(string path);



#endif


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
#include <sstream>
void gotodir(string command);
void rename(string command);
void populateCommands();
void commandModeOn();
void commandModeOff();
void executeCommands(string command);
void createDir(string path);
void createFile(string path);
void gotodir(string command);
void deletefile(string command);
void deletedir(string command);
#define ESC  27
#define ENTER   10
#define HOME 'h'
#define BACK 127


#endif
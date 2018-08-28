
#ifndef FILELISTING_H
#define FILELISTING_H
#include <vector>
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


static struct winsize size;

#define ESC  27
#define ENTER   10


void move_down(int dis); 
void move_up(int dis); 
void move_left(int dis); 
void move_right(int dis); 
void setCursorAtEnd();
void handleDirectoryName();
using namespace std;


void FileExplorer();
void handleOutput();

void errorHandler(int code);
void listFile(char *dirname);

char* handleDirectoryName(char* dir);

#endif

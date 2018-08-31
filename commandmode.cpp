#include <iostream>
#include<string.h>
using namespace std;
#include<vector>
#include<sstream>

#include "normalmode.h"
#include "commandMode.h"


void commandModeOn()
{

	string command;
	char ch;
	int i=0;
	
	while(1)
	{

		char ch=getchar();
		command+=ch;



		if((int)ch==ESC)
			return;
		if((int)ch==BACK)
		{
			std::remove(command.begin(),command.end(),ch);
			cout<<command;
		}

	}
}
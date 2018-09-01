#include <iostream>
#include<string.h>
using namespace std;
#include<map>
#include "normalmode.h"
#include "commandMode.h"
struct winsize size_win;
string homeDir;
string homeDir1;
	string command="";
map<string,int> mapOfCommands;
void populateCommands()
{


	mapOfCommands.insert(pair<string,int>("create_file",0));
	mapOfCommands.insert(pair<string,int>("create_dir",1));
	mapOfCommands.insert(pair<string,int>("rename",2));
	mapOfCommands.insert(pair<string,int>("goto",3));
	mapOfCommands.insert(pair<string,int>("delete_file",4));
	mapOfCommands.insert(pair<string,int>("delete_dir",5));
	//mapOfCommands.insert(pair<string,int>("create_file",0));
}

void gotodir(string command)
{	

	stringstream test(command);
	string segment;
	vector<string> commandlist;


	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string destnPath=commandlist[1];
	if(destnPath.find("/")!=std::string::npos)
		destnPath=homeDir1;
	else
		homeDir1+=destnPath;
	chdir(destnPath.c_str());
	



	char currentDir[PATH_MAX];
	if(getcwd(currentDir, sizeof(currentDir)) == NULL) 
	{
		cout<<"error in fetching current directory";
	}
	cout<<"currentDir changed"<<currentDir;



}


void rename(string command)
{

	homeDir1=homeDir;


	stringstream test(command);
	string segment;
	vector<string> commandlist;


	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string oldName=commandlist[1];
	string newName=commandlist[commandlist.size()-1];
	int status=rename(oldName.c_str(),newName.c_str());
	if(status!=0)
		cout<<"error in renaming";




}
void executeCommands(string command)
{

	stringstream test(command);
	string segment;
	vector<string> commandlist;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}

	string commandpart=commandlist[0];
	cout<<commandpart;
	if(mapOfCommands.find(commandpart)!=mapOfCommands.end())
	{

		int comm=mapOfCommands[commandlist[0]];
		cout<<comm;

		switch(comm)
		{


			case 0:createFile(command);
					break;
			case 1:createDir(command);
					break;
			case 2:rename(command);
					break;
			case 3:gotodir(command);
					break;
			case 4:deletefile(command);
					break;
			case 5:deletedir(command);
					break;		

							}

	}
	else
	{
		cout<<"command not found";
	}



}


void deletefile(string command)
{


		homeDir1=homeDir;


	stringstream test(command);
	string segment;
	vector<string> commandlist;
	FILE *fptr;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string fileName=commandlist[1];
	homeDir1+="/";
	homeDir1+=fileName;
	int status=remove(homeDir1.c_str());
	if(status!=0)
		cout<<"check the file name";








}


void deletedir(string command)
{

	homeDir1=homeDir;
	stringstream test(command);
	string segment;
	vector<string> commandlist;
	FILE *fptr;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string directoryName=commandlist[1];
	homeDir1+="/";
	homeDir1+=directoryName;

	int status=rmdir(homeDir1.c_str());
	if(status!=0)
		cout<<"check the file name";





}




void createDir(string command)
{



	homeDir1=homeDir;


	stringstream test(command);
	string segment;
	vector<string> commandlist;
	FILE *fptr;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string fileName=commandlist[1];
	string destn=commandlist[commandlist.size()-1];

	if(destn.find("~")!=std::string::npos)
		
		{	
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;


		}
		else if(destn.find(".")!=std::string::npos)
		{
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;

		}
		else
		{
			homeDir1+=destn;
			destn=homeDir1;
		}
		destn+="/";
		destn+=fileName;
		mkdir(destn.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		
}
void createFile(string command)
{
	
	homeDir1=homeDir;
	stringstream test(command);
	string segment;
	vector<string> commandlist;
	FILE *fptr;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	string folderName=commandlist[1];
	string destn=commandlist[commandlist.size()-1];

	if(destn.find("~")!=std::string::npos)
		
		{	
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;


		}
		else if(destn.find(".")!=std::string::npos)
		{
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;

		}
		else
		{
			homeDir1+=destn;
			destn=homeDir1;
		}
		destn+="/";
		destn+=folderName;
		
		fptr=fopen(destn.c_str(),"w");
		if(fptr!=NULL){
			cout<<"file created at destination";
			fclose(fptr);
		}
		else
			cout<<"invalid destination directory"<<destn;

		int status;

			status = mkdir(destn.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}





void commandModeOn()
{

	populateCommands();
	if (ioctl(0, TIOCGWINSZ, (char *) &size_win) < 0)
		cout<<"error in fetching window size";
	char currentDir[255];
	if(getcwd(currentDir, sizeof(currentDir)) == NULL) 
	{
		cout<<"error in fetching current directory";
	}
	string str(currentDir);
	homeDir=str;
	homeDir1=str;	
	int last_row=size_win.ws_row;

	string mode="COMMAND MODE";



	char ch;
	int i=0;
	
	while(1)
	{

		char ch=getchar();
		
		cout<<ch;


		if((int)ch==ESC)
			return;
		if((int)ch==BACK && command!="")
		{

			command.pop_back();
			printf("\x1b[%d;%dH",last_row,mode.length()+1);

			cout<<command;
			cout<<" ";
			printf("\x1b[%d;%dH",last_row,mode.length()+command.length()+1);
			//cout<<command;
			 continue;
		
		}
		if((int)ch==ENTER){
			
			if(command!="")
				executeCommands(command);
			command="";
			continue;
		}
		
		command+=ch;

	}
}
/*
** Roll Number: 2018201101
	Name: Suchismith Roy

*/





#include "normalmode.h"
#include "commandMode.h"
struct winsize size_win;
struct stat fileDetails;
static struct winsize size;
string homeDir;
string homeDir1;
int totalrows;
	string command="";
map<string,int> mapOfCommands;
using namespace std;

void populateCommands()
{


	mapOfCommands.insert(pair<string,int>("create_file",0));
	mapOfCommands.insert(pair<string,int>("create_dir",1));
	mapOfCommands.insert(pair<string,int>("rename",2));
	mapOfCommands.insert(pair<string,int>("goto",3));
	mapOfCommands.insert(pair<string,int>("delete_file",4));
	mapOfCommands.insert(pair<string,int>("delete_dir",5));
	mapOfCommands.insert(pair<string,int>("copy",6));
	mapOfCommands.insert(pair<string,int>("move",7));
}
// move files and directories

void move(string command)
{


	vector<string> commandlist;
	stringstream test(command);
	string segment="";
	string destn="";
	
	while(getline(test,segment,' '))
	{   
        
  		commandlist.push_back(segment);
	}
	destn=commandlist[commandlist.size()-1];

	for(int i=1;i<=commandlist.size()-2;i++)
	{

		string folder=commandlist[i];
		cout<<folder;
		chdir(homeDir.c_str());
		stat(folder.c_str(),&fileDetails);
		mode_t permission=fileDetails.st_mode;
		char dir=permission & S_IFDIR ? 'd' : '-';
		if(dir=='-')
		{	
			//cout<<"it is a file";
			moveFiles(folder,destn);
		
		 	
		}
		if(dir=='d')
		{
			moveDirectories(folder,destn);
		}



	}













}


void moveFiles(string source,string destn)
{

	string homeDir1=homeDir;
	FILE *fptr1,*fptr2;

		if(destn.find("~")!=std::string::npos)
		{	
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;


		}	
		 





		 	destn+="/";
		 	destn+=source;
			fptr2=fopen(destn.c_str(),"w");
			fptr1=fopen(source.c_str(),"r");
			if(fptr1==NULL)
				cout<<"Wrong file";
			if(fptr2==NULL)
				cout<<"Wrong file";




			if(fptr1!=NULL && fptr2!=NULL){

			char ch;
			while((ch=fgetc(fptr1))!=EOF)
			{
			
				fputc(ch,fptr2);
			}
			fclose(fptr1);
			fclose(fptr2);
			remove(source.c_str());
			cout<<"files copied succesfully";
			}
			
			

}





//copies files and directories


void copyCommand(string command)
{
	vector<string> commandlist;
	stringstream test(command);
	string segment="";
	string destn="";
	
	while(getline(test,segment,' '))
	{   
        
  		commandlist.push_back(segment);
	}
	destn=commandlist[commandlist.size()-1];

	for(int i=1;i<=commandlist.size()-2;i++)
	{

		string folder=commandlist[i];
		cout<<folder;
		chdir(homeDir.c_str());
		stat(folder.c_str(),&fileDetails);
		mode_t permission=fileDetails.st_mode;
		char dir=permission & S_IFDIR ? 'd' : '-';
		if(dir=='-')
		{	
			//cout<<"it is a file";
			copyFiles(folder,destn);
		
		 	
		}
		if(dir=='d')
		{
			copyDirectories(folder,destn);
		}



	}





}




void moveDirectories(string source,string destn)
{
	string homeDir1=homeDir;
	copyDirectories(source,destn);	
	homeDir1=homeDir1+"/"+source;
	deleteDirRecu(homeDir1);


}





void copyDirectories(string source,string destn)
{
	DIR *dp;
	struct dirent *dirp;
	vector<string> directoryList;
	vector<string> destinationList;
	string homeDir1=homeDir;
	if(source.find("/")!=std::string::npos)
	{
		homeDir1+=source;
	    destn=destn+source;
	    directoryList.push_back(homeDir1);
	    destinationList.push_back(destn);
	}
	else
	{
	homeDir1+="/"+source;

	directoryList.push_back(homeDir1);
	destn=destn+"/"+source;
	destinationList.push_back(destn);

	}

	while(!directoryList.empty()){

		 	string traverseDir=directoryList.front();
		 	string target=destinationList.front();
		 	destinationList.erase(destinationList.begin());
		 	directoryList.erase(directoryList.begin());
		
   			stat(target.c_str(), &fileDetails);
		 	mkdir(target.c_str(),fileDetails.st_mode);
		 	DIR *dp;
		 	if( (dp = opendir(traverseDir.c_str()))!=NULL)
		 		dirp = readdir(dp);
		 	
		 	chdir(traverseDir.c_str());
		 	while ((dirp = readdir(dp)) != NULL){

		 		 stat(dirp->d_name,&fileDetails);
				 mode_t permission=fileDetails.st_mode;
				 char dir=permission & S_IFDIR ? 'd' : '-';
				 if(dir=='d')
				 {

				 	if(strcmp(dirp->d_name,".")){
				 		string presentDir=traverseDir+"/"+dirp->d_name;
				 		destn=destn+"/"+dirp->d_name;
				 		string targetDir;
				 		targetDir=target+"/"+dirp->d_name;
				 		directoryList.insert(directoryList.begin(),presentDir);
				 		destinationList.insert(destinationList.begin(),targetDir);
				 	}
				 }
				 else
				 {

				 	string targetFile="";
				 	targetFile=target+"/"+dirp->d_name;

				 	fopen(targetFile.c_str(),"w");
				 }
			}	


	}

}




void copyFiles(string source,string destn)
{

	string homeDir1=homeDir;
	FILE *fptr1,*fptr2;

		if(destn.find("~")!=std::string::npos)
		{	
			int index=destn.find("~");
			destn.replace(index,1,"");
			homeDir1+=destn;
			destn=homeDir1;


		}	
		 





		 	destn+="/";
		 	destn+=source;
			fptr2=fopen(destn.c_str(),"w");
			fptr1=fopen(source.c_str(),"r");
			if(fptr1!=NULL && fptr2!=NULL){

			char ch;
			while((ch=fgetc(fptr1))!=EOF)
			{
			
				fputc(ch,fptr2);
			}
			fclose(fptr1);
			fclose(fptr2);
			}
			cout<<"files copied succesfully";

}






//changes curent directory to given directory

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
//renames the files mentioned

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
	if(mapOfCommands.find(commandpart)!=mapOfCommands.end())
	{

		int comm=mapOfCommands[commandlist[0]];
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
			case 6:copyCommand(command);	
					break;
			case 7:move(command);
					break;
							}

	}
	else
	{
		cout<<"command not found";
	}



}
// delete files

void deletefile(string command)
{

	string homeDir1=homeDir;
	stringstream test(command);
	string segment;
	vector<string> commandlist;
	FILE *fptr;

	while(getline(test, segment, ' '))
	{
   		commandlist.push_back(segment);
	}


	cout<<commandlist.size();

	for(int i=1;i<commandlist.size();i++)
	{

		string folder=commandlist[i];
		homeDir1+="/";
		homeDir1+=folder;
		cout<<homeDir1;
		int status=remove(homeDir1.c_str());
		if(status!=0)
		cout<<"check the file name";
		else
			cout<<"Deleted succesfully";

	}		



}
//deletes 
void deleteDirRecu(string path)
{

	DIR *dp;
	struct dirent *dirp;
	cout<<path;

	chdir(path.c_str());
	if( (dp = opendir(path.c_str()))!=NULL){
		while ((dirp = readdir(dp)) != NULL){

		 		 stat(dirp->d_name,&fileDetails);
				 mode_t permission=fileDetails.st_mode;
				 char dir=permission & S_IFDIR ? 'd' : '-';

				 if(dir=='d')
				 {

				 	if(strcmp(dirp->d_name,".") &&  strcmp(dirp->d_name,"..")){
				 		string presentDir=path+"/"+dirp->d_name;
				 		cout<<presentDir<<"\n";
				 		deleteDirRecu(presentDir);
				 		rmdir(presentDir.c_str());
				 	}
				 	else{

				 		rmdir(dirp->d_name);
				 	}

				 }
				 else
				 {

				 	remove(dirp->d_name);
				 }
			}	
	}

	rmdir(path.c_str());

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


	for(int i=1;i<commandlist.size();i++)
	{

		string folder=commandlist[i];
		homeDir1+="/";
		homeDir1+=folder;
		cout<<homeDir1;
		deleteDirRecu(homeDir1);

	}	



	// string directoryName=commandlist[1];
	// homeDir1+="/";
	// homeDir1+=directoryName;

	// int status=rmdir(homeDir1.c_str());
	// if(status!=0)
	// 	cout<<"check the file name";
	




}



// creates new directory
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

//create new file
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
		totalrows=size.ws_row;
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
	command="";

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
			
			if(command!=""){
				executeCommands(command);

			}
			
			command="";
			continue;
		}
		
		command+=ch;

	}
}
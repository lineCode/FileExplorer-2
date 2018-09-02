/*
** Roll Number: 2018201101
	Name: Suchismith Roy

*/



#include "filelisting.h"
#include "normalmode.h"
#include "commandMode.h"
using namespace std;



int visit=0;               		
int trajectory_index=0;
int visit_flag=0;
int offset=0;
int upper_end=1;
int lower_end=0;
int total_rows=0;
int current_pos=1;
int overflow_flag=0;
int firstVisit=0;
int current_ind=0;
int debug=0;
string currentDir="";
string homeDirectory="";
vector<string> trajectory;
struct fileAttributes{

        char user_grp_others[12];
        string user_name;
        string group_name;
        string last_modified_time;
        char b;
        size_t file_size;
        string dirname;
};
vector<fileAttributes> directories;






void resetCursor()
{
	current_pos=1;
	offset=0;
	int upper_end=1;
	int lower_end=0;

}

void clearScr()
{
	printf("\x1b[2J");
	printf("\x1b[1;1H");
}


void redraw()
{
printf("\x1b[1;1H");
}
void setCursorAtEnd()
{
	printf("\x1b[%d;1H",lower_end);
}

void printFileAttributes(int start,int end){

	struct fileAttributes fileattr;

	if(end>directories.size())
		end=directories.size()-1;
	
	for(int i=start;i<=end;i++)
	{

		fileattr=directories[i];

		cout<< fileattr.user_grp_others << " "<< fileattr.user_name << " " << fileattr.group_name << " " << 
		fileattr.file_size <<fileattr.b<<" "<< fileattr.last_modified_time<<" "<<fileattr.dirname <<"\n";

	}
	
	


}

string handleDirectoryName(string dir)
{

        
		if(dir[0]=='/')		
        	return dir;
        else
        {
        	string dir2="";
        	dir2+="/";
        	dir2+=dir;
        	currentDir+=dir2;
        	return currentDir;


        }



}

void move_up(int dis)
{
	
		
		if(current_pos>=upper_end )
		{
		current_pos-=dis;
		printf("\033[%d;1H",current_pos);
		}
		else
		{	
				
		if(offset && overflow_flag){
			clearScr();
			printFileAttributes(offset-1,lower_end+offset-1);
			redraw();
			offset-=1;
		}

		}
		

}


void move_down(int dis)
{
	
	
	if(current_pos<lower_end)
	{	
		current_pos+=dis;
		
		printf("\033[%d;1H",current_pos);
		
		
	}
	else
	{
		if(overflow_flag){
		
		clearScr();
		if(lower_end+offset-1<directories.size()){
			printFileAttributes((upper_end-1)+offset,lower_end+offset-1);
			
			printStatusLine("NORMAL MODE");
			setCursorAtEnd();
			offset+=1;
		}
		else
			printFileAttributes((upper_end-1)+offset,lower_end+offset-2);
		}

	}






	
}

void move_left()
{



	if(visit_flag)
	{	

		 trajectory_index>0?trajectory_index-=1:trajectory_index=0;
		 string visited_dir=trajectory[trajectory_index];
		 currentDir=visited_dir;
		 directories.erase(directories.begin(),directories.end());
		 listFile(currentDir);

		

	}

	

}
void move_right()
{


	if(visit_flag)
	{	


		trajectory_index<trajectory.size()-1?trajectory_index+=1:trajectory_index=trajectory.size()-1;
		string visited_dir=trajectory[trajectory_index];
		currentDir=visited_dir;
		directories.erase(directories.begin(),directories.end());

		listFile(currentDir);


	}

		
	



}








void handleOutput(){
    
     while(1){
     	int c = getchar();
		if(c==ESC)
		{

			char brac=getchar();

			if(brac=='[')
			{

				switch (getchar()) {
            		case 'A':
						move_up(1);
                		break;
            		case 'B':
                		move_down(1);
                		break;
            		case 'C':
                		move_right();
                		break;
            		case 'D':
                		move_left();
                		break;
            		
        	}	

		}


		}
		else if(c==ENTER)
		{	
			
			
			
			struct fileAttributes fileattributes=directories[current_pos+offset-1];
			string selectedDir=directories[current_pos+offset-1].dirname;
			visit_flag=1;
			  

			 if(fileattributes.user_grp_others[0]=='d')

			 {

			  	if(selectedDir==".."){
	
			  	 		currentDir=homeDirectory;

			  	 	}
			  	 else if(selectedDir==".")
			  	 {
			  	 	currentDir=currentDir;
			  	 }	
				 else{
				 	visit+=1;		 	
				 	selectedDir=handleDirectoryName(selectedDir);			  
				 	trajectory.push_back(selectedDir);
				 	trajectory_index+=1;
				 	 
				 	}

			 	directories.erase(directories.begin(),directories.end());	
				listFile(currentDir);

			  }
			  else if(fileattributes.user_grp_others[0]=='-'){
			  	int pid;
			   	pid = fork();
			   	string path;
			   	path=currentDir;
			   	path+="/";

			   	path+=selectedDir;
				if (pid == 0) {

					if(path.find(".txt")!=string::npos || path.find(".h")!=string::npos || path.find(".cpp")!=string::npos|| path.find(".c")!=string::npos)
					{
					execl("/usr/bin/gedit", "gedit", path.c_str(), (char *)0);
					}//execv("gedit",path.c_str());
  					else if(path.find(".mp3")!=string::npos || path.find(".mp4")!=string::npos ||path.find(".mkv")!=string::npos )
  					execl("/snap/bin/vlc", "vlc", path.c_str(), (char *)0);	
  					else if(path.find(".pdf")!=string::npos)
  					execl("/usr/bin/evince", "evince", path.c_str(), (char *)0);
  					else
  					execl("/usr/bin/xdg-open", "xdg-open", path.c_str(), (char *)0);

  					exit(1);
				 }
			  	}
			  	

		}
		else if(c==HOME)
		{	
			currentDir=homeDirectory;
			visit=1;
			directories.erase(directories.begin(),directories.end());
			listFile(homeDirectory);


		}
		else if(c==BACK)
		{


			if(currentDir!=homeDirectory){
	
						string lastVisitedDir=trajectory[trajectory_index];
						lastVisitedDir=lastVisitedDir.substr(0,lastVisitedDir.find_last_of("/"));
						currentDir=lastVisitedDir;
						trajectory.push_back(lastVisitedDir);
						trajectory_index+=1;
						directories.clear();
						listFile(currentDir);
			}



		}
		else if(c==':')
		{

			printStatusLine("COMMAND MODE");
			commandModeOn();
			clearScr();
			//printFileAttributes(upper_end-1,lower_end-1);
			//printStatusLine("NORMAL MODE");
			directories.clear();
			listFile(currentDir);
			redraw();
			continue;			

		}
		else if(c=='q')
		{

		
			return;
		}

	}

}





void errorHandler(int code){


	switch(code){

		case 11:cout<<"please enter file name";
				break;

		case 12:cout<<"please enter a valid filename/ directory";
				break;
		case 13:cout<<"Terminal Error";
				break;




	}
}



void FileExplorer()
{


	char currentDir1[PATH_MAX];

	char homeDirectory1[PATH_MAX];
	if(getcwd(currentDir1, sizeof(currentDir1)) == NULL) 
	{
		cout<<"error in fetching current directory";
	}
	currentDir=currentDir1;

	if(getcwd(homeDirectory1, sizeof(homeDirectory1)) == NULL) 
	{
		cout<<"error in fetching home directory";
	}
	homeDirectory=homeDirectory1;
	trajectory.push_back(homeDirectory);

	visit=1;
	cout<<homeDirectory;
	listFile(currentDir);
	handleOutput();
	return;


}


void printStatusLine(string mode)
{

	printf("\x1b[%d;0H",total_rows+2);
	cout<<mode;
	
}

void fetchWindowSize(int descriptor)
{
	if (ioctl(descriptor, TIOCGWINSZ, (char *) &size) < 0)
	errorHandler(13);
	total_rows=size.ws_row-2;
	
}

void resizeSignal(int signal)
{
	fetchWindowSize(0);
	directories.clear();
	listFile(currentDir);

}


void listFile(string dirname)
{
		DIR *dp;

		struct dirent *dirp;
		struct stat fileDetails;
		struct group *group_details;
		struct passwd *user_details;
		struct fileAttributes fileattributes;
		char ugo[11];
		
		if(dirname==".." && visit==1)
			dirname=homeDirectory;
		if(signal(SIGWINCH,resizeSignal)!=SIG_ERR)
			fetchWindowSize(0);
		

		if((dp = opendir(dirname.c_str()))==NULL){
			cout<<"unable to open"<<dirname;
			errorHandler(12);


		}
		else
		{

			while ((dirp = readdir(dp)) != NULL)
			{	

					if(visit==1)
		    		stat(dirp->d_name,&fileDetails);
		    		else
		    		{

							string dname;
							dname=currentDir;
							dname+="/";
							dname+=dirp->d_name;
							stat(dname.c_str(),&fileDetails);
		    		}

			    mode_t permission=fileDetails.st_mode;
		    	ugo[0]=permission & S_IFDIR ? 'd' : '-';
		   		ugo[1]=permission & S_IRUSR ? 'r' : '-';
		   		ugo[2]=permission & S_IWUSR ? 'w' : '-';
		   		ugo[3]=permission & S_IXUSR ? 'x' : '-';
		   		ugo[4]=permission & S_IRGRP ? 'r' : '-';
		   		ugo[5]=permission & S_IWGRP ? 'w' : '-';
		   		ugo[6]=permission & S_IXGRP ? 'x' : '-';
		   		ugo[7]=permission & S_IROTH ? 'r' : '-';
		   		ugo[8]=permission & S_IWOTH ? 'w' : '-';
		   		ugo[9]=permission & S_IXOTH ? 'x' : '-';
		   		ugo[10]='\0';
		   		
		   		size_t fileSize=(fileDetails.st_size/1024);
		   		char t=(fileDetails.st_size/1024>1)?'K':'B';
		    	group_details=getgrgid(fileDetails.st_gid);
		    	user_details= getpwuid(fileDetails.st_uid);
		    	string user_name=user_details->pw_name;
		    	string group_name=group_details->gr_name;    
		    	string last_modified_time=ctime(&fileDetails.st_mtime);
		    	if(last_modified_time[last_modified_time.length()-1]=='\n')
		    		last_modified_time[last_modified_time.length()-1]='\0';
		    	strcpy(fileattributes.user_grp_others, ugo);		   		
		   		fileattributes.file_size=fileSize;
		    	fileattributes.user_name=user_name;
		    	fileattributes.group_name=group_name;
				fileattributes.last_modified_time=last_modified_time;
		    	fileattributes.dirname=dirp->d_name;
		    	fileattributes.b=t;
			    directories.push_back(fileattributes);		    	
	    	}

	    	if(total_rows<=directories.size())
				overflow_flag=1;
			lower_end= (overflow_flag)?total_rows:directories.size();
			resetCursor();
			clearScr();
	    	printFileAttributes(upper_end-1,lower_end-1);
	    	printStatusLine("NORMAL MODE");
	    	redraw();
	    	

   	
   		closedir(dp);
   }
   
}
































		

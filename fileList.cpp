#include "filelisting.h"
#include "normalmode.h"
using namespace std;
int offset=0;
int upper_end=1;
int lower_end=0;
int total_rows=0;
int current_pos=1;
int overflow_flag=0;
int current_ind=0;
int debug=0;
char parentDir[PATH_MAX]="";

struct fileAttributes{

        char user_grp_others[12];
        string user_name;
        string group_name;
        string last_modified_time;
        char b;
        size_t file_size;
        char* dirname;
};
vector<fileAttributes> directories;
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
	printf("\x1b[%d;1H",lower_end+1);
}

void printFileAttributes(int start,int end){

	struct fileAttributes fileattr;

	
	if(end>directories.size())
		end=directories.size()-1;
	if(start<0)
		start=0;
	for(int i=start;i<=end;i++)
	{

		fileattr=directories[i];

		cout << fileattr.user_grp_others << " "<< fileattr.user_name << " " << fileattr.group_name << " " << 
		fileattr.file_size <<fileattr.b<<" "<< fileattr.last_modified_time<<" "<<fileattr.dirname <<"\n";

	}
	
	
		


}

char* handleDirectoryName(char* dir)
{

        
		if(dir[0]=='/')		
        	return dir;
        else
        {

        	char* dir2;
        	int i;	
        	dir2[0]='/';
        	for( i=1;dir[i-1]!='\0';i++)
        		dir2[i]=dir[i-1];
        	dir2[i]=dir[i];


        	//cout<<"directory is"<<dir2;
        	strcat(parentDir,dir2);

        	return parentDir;


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
		offset+=1;
		clearScr();
		printFileAttributes((upper_end-1)+offset,lower_end+offset-1);
		setCursorAtEnd();
	}

	}






	
}

void move_left()
{printf("\033[%dC",1);

}
void move_right()
{
	// string str1=directories[current_pos].dirname;
	// char *filename = new char[str1.length() + 1];
	// strcpy(filename, str.c_str());
	// listFile(.c_str());
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
                		move_left();
                		break;
            		case 'D':
                		move_right();
                		break;
            		
        	}	

		}


		}
		else if(c==ENTER)
		{	
			
			
			//cout<<"you selected"<<handleDirectoryName(selectedDir);
			 struct fileAttributes fileattributes=directories[current_pos+offset-1];
			directories.push_back(fileattributes);
			 debug=1;
			 
			
			 directories.clear();
			directories.push_back(fileattributes);
			
			 if(fileattributes.user_grp_others[0]=='d')

			 {
			
			 	char* selectedDir=directories[current_pos+offset-1].dirname;	
			 	selectedDir=handleDirectoryName(selectedDir);
			 	cout<<selectedDir;
			 	
			 	listFile(selectedDir);

			  }

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


	//char pwd[PATH_MAX];

	if(getcwd(parentDir, sizeof(parentDir)) == NULL) 
	{
		cout<<"error in fetching current directory";
	}
	

		listFile(parentDir);



}







void listFile(char *dirname)
{
		DIR *dp;

		struct dirent *dirp;
		struct stat fileDetails;
		struct group *group_details;
		struct passwd *user_details;
		struct fileAttributes fileattributes;
		char ugo[11];
		if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
			errorHandler(13);
		total_rows=size.ws_row-2;

		if((dp = opendir(dirname))==NULL){
			errorHandler(12);
			cout<<"no issues here";

		}
		else
		{

		while ((dirp = readdir(dp)) != NULL)
		{	

		    	stat(dirp->d_name,&fileDetails);
		    	
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
		    	if(fileattributes==NULL)
		    		cout<<"it is null";
		    	if(debug==0){

		    	directories.push_back(fileattributes);
		    	
    			}	

    	}
    	if(debug==0){
    	if(total_rows<directories.size())
			overflow_flag=1;
		lower_end= (overflow_flag)?total_rows:directories.size();


    	clearScr();
    	if(debug==0)
    		printFileAttributes(upper_end-1,lower_end-1);
    	redraw();
    	handleOutput();
    	
   		}  
   		closedir(dp);
   }
   
}
































		

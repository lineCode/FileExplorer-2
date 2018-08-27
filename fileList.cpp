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
	for(int i=start;i<=end;i++)
	{

		fileattr=directories[i];

		cout << fileattr.user_grp_others << " "<< fileattr.user_name << " " << fileattr.group_name << " " << 
		fileattr.file_size <<fileattr.b<<" "<< fileattr.last_modified_time<<" "<<fileattr.dirname <<"\n";

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
		
		if(offset){
			clearScr();
			printFileAttributes(offset-1,lower_end+offset-1);




			redraw();
			offset-=1;
		}

		}
		

}


void move_down(int dis)
{
	
	
	if(current_pos<=lower_end)
	{	
		current_pos+=dis;
		
		printf("\033[%d;1H",current_pos);
		
	}
	else
	{

		offset+=1;
		clearScr();
		printFileAttributes((upper_end-1)+offset,lower_end+offset);
		setCursorAtEnd();


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
			printf("\033[40;70H");
			cout<<"you chose"<<directories[current_pos+offset-1].dirname;

			struct fileAttributes fileattributes;
			fileattributes=directories[current_pos+offset-1];
			if(fileattributes.user_grp_others[0]=='d')
				listFile(fileattributes.dirname);
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

	//row=directories.size();

		total_rows=size.ws_row-2;
		
	






		if((dp = opendir(dirname))==NULL)
			errorHandler(12);
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
		    	directories.push_back(fileattributes);
		    	
    	

    	}

    	if(total_rows<directories.size())
			overflow_flag=1;
		lower_end= (overflow_flag)?total_rows:directories.size();


    	clearScr();
    	printFileAttributes(upper_end-1,lower_end-1);
    	redraw();
    	handleOutput();
    	closedir(dp);
   		  
   }
}
































		

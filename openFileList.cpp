#include "filelisting.h"
#include "normalmode.h"



int
main(int argc, char *argv[])
{
		
		
		if(argc!=2)
			errorHandler(11);
		else
		{

			 // write(STDOUT_FILENO, "\033c", 3);
				// write(STDOUT_FILENO, "\x1b[0;0H", 3);
			
			normalModeOn();
			listFile(argv[1]);
			
			normalModeOff();


		}


		exit(0);
}

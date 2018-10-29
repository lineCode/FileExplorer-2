Terminal Based File Explorer System

Two modes of operation have been implemented. Normal mode and Command Mode.
The application extensively uses system calls for functioning of different components , in order to act as a 
single terminal based file explorer system.

Normal Mode:
This is the default mode in which the file explorer would open in. 
It will list all the files and directories, in alphabetically sorted order,  present in the directory, from which the program is executed. Current directory is treated as the Root directory, i.e. the file explorer will not go to the parent directory of the current directory. 
If the number of entries to be listed is more than the window size then the user will be able to scroll down, if required. 
Similarly scroll up if the user has scrolled to the very end of the list, list of all the files and folders of the current directory. 
If the length of file/directory  name is more than the window width, i.e. too long to fit in a  single line, it would wrap around in the next line. Application will scroll accordingly.


Important functionality of this explorer is that it lets user traverse to previously visited directories with the help of left and right arrow keys, visit home, root directory of the application, by pressing ‘h’ and go one step back in the traversal, i.e. previously visited directory with the help of “backspace” key. 
Going backward and forward with the help of left and right arrow key is similar to back/front feature of any browser.
Also, by pressing enter on any file, not directory, it would open that file and on closing the opened file, user will return to same state of the application in which he/she left it.

Command Mode:
By pressing ‘:’, user can enter command mode of the application where he/she can run basic linux commands like
copy:
Copy file(s) to a particular destination. File permission remain intact after copy.
move:
Move file(s) to a particular destination. File permission remain intact after move.
rename:
Rename any file or directory
create:
Create a file/directory in a specified location
delete:
Delete a file/directory. This command requires depth first  traversal on directory in case a directory has to be deleted.
goto:
Goto a particular location specified by the user. 
search:
Search for a particular file in the entire directory structure. It will perform breadth first search on the current directory and will list all the paths that has the mentioned file. User can traverse to any of the directories of the result. 






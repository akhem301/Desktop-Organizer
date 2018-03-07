# Desktop-Organizer
A program to clean your desktop files according to its type and organize it into the documents folder.

The following readme file includes all information regarding the requirements and 
working of the desktop oraginzer program.
It also includes some variations to clean any directory

Requirements:

1. A linux/unix operating system with bash/shell (ubuntu/fedora/mint/debian/macos/etc)
2. g++ compiler to run c++ file (version 6.4.x or above)

Files in the project:

1. README.txt - The documentation of everything related to the infrastructure engineering challenge.
2. deskorg.cpp - An efficient c++ code to search for all the files on the desktop
3. deskorg.sh - Shell script to move all the files from desktop to seperate folders in documents directory.
4. allformats.txt - Details of all image,video,music,etc formats to search.
5. deskorg - An executble file

How to run:

Step 1: Extract the zip file on desktop or any folder.
Step 2: Open terminal and change the directory to desktop_organizer folder
Step 3: Run the command "./deskorg.sh"

Observe the desktop and documents folder. All files of particular format have been moved to 
documents in their respective folders.
  
Working:

Aim - The aim of the challenge was to organize all the scattered files such as documents,videos,images on the desktop
	  in documents folder creating seperate folders for each type of file.
	  
How it works - The task is divided into two parts,

			   --> A c++ code which efficiently searches for the files on the desktop folder non-recursively
			       (recursively in variation section).
			       
			   --> A shell script to actually move the files to the specific folder in the documents directory.
				   
			
******** Working of C++ Code (deskorg.cpp) *********

Note: A lot of data structures are used to maintain the space and time effciency of the program.
	  Each data structure is mentioned with its usage in the code.

>>> Data Structures
	  
--> filelist[] -  We have initially declared a global array of vector of pair (a 2D dynamic array with 2 fields)
				  a string and an long integer. It stores the name of the files along with their size.

--> format - It is a map (a binary search tree) which maps a string value into an integer.
			 It stores all the file formats (eg. avi,png,jpg,mp3,mp4,zip,etc) and maps it to a specific number
			 according to its type. (Further discussed in format section).
			 
--> rmap -   It also is a binary search tree which maps reverse of format. It maps the same integer to its type (string)
			 For eg. 1 is mapped to video, 2 is mapped to photos ,etc.
			 

>>> Format storing (Line 84 to Line 88)

We are storing all the file formats corresponding to its type by taking input from a file (allformats.txt). 
Taking input from the file is beneficial in this situation as it allows easy updation of any new file format.
Just by updating the text file it allows us to segregate yet another file format form your desktop (further in format of files).

>>> Path building (Line 94 to Line 97)

Declaring four string variables for setting paths for different locations used in the code below.
One of the most important path variable is the home varible which allows to retrieve the home path of the system.
It frees the constraint of changing the path of home for every new system which would run this project, as it automatically
detects the home path and stores in the string home.

>>> Searching (Line 104 to Line 104 and Line 17 to Line 52)

This part includes the function call to search function. Which demands three parameters- directory name , sizelist(call by reference)
,flag.

The first parameter is clear by itself, the name of the directory to search for (Desktop for now).
Second parameter is an empty vector of pair (dynamic array) which is referred by address so that all the files to me moved are 
stored in the vector.
Third parameter is a boolean variable flag which decided for recursive and non-recursive search. (Set to false initially for 
non-recursive search).

The function searches for all the files, as soon as it encounters a file it will push it into the the sizelist.
But if it encounters a directory it does not recusrsively search for the directory ans simply continues. (Because flag = false)

As dynamic array takes O(1) to insert,

Time Complexity: O(numeber_of_files)

>>> Filtering (Line 105 and Line 54 to Line 72)
			 
This part is the function call to filter function which basically filters all the files based on their type and 
according to their format ans stores them into the main list (filelist[]).

It has two parameters,

First parameter is the sizelist which we obtained from the search function, which includes details of the all the files.
Second parameter is the map format. It has the mapping of the format to its type (Data Structures Section).

This function aims at filtering the files based on their extension. So to extract the extension we are not reading the 
whole file name as it can be very long. So we are instead evaluating the full name of the file from the end and breaking
the flow of control whenever we encounter a period (".").
We are exploiting the fact that average length of the extension is about 4 characters. So we have to maximum read upto 4 characters
from the end. Hence we are storing the characters in a string extension and then reversing it at the end.

We then check convert into the lower case and check whether the format of the extension exists or not.
If it does then we push it into our vector (filelist[]) otherwise discard it.

Let the number of files be n.

Time Complexity: O( 4 * n * log(n) ). Note: Here we can neglect the log(n) factor of the map as it is negligible.

>>> Logfile generation (Line 107 to Line 125)

This part of code generates a filelog.txt which includes the information of all the files which are being moved
from the desktop along with their sizes and total sizes of all documents.

>>> InformationFile Generation (Line 129 to Line 139)
			 
A fileinfo.txt is generated which has the names of the files to be moved but not their sizes. Their format is specific so that
the shell script can interpret the file and run the move operations accordingly toeach specific folder.

************************************ END ************************************************

************* Working of the shell script (deskorg.sh) **********************************

Shell script in the beginning compiles and runs the above c++ file (deskorg.cpp). Which intern generates the filelog.txt
and fileinfo.txt. 

The script initializes the location array which includes the folder names to be created and the 
filename variable (address of fileinfo.txt).

It is followed by a loop which reads the text file line by line and processes the files into the their respective folder with
the help of the infrastructure of the fileinfo.txt file and mv (move) command to move the files to the desired location.

*********************************** END **************************************************

Formats of Files:

Formats are very important in this task. You need to know what type of files you use on a daily basis and what are their formats.
We tend to download an external file from the internet genrally on our desktops. So there can be varying and a large number of files.
We need to add formats accordingly to our program.

If we would have har coded the formats in the cpp file then it would be very difficult for a normal person to 
add the format further.
By taking input from a file it makes it very easy to add the format in the text file.

+-----------------------+
|___Type___|__Code______|
|          |	        |
|  Video   |	  1     |
|  Photo   |	  2     |
|  Doc     |	  3     |
|  Zip	   |	  4     |
|  Music   |      5     |
+-----------------------+

To insert a particular format in the allformats.txt file.

--> Identify the type of extension 
--> Get the number code of the type from the above table
--> Insert the format as "format code".

For eg. mkv is a video type extension.
Video has the number code 1.

So it will be added as "mkv 1".
Refer to allformats.txt file for clear explanantion.



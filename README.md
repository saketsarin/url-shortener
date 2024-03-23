﻿# Installation Steps 

This is a step-by-step guide to install the required sqlite files and compile the code to run the url shortener script. It has been tested on a Windows machine, but should work on any OS with minor modifications. Feel free to reach out to me if you have any issues.

#### NOTE: Feel free to skip to step 5 to run the script as I have already compiled the required sqlite files here

**STEP 1:** install sqlite amalgation files from below link:

<https://www.sqlite.org/download.html>

![step 1](./img/image1.png)

**STEP 2:**  unzip the files into a new folder named “sqlite” in your root directory:

![step 2](./img/image2.png)

**STEP 3:**  open the root directory folder in a new vscode window, and your current file structure should be like:

![step 3](./img/image3.png)

**STEP 4:**  open the terminal and and run the following commands to go to the sqlite directory and compile our sqlite code:

1. `cd sqlite`
1. `gcc -c sqlite3.c`
1. `ar rcs libsqlite3.a sqlite3.o`

![step 4-1](./img/image4.png)

Your file structure should now look like:

![step 4-2](./img/image5.png)


**STEP 5:** now run the following commands to go back to the root directory and compile our code:

1. `cd ..`
1. `g++ -std=c++11 main.cpp url\_shortener.cpp -o url\_shortener.exe -I sqlite -L sqlite -lsqlite3`

![step 5-1](./img/image6.png)

the file directory should have an executable file now:

![step 5-2](./img/image7.png)


**STEP 6:** now, run the below command to run the executable, then input any url to shorten it:

1. `url\_shortener`

The file directory should have a database file (url\_shortener.db) now:

![step 6](./img/image8.png)

---

# Sample Output:

![output](./img/image9.png)

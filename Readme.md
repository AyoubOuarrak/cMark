#cMark
A small software to get device information and plot data into a line chart
###How does it works
cMark is composed by two part, a command line software written in C++ that collect memory info every 5 min (by default) and save data in a sqlite db. The command line software works in OSX, Linux and Windows. At compilation time the platform is checked and the appropriate header is included, compiled and linked. The design of software is Object Oriented and it use polymorphism, to offer the possibility to add new methods for monitoring other parts of the device.    
The second part of cMark is a gui that simply open the SQLite db, analyzes the data and displays it in a line chart.

###Technologies used 
The gui is written using web technologies and [electron](http://electron.atom.io) to build native apps. Charts are made using [chart.js](http://www.chartjs.org), a lovely javascript library that make beautiful charts. There is also something of [bootstrap](getbootstrap.com/) in the html code to do some layout trick.    
Using web stuff to build desktop apps is not a thing that I love, but in this case I turned a blind eye, why? Because I don't have the time to build native gui apps for osx, linux and windows from scratch, the performance in the gui is not a priority (in this case. 

###Dependencies
To compile and run cMark you need a C++ compiler with std11 compatibility, cmake and sqlite3.    
If you want to run the gui, you need Node.js and npm.

###How to compile
just type in the root dir of the project:   
``` cmake CMakeLists ```  
``` make ```   
``` ./build/cMark ```    
cMark will start collecting data, don't except to receive some output from the command line, you will notice the presence of the SQLite db in build dir.   

####Run the gui
``` cd app```  
``` npm start```
the gui will start showing a chart line from the SQLite db data 

###Testing
Tested in OSX El Capitan (clang-703.0.29), Windows 10 (MinGW) and Linux 14:04 (g++ 4.8.2)
In build dir, there is a memory.db for testing the gui, if you want to collect new data, delete the db from the buil dir.



-- About --

Battlestar-AI is a classic two-player battleships game
simulation written in C++. It is designed to be played by two
AIs at a time, for a given amount of rounds. An AI is loaded
at compile time by passing the address of an instance of your
AI to the Game object.

This simulation is designed for the GAPlayer class; a class that
tests concepts researched in a paper found at:
http://lostindev.com/files/FinalResearchPaper.pdf

-- Build --

This application runs on both WIN32 and Unix/Unix-Like systems.
This has been tested with GCC on a 32bit machine and VS2008.


To build via the make file, type:

$> make

To clean, type:

$> make clean

To run the application, type

$> ./battlestar-ai


To build via Visual Studion 2008:

Create a new win32 C++ console solution, make sure the project is empty
and is *not* using precompiled headers, and import the code by right-
clicking the project head in the directory tree and select "Add ->" and then
"Add Item...". No special build flags are needed.

-- Pre-Trained Data --

Pre-trained data, for each GA component, uses several data files to save
enemy-placement data over time. *.dat1 is used for placement. *.dat2 is
used for shooting. *.dat3 is used for sinking. All default data is named as
"Default.*"

-- Usage --

This is a simulation without any real-time interaction. Program
parameters are hard-coded; Modify, build, and run as needed.

PLEASE review Main.cpp and look for the section labeled CONFIGURATION.

-- Copyright Notice --

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the 
Free Software Foundation, either version 3 of the License, or (at your 
option) any later version.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
Public License for more details. (http://www.gnu.org/copyleft/gpl.html)

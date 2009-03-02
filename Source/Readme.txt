-- About --

Battlestar-AI is a classic two-player battleships game
simulation written in C++. It is designed to be played by two
AIs at a time, for a given amount of rounds. An AI is loaded
at compile time by passing the address of an instance of your
AI to the Game object.

-- Build --

This application runs on both WIN32 and Unix/Unix-Like systems.
This has been tested with GCC and VS2008.

To build via the make file, type:

$> make

To clean, type:

$> make clean

To run the application, type

$> ./battlestar-ai

To build via Visual Studion 2008:

Create a new win32 C++ project, make sure the project is empty
and is *not* using precompiled headers, and import the code. No
special build flags are needed.

-- Usage --

This is a simulation without any real-time interaction. Program
parameters are hard-coded; Modify, build, and run as needed.

-- Copyright Notice --

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the 
Free Software Foundation, either version 3 of the License, or (at your 
option) any later version.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
Public License for more details. (http://www.gnu.org/copyleft/gpl.html)

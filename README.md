# SanajahtiSolver

## What is this?
SanajahtiSolver is a program to solve the game Sanajahti. The game needs no
further explanations. This program can either be used to manually input the game,
and then solve it, or you can even solve Sanajahti games automatically with
an Android phone.

Basic usage can be seen from the following Youtube video: https://www.youtube.com/watch?v=4zfFo4Q2DFE

## Project Structure

This repository contains three subdirectories:

* plan/ for the plan 
* doc/  for the final documentation
* src/  for all the source code
* test/ for unit tests
* platform-tools/ for bundled Android SDK binaries
* tools/ for bundled Android SDK binaries

In addition there are a few files here:

* .gitignore
* CMakeLists.txt for build system
* README.md you're reading it..
* kotus.txt a bundled wordlist
* sanajahti.pro for qmake-based build system

## Instructions
### How to build the software
The software is built using CMake, which generates the required makefiles to build the software. As the program is written using Qt UI framework, Qt (version 5) must be installed to build the software. Build instructions:

1. Set environment variable QTDIR to your Qt installation directory (with right compiler), for example /Users/jma/Qt/5.5/clang_64/. Example command: export QTDIR="/Users/jma/Qt/5.5/clang_64/"
2. Use CMake in the main directory, where CMakeLists.txt is located, with command “cmake ./”
3. Build the program using command “make” in the same directory
4. The program is now built and ready to be used. Note that folders “tools” and “platform-tools” should be in the same folder as the executable, as these include binaries for android-interoperability

### How to use the software
- After starting the program you need to specify the library file containing all
the words needed by the solver. This is done by pressing button “Library”, and 
the selecting the correct file.
- Next you can let the program automatically solve game by using button 
“Auto Solve”. This feature takes screenshot of the phone screen, so make sure 
the game is running and the grid is visible. Alternatively you can manually fill
the grid and press button “Start” to show all the words found by the program on 
the screen.
- If you want to solve another grid you can use the Auto Solve feature straight 
away, but for manual inputting, you need to press the button “Restart” first.

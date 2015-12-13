### This is an example readme for the project.

This repository contains three subdirectories:

* plan/ for the plan 
* doc/  for the final documentation
* src/  for all the source code

You can write a short summary of your project into this file.
This file is read by the gitlab and is shown on the repository's front page.

## How to build project

This project uses a CMake based build system. User needs to have Qt5 installed.

Build steps:
1. set environment variable QTDIR to Qt directory, for example:
   export QTDIR="/Users/jma/Qt/5.5/clang_64/"
2. in sanajahti folder (where CMakeLists.txt is located) use cmake with command:
   "cmake ./"
3. use command "make" to build project
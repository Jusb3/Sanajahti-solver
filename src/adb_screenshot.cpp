#include "adb_screenshot.hpp"
#include <stdio.h>
#include <iostream>

// usage:
// auto adbscr = new ADBScreenShot();
// bool success = adbscr.takeScreenshot('grid.png');
// if(success) {
//   // read file saved at './grid.png'
// } else {
//   // couldn't get screenshot, handle this case.
// }

// Constructor where we define the path to adb tools and the global path
ADBScreenshot::ADBScreenshot(const std::string &path) : path(path)
{
    #ifdef _WIN32
        extension ="/platform-tools/adb.exe";
    #elif __linux__
        extension ="/platform-tools/adb_linux";
    #elif __APPLE__
        extension ="/platform-tools/adb_mac";
    #endif
}

// Function to take a screenshot. Saves <name>.png to current folder if
// succeeds. Otherwise returns false and prints error to stderr.
bool ADBScreenshot::takeScreenshot(const std::string &name)
{
    int is_adb = system(std::string(path+extension+std::string(" version")).c_str());
    if(is_adb != 0){
        std::cerr<<"ADB is not installed!"<<std::endl;
        return false;
    }

    // take the screenshot and save it to SD card
    int succ = system(std::string(path+extension+std::string(" shell screencap -p /sdcard/sanajahtiscr.png")).c_str());
    if(succ != 0){
        std::cerr<<"Failed to take a screenshot!"<<std::endl;
        return false;
    }

    // pull the file from the sdcard & remove it at the same time
    std::string pull_cmd = std::string(path+extension+std::string(" pull /sdcard/sanajahtiscr.png ./auto-generated_files/") + name);
    succ = system(pull_cmd.c_str());
    int rmsucc = system(std::string(path+extension+std::string(" shell rm /sdcard/sanajahtiscr.png")).c_str());
    if(succ != 0){
        std::cerr<<"Failed to fetch the screenshot from the mobile device!"<<std::endl;
        return false;
    }
    if(rmsucc != 0){
        std::cerr<<"Failed to remove the screenshot from the mobile device!"<<std::endl;
        return false;
    }

    return true;
}

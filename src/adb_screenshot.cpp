#include "adb_screenshot.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

// usage:
// auto adbscr = new ADBScreenShot();
// bool success = adbscr.TakeScreenshot('grid.png');
// if(success) {
//   // read file saved at './grid.png'
// } else {
//   // couldn't get screenshot, handle this case.
// }

// Function to take a screenshot. Saves <name>.png to current folder if
// succeeds. Otherwise returns false and prints error to stderr.
bool ADBScreenshot::TakeScreenshot(const std::string &name)
{
    int is_adb = system("adb version");
    if(is_adb != 0){
        std::cerr<<"ADB is not installed!"<<std::endl;
        return false;
    }

    // take the screenshot and save it to SD card
    int succ = system("adb shell screencap -p /sdcard/sanajahtiscr.png");
    if(succ != 0){
        std::cerr<<"Failed to take a screenshot!"<<std::endl;
        return false;
    }

    // pull the file from the sdcard & remove it at the same time
    std::string pull_cmd = std::string("adb pull /sdcard/sanajahtiscr.png ./") + name;
    succ = system(pull_cmd.c_str());
    int rmsucc = system("adb shell rm /sdcard/sanajahtiscr.png");
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

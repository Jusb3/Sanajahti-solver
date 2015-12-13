#pragma once
#include <string>

class ADBScreenshot
{
public:
        ADBScreenshot(const std::string &path);
        bool takeScreenshot(const std::string &name);
private:
        std::string extension;
        std::string path;
};

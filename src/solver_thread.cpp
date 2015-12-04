#include "solver_thread.hpp"
#include "adb_screenshot.hpp"
#include "window.hpp"



SolverThread::SolverThread()
{

}

void SolverThread::init(OCR ocr, vector<pair<string,vector<pair<int, int>>>> results, string path)
{
    this->ocr = ocr;
    this->results = results;
    this->path = path;
}
void SolverThread::run()
{
    std::ofstream myfile;
    myfile.open("commands.py");
    myfile << "from com.android.monkeyrunner import MonkeyRunner, MonkeyDevice\n";
    myfile << "device = MonkeyRunner.waitForConnection()\n";
    for(auto obj : results){
        for (auto route : obj.second) {
            std::pair<int,int> coord = ocr.getTileCoordinate(route.first-1,route.second-1);
            myfile << "device.touch("+to_string(coord.first)+string(", ")+to_string(coord.second)+string(", MonkeyDevice.DOWN)\n");
        }
        myfile << "MonkeyRunner.sleep(0.2)\n";
        myfile << "device.touch(0,0, MonkeyDevice.UP)\n";
    }
    myfile.close();
    system(string(string("C:/adb/win_tools/tools/monkeyrunner.bat ")+path+string("/../commands.py")).c_str());
}

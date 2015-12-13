#include "solver_thread.hpp"

SolverThread::SolverThread()
{
    //defining correct path for used operating system
    #ifdef _WIN32
        extension ="/tools/monkeyrunner.bat ";
    #else
        extension ="/tools/monkeyrunner ";
    #endif
}

//initializing function
void SolverThread::init(OCR ocr, std::vector<pair<std::string,std::vector<pair<int, int>>>> results, std::string path)
{
    this->ocr = ocr;
    this->results = results;
    this->path = path;
}

void SolverThread::run()
{
    //generating the monkeyrunner script-file for sending automated playing.
    std::ofstream myfile;
    myfile.open("auto-generated_files/commands.py");
    myfile << "from com.android.monkeyrunner import MonkeyRunner, MonkeyDevice\n";
    myfile << "device = MonkeyRunner.waitForConnection()\n";
    for(auto obj : results){
        for (auto route : obj.second) {
            std::pair<int,int> coord = ocr.getTileCoordinate(route.first-1,route.second-1);
            myfile << "device.touch("+std::to_string(coord.first)+string(", ")+std::to_string(coord.second)+string(", MonkeyDevice.DOWN)\n");
        }
        myfile << "MonkeyRunner.sleep(0.2)\n";
        myfile << "device.touch(0,0, MonkeyDevice.UP)\n";
    }
    myfile.close();
    //send script-file to monkeyrunner
    int mrsucc = std::system(std::string(path+extension+path+std::string("/auto-generated_files/commands.py")).c_str());
    if(mrsucc != 0){
        std::cerr << "Error running the MonkeyRunner script." << std::endl;
        emit showMB();
    }

}

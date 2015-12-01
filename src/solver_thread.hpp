#ifndef AUTOSOLVER_H
#define AUTOSOLVER_H
#include <QThread>
#include <QString>
#include <iostream>
#include "ocr.hpp"
#include "solver.hpp"

using namespace std;

class SolverThread : public QThread
{
    public:
        SolverThread();
        void init(OCR ocr, vector<pair<string, vector<pair<int, int>>>> results, string path);
    private:
        void run();
        OCR ocr;
        string path;
        vector<pair<string, vector<pair<int, int>>>> results;
};
#endif // AUTOSOLVER_H

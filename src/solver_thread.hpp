#ifndef AUTOSOLVER_H
#define AUTOSOLVER_H
#include <QThread>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <fstream>
#include "ocr.hpp"
#include "solver.hpp"

using namespace std;

class SolverThread : public QThread
{
    Q_OBJECT

    public:
        SolverThread();
        void init(OCR ocr, vector<pair<string, vector<pair<int, int>>>> results, string path);
        void run();

    private:
        OCR ocr;
        string path;
        string extension;
        vector<pair<string, vector<pair<int, int>>>> results;

    signals:
        void showMB();
};
#endif // AUTOSOLVER_H

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
    //initializing function
    void init(OCR ocr, vector<pair<string, vector<pair<int, int>>>> results, string path);
    //overrides function from QThread
    //executes the thread
    void run();
private:
    OCR ocr;
    string path;
    string extension;
    vector<pair<string, vector<pair<int, int>>>> results;
signals:
    //signal for main window to show error window
    void showMB();
};
#endif // AUTOSOLVER_H

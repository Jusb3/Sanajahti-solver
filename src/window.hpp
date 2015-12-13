#ifndef WINDOW_H
#define WINDOW_H
#pragma once
#include "solver.hpp"
#include "ui.hpp"
#include <fstream>
#include <QWidget>
#include <QSignalMapper>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include "ocr.hpp"
#include "solver_thread.hpp"

class QLineEdit;
class QString;
//Main 
class Window : public QWidget
{
    Q_OBJECT
public:
    //init all the basic elements of the window.
    Window();
    //return size of the x-axis of the grid.
    int getX();
    //return size of the y-axis of the grid.
    int getY();
    //returns the path of the library given.
    std::string getLibrary();
    // get the inputted character grid and return a vector of it
    // encodes the characters in the grid to a custom 64-bit fixed-width format
    std::vector<uint64_t> getGrid();
private:
    //creates tile to certain location and returns pointer to it.
    QLineEdit* addTile(int x, int y);
    //returns coordinates to center of tile
    QPoint tileMiddle(int id);
    //creates grid of size x * y
    void makeGrid(int x, int y);
    //returns true if all tiles of the grid contain a letter.
    bool gridFilled();
    //fill the list with all words found in the grid.
    void fillList();
    //calls the solver and sets elements properties.
    void solve();
    //appends line from start to end to lines
    void addLine(int start, int end);
    //paints path lines to window
    void paintEvent(QPaintEvent *);
    QVector<QLineEdit*> tiles;
    QVector<QLine> lines;
    QLineEdit* xpanel;
    QLineEdit* ypanel;
    QLineEdit* library_path;
    QPushButton* browse_button;
    QPushButton* start_button;
    QPushButton* restart_button;
    QPushButton* adb_button;
    QSignalMapper* mapper;
    QComboBox* list;
    SanajahtiSolver solver;
    SolverThread thread;
    QString path;
    vector<pair<string, vector<pair<int, int>>>> result;
public slots:
    //show messagebox if Monkeyrunner return error.
    void showMonkeyRunnerError();
private slots:
    //when value of a tile is changed, jump to next
    void valueChanged(int id);
    //change the grid size to that spefied by ypanel and xpanel.
    void gridChange();
    //saves the path of the library specified by user to field library_path and constructs solver with that library.
    void browse();
    //solves the grid from phone.
    void adb_start();
    //solves the grid specified by user.
    void manual_start();
    //adjust the grid to show the route of the word.
    void drawWord(const QString& word);
    //resets window so editing grid is possible.
    void restart();
};
#endif

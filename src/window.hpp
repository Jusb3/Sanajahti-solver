#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "solver.hpp"
#include <QSignalMapper>
#include <QPushButton>
#include <QComboBox>
#include "ocr.hpp"

class QLineEdit;
class QString;

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
    int getX();
    int getY();
    std::string getLibrary();
    std::vector<uint64_t>getGrid();
private:
    QLineEdit* addTile(int x, int y);
    void makeGrid(int x, int y);
    bool gridFilled();
    void fillList();
    QVector<QLineEdit*> tiles;
    QLineEdit* xpanel;
    QLineEdit* ypanel;
    QLineEdit* library_path;
    QPushButton* browse_button;
    QPushButton* start_button;
    QPushButton* restart_button;
    QPushButton* adb_button;
    QSignalMapper* mapper;
    QComboBox* list;
    vector<pair<string, vector<pair<int, int>>>> result;
    SanajahtiSolver solver;
private slots:
    void valueChange(int id);
    void gridChange();
    void browse();
    void manual_start();
    void adb_start();
    void drawWord(const QString& word);
    void restart();
};
bool longLex(const pair<string, vector<pair<int, int>>>& a,
             const pair<string, vector<pair<int, int>>>& b);
#endif

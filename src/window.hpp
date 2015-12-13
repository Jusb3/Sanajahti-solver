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

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
    int getX();
    int getY();
    std::string getLibrary();
    std::vector<uint64_t> getGrid();
private:
    QLineEdit* addTile(int x, int y);
    QPoint tileMiddle(int id);
    void makeGrid(int x, int y);
    bool gridFilled();
    void fillList();
    void solve();
    void addLine(int start, int end);
    void paintEvent(QPaintEvent *event);
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
private slots:
    void valueChange(int id);
    void gridChange();
    void browse();
    void manual_start();
    void adb_start();
    void drawWord(const QString& word);
    void restart();
};
#endif

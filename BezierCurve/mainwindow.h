#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "beziercurveeditor.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BezierCurveEditor m_editor;
};

#endif // MAINWINDOW_H

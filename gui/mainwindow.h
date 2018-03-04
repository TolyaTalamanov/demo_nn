#ifndef DEMO_NN_GUI_MAINWINDOW_H
#define DEMO_NN_GUI_MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
protected:
    void createActions();
};
#endif //DEMO_NN_GUI_MAINWINDOW_H

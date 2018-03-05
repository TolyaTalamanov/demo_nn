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
private:
    void open();
private:
    QImage  image;
    QLabel* imageLabel;

};
#endif //DEMO_NN_GUI_MAINWINDOW_H

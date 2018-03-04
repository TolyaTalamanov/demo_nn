#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(tr("Demo_nn"));
    createActions();
}

MainWindow::~MainWindow(){

}

void MainWindow::createActions(){
    QMenu* filemenu = menuBar()->addMenu(tr("&File"));
    QToolBar* fileToolBar = addToolBar(tr("File"));
}

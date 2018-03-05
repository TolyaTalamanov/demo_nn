#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow() : imageLabel(new QLabel) {
    setWindowTitle(tr("Demo_nn"));
    setCentralWidget(imageLabel);
    createActions();
}

MainWindow::~MainWindow() {

}

void MainWindow::createActions() {
    QMenu* filemenu = menuBar()->addMenu(tr("&File"));

    QAction* actOpen = new QAction("image open action", 0);
    actOpen->setText("&Open");
    actOpen->setShortcut(QKeySequence("CTRL+O"));

    connect(actOpen, &QAction::triggered, this, &MainWindow::open);

    filemenu->addAction(actOpen);
    QToolBar* ptb = new QToolBar("ToolBar");
    ptb->addAction(actOpen);
}

void MainWindow::open() { 
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath());
    if (!fileName.isEmpty()) {
      image.load(fileName);
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->show();
}

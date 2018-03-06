#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow() : _imageLabel(new QLabel) {
  setWindowTitle(tr("Demo_nn"));
  setCentralWidget(_imageLabel);
  createActions();
}

MainWindow::~MainWindow() {

}

void MainWindow::createActions() {
  QMenu* filemenu = menuBar()->addMenu(tr("&File"));

  QAction* actOpen = new QAction("image open action", 0);
  actOpen->setText("&Open...");
  actOpen->setShortcut(QKeySequence("CTRL+O"));

  QAction* actSave = new QAction("image save action", 0);
  actSave->setText("&Save");
  actSave->setShortcut(QKeySequence("CTRL+S"));

  QAction* actSaveAs = new QAction("image save as action", 0);
  actSaveAs->setText("&Save As...");
  actSaveAs->setShortcut(QKeySequence("CTRL+SHIFT+S"));

  connect(actOpen,   &QAction::triggered, this, &MainWindow::open);
  connect(actSave,   &QAction::triggered, this, &MainWindow::save);
  connect(actSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

  filemenu->addAction(actOpen);
  filemenu->addAction(actSave);
  filemenu->addAction(actSaveAs);

  QToolBar* ptb = new QToolBar("ToolBar");

  ptb->addAction(actOpen);
  ptb->addAction(actSave);
  ptb->addAction(actSaveAs);
}

void MainWindow::open() { 
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath());
  if (!fileName.isEmpty()) {
    _image.load(fileName);
  }
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
  _imageLabel->show();
}

void MainWindow::save(){
  //TODO 
}

void MainWindow::saveAs(){
  QString saveImagePath = QFileDialog::getSaveFileName(this, tr("Save"), "",
                                                       tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
  _image.save(saveImagePath);
}

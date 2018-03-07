#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow() {
  readSettings();

  setWindowTitle(tr("Demonstration neural networks"));

  createCentralWidget();
  createToolBar();

  createActions();
}

MainWindow::~MainWindow() {

}

void MainWindow::createActions() {
  createFileActions();
  createEditActions();
}

void MainWindow::open() { 
  QString imagePath = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath());
  if (!imagePath.isEmpty()) {
    _image.load(imagePath);
  }
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
  _imageLabel->show();
}

void MainWindow::save() {
  //TODO 
}

void MainWindow::saveAs() {
  QString saveImagePath = QFileDialog::getSaveFileName(this, tr("Save"), "",
                                                       tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
  _image.save(saveImagePath);
}

void MainWindow::paste() {
  const QClipboard* clipboard = QApplication::clipboard();
  const QMimeData* mimeData = clipboard->mimeData();

  if (mimeData->hasImage()) {
    QPixmap pixmap = qvariant_cast<QPixmap>(mimeData->imageData());
    _image = pixmap.toImage();
    _imageLabel->setPixmap(pixmap);
  }
}

void MainWindow::copy() {
  QApplication::clipboard()->setImage(_image, QClipboard::Clipboard);
}

void MainWindow::cut() {
  copy();
  _image = QImage();
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
}

void MainWindow::readSettings() {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
  if (geometry.isEmpty()) {
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2,
        (availableGeometry.height() - height()) / 2);
  } else {
    restoreGeometry(geometry);
  }
}

void MainWindow::writeSettings() {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  settings.setValue("geometry", saveGeometry());
}

void MainWindow::createFileActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

  const QIcon openIcon = QIcon::fromTheme("open-image", QIcon("../icons/open.png"));
  QAction* actOpen = fileMenu->addAction(openIcon, tr("&Open"), this, &MainWindow::open);
  actOpen->setShortcut(QKeySequence::Open);
  actOpen->setStatusTip(tr("Open image"));
  fileMenu->addAction(actOpen);
  _toolBar->addAction(actOpen);

  const QIcon saveIcon = QIcon::fromTheme("save-image", QIcon("../icons/save.png"));
  QAction* actSave = fileMenu->addAction(saveIcon, tr("&Save"), this, &MainWindow::save);
  actSave->setShortcut(QKeySequence::Save);
  actSave->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSave);

  QAction* actSaveAs = fileMenu->addAction(saveIcon, tr("&Save As..."), this, &MainWindow::saveAs);
  actSaveAs->setShortcut(QKeySequence::SaveAs);
  actSaveAs->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSaveAs);
  _toolBar->addAction(actSaveAs);

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("exit-image", QIcon("../icons/exit.png"));
  QAction* actExit = fileMenu->addAction(exitIcon, tr("&Exit"), this, &QWidget::close);
  actExit->setShortcut(QKeySequence::Quit);
  actExit->setStatusTip(tr("Exit the application"));
  fileMenu->addAction(actExit);

}

void MainWindow::createEditActions() {
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit")); 

  const QIcon cutIcon = QIcon::fromTheme("cut-image", QIcon("../icons/cut.png"));
  QAction* actCut = editMenu->addAction(cutIcon, tr("&Cut"), this, &MainWindow::cut);
  actCut->setShortcut(QKeySequence::Cut);
  actCut->setStatusTip(tr("Cut image"));
  editMenu->addAction(actCut);
  _toolBar->addAction(actCut);
  //actCut->setEnabled(false);

  const QIcon copyIcon = QIcon::fromTheme("copy-image", QIcon("../icons/copy.png"));
  QAction* actCopy = editMenu->addAction(copyIcon, tr("&Copy"), this, &MainWindow::copy);
  actCopy->setShortcut(QKeySequence::Copy);
  actCopy->setStatusTip("Copy image");
  editMenu->addAction(actCopy);
  _toolBar->addAction(actCopy);
  //actCopy->setEnabled(false);

  const QIcon pasteIcon = QIcon::fromTheme("paste-image", QIcon("../icons/paste.png"));
  QAction* actPaste = editMenu->addAction(pasteIcon, tr("&Paste"), this, &MainWindow::paste);
  actPaste->setShortcut(QKeySequence::Paste);
  editMenu->addAction(actPaste);
  editMenu->setStatusTip("Paste image");
  _toolBar->addAction(actPaste);

}

void MainWindow::createToolBar() {
  _toolBar = new QToolBar("ToolBar");
  addToolBar(_toolBar);
}

void MainWindow::createCentralWidget() {
  _imageLabel = new QLabel();
  setCentralWidget(_imageLabel);
}

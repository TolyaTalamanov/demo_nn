#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow() {
  readSettings();
  setFixedSize(QDesktopWidget().availableGeometry(this).size() * 0.8);
  setWindowTitle(tr("Demonstration neural networks"));
  createCentralWidget();
  createStatusBar();
  createActions();
}

MainWindow::~MainWindow() {

}

void MainWindow::createActions() {
  createFileActions();
  createEditActions();
  createHelpActions();
}

void MainWindow::open() { 
  QString imagePath = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath());
  if (!imagePath.isEmpty()) {
    _image.load(imagePath);
  }
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
  _imageLabel->show();
  emit setImage(true);
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
    emit setImage(true);
  }
}

void MainWindow::copy() {
  QApplication::clipboard()->setImage(_image, QClipboard::Clipboard);
}

void MainWindow::cut() {
  copy();
  _image = QImage();
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
  emit setImage(false);
}

void MainWindow::about() {
  QMessageBox::about(this, tr("About Application"),
      tr("The <b>Application</b> example demonstrates how to "
        "run neural networks"));
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
  QToolBar* fileToolBar = addToolBar(tr("File"));

  const QIcon openIcon = QIcon::fromTheme("open-image", QIcon("../icons/open.png"));
  QAction* actOpen = fileMenu->addAction(openIcon, tr("&Open"), this, &MainWindow::open);
  actOpen->setShortcut(QKeySequence::Open);
  actOpen->setStatusTip(tr("Open image"));
  fileMenu->addAction(actOpen);
  fileToolBar->addAction(actOpen);

  const QIcon saveIcon = QIcon::fromTheme("save-image", QIcon("../icons/save.png"));
  QAction* actSave = fileMenu->addAction(saveIcon, tr("&Save"), this, &MainWindow::save);
  actSave->setShortcut(QKeySequence::Save);
  actSave->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSave);

  QAction* actSaveAs = fileMenu->addAction(saveIcon, tr("&Save As..."), this, &MainWindow::saveAs);
  actSaveAs->setShortcut(QKeySequence::SaveAs);
  actSaveAs->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSaveAs);
  fileToolBar->addAction(actSaveAs);

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("exit-image", QIcon("../icons/exit.png"));
  QAction* actExit = fileMenu->addAction(exitIcon, tr("&Exit"), this, &QWidget::close);
  actExit->setShortcut(QKeySequence::Quit);
  actExit->setStatusTip(tr("Exit the application"));
  fileMenu->addAction(actExit);

}

void MainWindow::createEditActions() {
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
  QToolBar* editToolBar = addToolBar(tr("Edit"));

  const QIcon cutIcon = QIcon::fromTheme("cut-image", QIcon("../icons/cut.png"));
  QAction* actCut = editMenu->addAction(cutIcon, tr("&Cut"), this, &MainWindow::cut);
  actCut->setShortcut(QKeySequence::Cut);
  actCut->setStatusTip(tr("Cut image"));
  editMenu->addAction(actCut);
  editToolBar->addAction(actCut);
  actCut->setEnabled(false);
  connect(this, &MainWindow::setImage, actCut, &QAction::setEnabled);

  const QIcon copyIcon = QIcon::fromTheme("copy-image", QIcon("../icons/copy.png"));
  QAction* actCopy = editMenu->addAction(copyIcon, tr("&Copy"), this, &MainWindow::copy);
  actCopy->setShortcut(QKeySequence::Copy);
  actCopy->setStatusTip("Copy image");
  editMenu->addAction(actCopy);
  editToolBar->addAction(actCopy);
  actCopy->setEnabled(false);
  connect(this, &MainWindow::setImage, actCopy, &QAction::setEnabled);

  const QIcon pasteIcon = QIcon::fromTheme("paste-image", QIcon("../icons/paste.png"));
  QAction* actPaste = editMenu->addAction(pasteIcon, tr("&Paste"), this, &MainWindow::paste);
  actPaste->setShortcut(QKeySequence::Paste);
  editMenu->addAction(actPaste);
  editMenu->setStatusTip("Paste image");
  editToolBar->addAction(actPaste);
  
  menuBar()->addSeparator();

}

void MainWindow::createHelpActions() {
  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

  QAction* actAbout = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  actAbout->setStatusTip("Show the application's About box");

  QAction* actAboutQt = helpMenu->addAction(tr("&About Qt"), qApp, &QApplication::aboutQt);
  actAboutQt->setStatusTip("Show the Qt library's About box");

}

void MainWindow::createCentralWidget() {
  _imageLabel = new QLabel();
  setCentralWidget(_imageLabel);
}

void MainWindow::createStatusBar() {
  statusBar()->showMessage(tr("Ready"));
}

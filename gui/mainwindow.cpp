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
  QAction* actOpen = new QAction(openIcon, "image open action", 0);
  actOpen->setText("&Open...");
  actOpen->setShortcut(QKeySequence("CTRL+O"));
  fileMenu->addAction(actOpen);
  _toolBar->addAction(actOpen);
  connect(actOpen,   &QAction::triggered, this, &MainWindow::open);

  const QIcon saveIcon = QIcon::fromTheme("save-image", QIcon("../icons/save.png"));
  QAction* actSave = new QAction(saveIcon, "image save action", 0);
  actSave->setText("&Save");
  actSave->setShortcut(QKeySequence("CTRL+S"));
  fileMenu->addAction(actSave);
  connect(actSave,   &QAction::triggered, this, &MainWindow::save);

  QAction* actSaveAs = new QAction(saveIcon, "image save as action", 0);
  actSaveAs->setText("&Save As...");
  actSaveAs->setShortcut(QKeySequence("CTRL+SHIFT+S"));
  fileMenu->addAction(actSaveAs);
  connect(actSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
  _toolBar->addAction(actSaveAs);

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("exit-image", QIcon("../icons/exit.png"));
  QAction* actExit = fileMenu->addAction(exitIcon, tr("&Exit"), this, &QWidget::close);
  actExit->setText("&Exit...");
  actExit->setShortcut(QKeySequence::Quit);
  fileMenu->addAction(actExit);

}

void MainWindow::createEditActions() {
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit")); 

  const QIcon cutIcon = QIcon::fromTheme("cut-image", QIcon("../icons/cut.png"));
  QAction* actCut = new QAction(cutIcon, "image cut action", 0);
  actCut->setText("Cut");
  actCut->setShortcut(QKeySequence("CTRL+X"));
  //actCut->setEnabled(false);

  const QIcon copyIcon = QIcon::fromTheme("copy-image", QIcon("../icons/copy.png"));
  QAction* actCopy = new QAction(copyIcon, "image copy action", 0);
  actCopy->setText("Copy");
  actCopy->setShortcut(QKeySequence("CTRL+C"));
  //actCopy->setEnabled(false);

  const QIcon pasteIcon = QIcon::fromTheme("paste-image", QIcon("../icons/paste.png"));
  QAction* actPaste = new QAction(pasteIcon, "image paste action", 0);
  actPaste->setText("Paste");
  actPaste->setShortcut(QKeySequence("CTRL+V"));

  editMenu->addAction(actCut);
  editMenu->addAction(actCopy);
  editMenu->addAction(actPaste);

  connect(actPaste, &QAction::triggered, this, &MainWindow::paste);
  connect(actCopy,  &QAction::triggered, this, &MainWindow::copy);
  connect(actCut,   &QAction::triggered, this, &MainWindow::cut);

  _toolBar->addAction(actCut);
  _toolBar->addAction(actCopy);
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

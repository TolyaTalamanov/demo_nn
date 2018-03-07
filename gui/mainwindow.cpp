#include "mainwindow.h"

MainWindow::MainWindow() : _imageLabel(new QLabel) {
  setWindowTitle(tr("Demo_nn"));
  setCentralWidget(_imageLabel);
  createActions();

  _imageLabel->setPixmap(QPixmap::fromImage(_image));
  _imageLabel->show();
}

MainWindow::~MainWindow() {

}

void MainWindow::createActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit")); 

  QToolBar* toolBar = new QToolBar("ToolBar");
  addToolBar(toolBar);

  const QIcon openIcon = QIcon::fromTheme("open-image", QIcon("../icons/open.png"));
  QAction* actOpen = new QAction(openIcon, "image open action", 0);
  actOpen->setText("&Open...");
  actOpen->setShortcut(QKeySequence("CTRL+O"));

  const QIcon saveIcon = QIcon::fromTheme("save-image", QIcon("../icons/save.png"));
  QAction* actSave = new QAction(saveIcon, "image save action", 0);
  actSave->setText("&Save");
  actSave->setShortcut(QKeySequence("CTRL+S"));

  QAction* actSaveAs = new QAction(saveIcon, "image save as action", 0);
  actSaveAs->setText("&Save As...");
  actSaveAs->setShortcut(QKeySequence("CTRL+SHIFT+S"));

  fileMenu->addAction(actOpen);
  fileMenu->addAction(actSave);
  fileMenu->addAction(actSaveAs);

  connect(actOpen,   &QAction::triggered, this, &MainWindow::open);
  connect(actSave,   &QAction::triggered, this, &MainWindow::save);
  connect(actSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

  toolBar->addAction(actOpen);
  toolBar->addAction(actSaveAs);


  const QIcon cutIcon = QIcon::fromTheme("cut-image", QIcon("../icons/cut.png"));
  QAction* actCut = new QAction(cutIcon, "image cut action", 0);
  actCut->setText("Cut");
  actCut->setShortcut(QKeySequence("CTRL+X"));
  actCut->setEnabled(false);

  const QIcon copyIcon = QIcon::fromTheme("copy-image", QIcon("../icons/copy.png"));
  QAction* actCopy = new QAction(copyIcon, "image copy action", 0);
  actCopy->setText("Copy");
  actCopy->setShortcut(QKeySequence("CTRL+C"));
  actCopy->setEnabled(false);

  const QIcon pasteIcon = QIcon::fromTheme("paste-image", QIcon("../icons/paste.png"));
  QAction* actPaste = new QAction(pasteIcon, "image paste action", 0);
  actPaste->setText("Paste");
  actPaste->setShortcut(QKeySequence("CTRL+V"));

  editMenu->addAction(actCut);
  editMenu->addAction(actCopy);
  editMenu->addAction(actPaste);

  connect(actPaste, &QAction::triggered, this, &MainWindow::paste);

  toolBar->addAction(actCut);
  toolBar->addAction(actCopy);
  toolBar->addAction(actPaste);

  statusBar()->showMessage(tr("Ready"));
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


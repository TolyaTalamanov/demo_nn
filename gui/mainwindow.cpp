#include <string>
#include "mainwindow.hpp"
#include "detector.hpp"
#include "label_parser.hpp"
#include "bounding_box.hpp"

MainWindow::MainWindow() {
  readSettings();
  setFixedSize(QDesktopWidget().availableGeometry(this).size() * 0.92);
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
  createRunActions();
}

void MainWindow::open() {
  QString imagePath = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    QDir::currentPath());

  if (!imagePath.isEmpty()) {
    _image.load(imagePath);
    _imageLabel->setPixmap(QPixmap::fromImage(_image));
    _imageLabel->show();
    emit setImage(true);
  }
}

void MainWindow::save() {
  // TODO(TolyaTalamanov): save action
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
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());

  const QByteArray geometry = settings.value("geometry",
                                              QByteArray()).toByteArray();

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
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());

  settings.setValue("geometry", saveGeometry());
}

void MainWindow::createFileActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  QToolBar* fileToolBar = addToolBar(tr("File"));

  const QIcon openIcon = QIcon::fromTheme("open-image",
                                           QIcon("../icons/open.png"));
  QAction* actOpen = fileMenu->addAction(openIcon, tr("&Open"),
                                                   this, &MainWindow::open);
  actOpen->setShortcut(QKeySequence::Open);
  actOpen->setStatusTip(tr("Open image"));
  fileMenu->addAction(actOpen);
  fileToolBar->addAction(actOpen);

  const QIcon saveIcon = QIcon::fromTheme("save-image",
                                           QIcon("../icons/save.png"));
  QAction* actSave = fileMenu->addAction(saveIcon, tr("&Save"),
                                         this, &MainWindow::save);

  actSave->setShortcut(QKeySequence::Save);
  actSave->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSave);

  QAction* actSaveAs = fileMenu->addAction(saveIcon, tr("&Save As..."),
                                           this, &MainWindow::saveAs);
  actSaveAs->setShortcut(QKeySequence::SaveAs);
  actSaveAs->setStatusTip(tr("Save image"));
  fileMenu->addAction(actSaveAs);
  fileToolBar->addAction(actSaveAs);

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("exit-image",
                                          QIcon("../icons/exit.png"));
  QAction* actExit = fileMenu->addAction(exitIcon, tr("&Exit"),
                                         this, &QWidget::close);

  actExit->setShortcut(QKeySequence::Quit);
  actExit->setStatusTip(tr("Exit the application"));
  fileMenu->addAction(actExit);
}

void MainWindow::createEditActions() {
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
  QToolBar* editToolBar = addToolBar(tr("Edit"));

  const QIcon cutIcon = QIcon::fromTheme("cut-image",
                                         QIcon("../icons/cut.png"));
  QAction* actCut = editMenu->addAction(cutIcon, tr("&Cut"),
                                        this, &MainWindow::cut);
  actCut->setShortcut(QKeySequence::Cut);
  actCut->setStatusTip(tr("Cut image"));
  editMenu->addAction(actCut);
  editToolBar->addAction(actCut);
  actCut->setEnabled(false);
  connect(this, &MainWindow::setImage, actCut, &QAction::setEnabled);

  const QIcon copyIcon = QIcon::fromTheme("copy-image",
                                          QIcon("../icons/copy.png"));
  QAction* actCopy = editMenu->addAction(copyIcon, tr("&Copy"),
                                           this, &MainWindow::copy);

  actCopy->setShortcut(QKeySequence::Copy);
  actCopy->setStatusTip("Copy image");
  editMenu->addAction(actCopy);
  editToolBar->addAction(actCopy);
  actCopy->setEnabled(false);
  connect(this, &MainWindow::setImage, actCopy, &QAction::setEnabled);

  const QIcon pasteIcon = QIcon::fromTheme("paste-image",
                                            QIcon("../icons/paste.png"));
  QAction* actPaste = editMenu->addAction(pasteIcon, tr("&Paste"),
                                            this, &MainWindow::paste);

  actPaste->setShortcut(QKeySequence::Paste);
  editMenu->addAction(actPaste);
  editMenu->setStatusTip("Paste image");
  editToolBar->addAction(actPaste);

  menuBar()->addSeparator();
}

void MainWindow::createHelpActions() {
  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction* actAbout = helpMenu->addAction(tr("&About"), this,
                                           &MainWindow::about);
  actAbout->setStatusTip("Show the application's About box");
  QAction* actAboutQt = helpMenu->addAction(tr("&About Qt"),
                                             qApp, &QApplication::aboutQt);
  actAboutQt->setStatusTip("Show the Qt library's About box");
}

void MainWindow::createRunActions() {
  QToolBar* runToolBar = addToolBar(tr("Run"));

  QWidget* spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  runToolBar->addWidget(spacer);

  QComboBox* netSelectionBox = new QComboBox();
  QStringList netNamed;
  netNamed << "ssd" << "yolo";
  netSelectionBox->addItems(netNamed);
  runToolBar->addWidget(netSelectionBox);

  const QIcon runIcon = QIcon::fromTheme("run", QIcon("../icons/run.png"));
  QPushButton* runButton = new QPushButton();
  connect(runButton, &QPushButton::clicked, this, &MainWindow::detect);
  runButton->setIcon(runIcon);
  runToolBar->addWidget(runButton);
}

void MainWindow::createCentralWidget() {
  _imageLabel = new QLabel();
  _imageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  _imageLabel->setStyleSheet("QLabel {background-color : gray;}");
  QScrollArea* scrollArea = new QScrollArea();
  scrollArea->setWidget(_imageLabel);
  scrollArea->setWidgetResizable(true);
  setCentralWidget(scrollArea);
}

void MainWindow::createStatusBar() {
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::detect() {
  const string& model_file  = "../models/SSD_300x300/deploy.prototxt";
  const string& weight_file =
  "../models/SSD_300x300/VGG_VOC0712_SSD_300x300_iter_120000.caffemodel";

  const string& mean_file    = "";
  const string& mean_value   = "104,117,123";
  const double conf_treshold = 0.5;

  int x1, y1, x2, y2;

  LabelParser labels("../models/SSD_300x300/labelmap_voc.prototxt");

  Detector detector(model_file, weight_file, mean_file, mean_value);
  auto detections = detector.Detect(_image.width(), _image.height(),
                                    _image.bits(),  _image.bytesPerLine());

  QVector<QColor> colors;
  colors.push_back(Qt::green);
  colors.push_back(Qt::blue);
  colors.push_back(Qt::cyan);
  colors.push_back(Qt::magenta);
  colors.push_back(Qt::yellow);
  colors.push_back(Qt::red);

  for (const auto& d : detections) {
    if (d[2] > conf_treshold) {
      x1 = static_cast<int>(d[3] * _image.width());
      y1 = static_cast<int>(d[4] * _image.height());
      x2 = static_cast<int>(d[5] * _image.width());
      y2 = static_cast<int>(d[6] * _image.height());

      QRect rect(QPoint(x1, y1), QPoint(x2, y2));
      int score = d[2] * 100;
      QString label = QString::fromStdString(labels.getLabelById(d[1])) +
                      QString(" ") + QString::number(score) + QString("%");

      QColor label_color = colors[static_cast<int>(d[1]) % colors.size()];
      QBoundingBox bounding_box(rect, label_color, label);
      bounding_box.draw(_image);
    }
  }
  _imageLabel->setPixmap(QPixmap::fromImage(_image));
}

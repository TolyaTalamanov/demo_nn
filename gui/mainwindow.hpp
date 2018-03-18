#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

#include <QtWidgets>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

 signals:
  void setImage(bool is_set);

 protected:
  void createActions();

 private slots:
  void open();
  void save();
  void saveAs();
  void paste();
  void copy();
  void cut();
  void about();

 private:
  void readSettings();
  void writeSettings();

  void createFileActions();
  void createEditActions();
  void createHelpActions();
  void createRunActions();

  void createStatusBar();
  void createCentralWidget();

 private:
  QImage    _image;
  QLabel*   _imageLabel;
};

#endif  // GUI_MAINWINDOW_H_

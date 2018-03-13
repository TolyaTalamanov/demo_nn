#ifndef DEMO_NN_GUI_MAINWINDOW_H
#define DEMO_NN_GUI_MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  MainWindow(const MainWindow& other) {

  }
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
Q_DECLARE_METATYPE(MainWindow)
#endif //DEMO_NN_GUI_MAINWINDOW_H

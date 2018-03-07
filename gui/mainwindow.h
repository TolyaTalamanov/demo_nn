#ifndef DEMO_NN_GUI_MAINWINDOW_H
#define DEMO_NN_GUI_MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

protected:
  void createActions();

private:
  void open();
  void save();
  void saveAs();
  void paste();

private:
  QImage  _image;
  QLabel* _imageLabel;

};
#endif //DEMO_NN_GUI_MAINWINDOW_H

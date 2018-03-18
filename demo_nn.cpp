#include <QApplication>
#include "gui/mainwindow.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  MainWindow* mainWindow = new MainWindow;
  mainWindow->show();
  return app.exec();
}

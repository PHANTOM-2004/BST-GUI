#ifndef BSTMAINWINDOW_HPP
#define BSTMAINWINDOW_HPP

#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QScrollArea>

class BstMainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit BstMainWindow(QWidget *parent = nullptr);

private:
  QAction *softwareInfoAction;
  QAction *buildInfoAction;
  QMessageBox *buildInfo;
  QMessageBox *softwareInfo;
  
  void initMenuBar();
  void initBuildInfo();
  void initSoftwareInfo();
  void showSoftwareInfo();
  void showBuildInfo();

signals:
};

#endif // BSTMAINWINDOW_HPP

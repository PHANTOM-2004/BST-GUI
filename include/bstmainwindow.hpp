/// \file
/// \brief definition of BstMainWindow


#ifndef BSTMAINWINDOW_HPP
#define BSTMAINWINDOW_HPP

#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QScrollArea>

/// \brief the mainwindow of the application
class BstMainWindow : public QMainWindow {
  Q_OBJECT
public:
  /// \brief construcr the menu bar, status bar, mainwidget
  explicit BstMainWindow(QWidget *parent = nullptr);

private:
  /// \brief action when clicked the software information in menu
  QAction *softwareInfoAction;
  /// \brief action when clicked the build information in menu
  QAction *buildInfoAction;
  /// \brief messagebox to show for build information
  QMessageBox *buildInfo;
  /// \brief messagebox to show for software information
  QMessageBox *softwareInfo;
 
  /// \brief initialize the memu bar, call once in constructor
  void initMenuBar();
  /// \brief initialize the build information in menu
  void initBuildInfo();
  /// \brief initialize the software information in menu
  void initSoftwareInfo();
  /// \brief show the software information when clicked
  void showSoftwareInfo();
  /// \brief show the build information when clicked
  void showBuildInfo();

signals:
};

#endif // BSTMAINWINDOW_HPP

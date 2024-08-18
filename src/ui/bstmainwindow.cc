/* \file bstmainwindow.cc
/ \brief implementation of BstMainWindow
*/

#include "bstmainwindow.hpp"
#include "common.hpp"
#include "mainwidget.hpp"
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qnamespace.h>

BstMainWindow::BstMainWindow(QWidget *parent) : QMainWindow{parent} {
  // set window title, window size
  setWindowTitle(tr("BST Visualization"));
  resize(common::MW_W, common::MW_H);

  /*---------------------------------------------------------------------------*/
  // menuBar
  initMenuBar();
  /*---------------------------------------------------------------------------*/
  auto centralwidget = new MainWidget(this);
  setCentralWidget(centralwidget);
  /*---------------------------------------------------------------------------*/
  statusBar();
}

void BstMainWindow::initCmpInfo() {
  static QString const help_content =
#include "help.html"
      ;

  cmpInfo = new QMessageBox(this);
  cmpInfo->setWindowTitle(tr("About String Comparison"));
  cmpInfo->setTextFormat(Qt ::RichText);
  cmpInfo->setText(help_content);

  cmpInfoAction = new QAction(tr("How is String Compared"), this);
  cmpInfoAction->setStatusTip(tr("About String Comparison"));
  connect(cmpInfoAction, &QAction::triggered, this,
          &BstMainWindow::showCmpInfo);
}

void BstMainWindow::initBuildInfo() {
  static QString const newline = "<br>";
  static QString const buildInfoTextFmt =
#include "build.html"
      ;

  static QString const compiler_info =
      QString(COMPILER_VERION).replace("\n", newline);
  static QString const generator_info =
      QString(GENERATOR).replace("\n", newline);
  static QString const cmake_version = QString(CMAKE_VERSION);
  static QString const qt_version = QString(QT6_VERSION);

  buildInfo = new QMessageBox(this);
  buildInfo->setWindowTitle(tr("Build Information"));
  buildInfo->setTextFormat(Qt::RichText); // show as html
  buildInfo->setText(buildInfoTextFmt.arg(compiler_info, generator_info,
                                          cmake_version, qt_version));

  buildInfoAction = new QAction(tr("build information"), this);
  buildInfoAction->setStatusTip("Building environment");
  connect(buildInfoAction, &QAction::triggered, this,
          &BstMainWindow::showBuildInfo);
}

void BstMainWindow::initSoftwareInfo() {
  static QString const softwareInfoText =
#include "profile.html"
      ;

  softwareInfo = new QMessageBox(this);
  softwareInfo->setWindowTitle(tr("Software Information"));
  softwareInfo->setTextFormat(Qt::RichText); // show as html
  softwareInfo->setText(softwareInfoText);

  softwareInfoAction = new QAction(tr("software information"), this);
  softwareInfoAction->setStatusTip(
      tr("About this software")); // when mouse hover on action
  connect(softwareInfoAction, &QAction::triggered, this,
          &BstMainWindow::showSoftwareInfo);
}

void BstMainWindow::initMenuBar() {
  // software info
  initSoftwareInfo();
  // set build info
  initBuildInfo();
  // set string cmp info
  initCmpInfo();

  QMenu *about = menuBar()->addMenu(tr("About"));
  about->addAction(softwareInfoAction);
  about->addAction(buildInfoAction);

  QMenu *help = menuBar()->addMenu(tr("Help"));
  help->addAction(cmpInfoAction);
}

void BstMainWindow::showSoftwareInfo() {
  qDebug() << "Show Software";
  softwareInfo->show();
}

void BstMainWindow::showCmpInfo() {
  qDebug() << "Show string comparison";
  cmpInfo->show();
}

void BstMainWindow::showBuildInfo() {
  qDebug() << "Show Build information";
  qDebug() << COMPILER_VERION;
  qDebug() << GENERATOR;
  qDebug() << CMAKE_VERSION;
  /*
  static QString const info =
      tr("C++ Compiler:\n") + tr(COMPILER_VERION) + "\n\n" + tr("Generator: ")
  + tr(GENERATOR) + "\n\n" + tr("CMake Version: ") + tr(CMAKE_VERSION);
  QMessageBox::information(this, tr("Build Information"), info);
  */
  buildInfo->show();
}

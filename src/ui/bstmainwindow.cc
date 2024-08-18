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
  static QString const help_content = R"(
    <h2>We compare the sring as below</h2>
    <p>
    When the length of s1 is not equal to s2, 
    <strong><i>the one with shorter length is smaller. </i></strong>
    When the length of s1 is equal to s2, 
    <strong><i>s1 and s2 are compared in dictionary order.</i></strong> 
    </p>
    <h2>Example</h2>
    <i>
    "a"   is <strong>smaller</strong> than "b"<br>
    "aaa" is s<strong>maller than </strong>"123333"<br>
    "288" is <strong>smaller than </strong>"123333"<br>
    ""    is <strong>NOT smaller than </strong>""<br>
    </i>
  )";

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
  static QString const buildInfoTextFmt = R"(  
<div>  
    <strong>Compiler Information:</strong><br>  
    <i>%1</i><br>  
    <br>
    <strong>Generator:</strong><br>  
    <i>%2</i><br>  
    <br>
    <strong>CMake Version:</strong><br>  
    <i>%3</i><br>
    <br>
    <strong>Qt Version:</strong><br>  
    <i>%4</i> 
</div>  
)";
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
  static QString const softwareInfoText = R"(
    <div>
    <strong>Author</strong><br>
    YT Chen, Tongji University<br>
    Profile: <a href="https://github.com/PHANTOM-2004">My Github Profile</a><br>
    <br>
    <strong>Git Repo</strong><br>
    <a href="https://github.com/PHANTOM-2004/BST-GUI">GitHub</a>. 
    If you like it please give me a star
    </div>
  )";

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

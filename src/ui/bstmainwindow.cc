#include "bstmainwindow.hpp"
#include "common.hpp"
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

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
    <i>%3</i> 
</div>  
)";
  static QString const compiler_info =
      QString(COMPILER_VERION).replace("\n", newline);
  static QString const generator_info =
      QString(GENERATOR).replace("\n", newline);
  static QString const cmake_version = QString(CMAKE_VERSION);

  static bool called = false;
  Q_ASSERT(called == false); // only call once
  if (called)
    return;
  called = true;

  buildInfo = new QMessageBox(this);
  buildInfo->setWindowTitle(tr("Build Information"));
  buildInfo->setTextFormat(Qt::RichText); // show as html
  buildInfo->setText(
      buildInfoTextFmt.arg(compiler_info, generator_info, cmake_version));
}

void BstMainWindow::initSoftwareInfo() {
  static QString const softwareInfoText = R"(
    <div>
    <strong>Author</strong><br>
    YT Chen, Tongji University<br>
    <br>
    <strong>Git Repo</strong><br>
    <a href="https://github.com/PHANTOM-2004/my-ics-pa">GitHub</a>. 
    If you like it please give me a star
    </div>
  )";

  static bool called = false;
  Q_ASSERT(called == false); // only call once
  if (called)
    return;
  called = true;

  softwareInfo = new QMessageBox(this);
  softwareInfo->setWindowTitle(tr("Software Information"));
  softwareInfo->setTextFormat(Qt::RichText); // show as html
  softwareInfo->setText(softwareInfoText);
}

BstMainWindow::BstMainWindow(QWidget *parent) : QMainWindow{parent} {
  // set window title, window size
  setWindowTitle(tr("BST Visualization"));
  resize(common::MW_W, common::MW_H);

  /*---------------------------------------------------------------------------*/
  // set up the action for showing software information
  // software info
  initSoftwareInfo();
  auto softwareInfoAction = new QAction(tr("software information"), this);
  softwareInfoAction->setStatusTip(
      tr("About this software")); // when mouse hover on action
  connect(softwareInfoAction, &QAction::triggered, this,
          &BstMainWindow::showSoftwareInfo);

  // set build info
  initBuildInfo();
  auto buildInfoAction = new QAction(tr("build information"), this);
  buildInfoAction->setStatusTip("Building environment");
  connect(buildInfoAction, &QAction::triggered, this,
          &BstMainWindow::showBuildInfo);

  /*---------------------------------------------------------------------------*/
  // menuBar
  QMenu *about = menuBar()->addMenu(tr("About"));
  about->addAction(softwareInfoAction);
  about->addAction(buildInfoAction);

  /*---------------------------------------------------------------------------*/
  // set scroll area size
  scrollArea = new QScrollArea(this);
  scrollArea->resize(common::SA_W, common::SA_H);

  /*---------------------------------------------------------------------------*/
  // set render area
  renderArea = new RenderArea(this);

  /*---------------------------------------------------------------------------*/
  // set child widget
  scrollArea->setWidget(renderArea);

  scrollArea->setWidgetResizable(false);
  scrollArea->horizontalScrollBar();
  scrollArea->verticalScrollBar();

  /*---------------------------------------------------------------------------*/

  /*---------------------------------------------------------------------------*/
  // add centralwidget
  centralwidget = new QWidget(this);
  centralwidget->setObjectName("centralwidget");
  centralwidget->resize(common::MW_W, common::MW_H);

  QVBoxLayout *layout = new QVBoxLayout(centralwidget);
  layout->addWidget(scrollArea);

  centralwidget->setLayout(layout);

  /*---------------------------------------------------------------------------*/
  setCentralWidget(centralwidget);

  /*---------------------------------------------------------------------------*/
  statusBar();
}

void BstMainWindow::showSoftwareInfo() {
  qDebug() << "Show Software";
  softwareInfo->show();
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

#include "bstmainwindow.hpp"
#include "common.hpp"
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <qaction.h>
#include <qdebug.h>

BstMainWindow::BstMainWindow(QWidget *parent) : QMainWindow{parent} {
  // set window title, window size
  setWindowTitle(tr("BST Visualization"));
  resize(common::MW_W, common::MW_H);

  /*---------------------------------------------------------------------------*/
  // set up the action for showing software information
  // software info
  auto softwareInfoAction = new QAction(tr("software information"), this);
  softwareInfoAction->setStatusTip(
      tr("About this software")); // when mouse hover on action
  connect(softwareInfoAction, &QAction::triggered, this,
          &BstMainWindow::showSoftwareInfo);

  // show build info
  auto buildInfoAction = new QAction(tr("build information"), this);
  buildInfoAction->setStatusTip("Build environment");
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
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(scrollArea);

  /*---------------------------------------------------------------------------*/
  // add centralwidget
  centralwidget = new QWidget(this);
  centralwidget->setObjectName("centralwidget");
  centralwidget->resize(common::MW_W, common::MW_H);
  centralwidget->setLayout(layout);

  /*---------------------------------------------------------------------------*/
  setCentralWidget(centralwidget);
}

void BstMainWindow::showSoftwareInfo() { qDebug() << "Show Software"; }

void BstMainWindow::showBuildInfo() {
  qDebug() << "Show Build information";
  qDebug() << COMPILER_VERION;
  qDebug() << GENERATOR;
  qDebug() << CMAKE_VERSION;
}

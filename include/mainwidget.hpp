/*! \file 
 *  \brief definition of MainWidget
 */
#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "renderarea.hpp"
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>

/// \brief serve as the centralWidget for BstMainWindow
class MainWidget : public QWidget {
  Q_OBJECT
public:
  /*!
  \fn MainWidget::MainWidget(QWidget *parent) : QWidget{parent}
  \brief construct the main widget as central widget for main window

  there are:
  1. scrollArea, containging the renderArea
  2. insert/find/delete button and edit line

  \param parent the parent of the widget
 */
  explicit MainWidget(QWidget *parent = nullptr);

private:
  /// \brief pointer to scroll area
  QScrollArea *scrollArea;
  /// \brief pointer to render area
  RenderArea *renderArea;
  /// \brief pointer to insert input
  QLineEdit *insertInput;
  /// \brief pointer to delete input
  QLineEdit *deleteInput;
  /// \brief pointer to find input
  QLineEdit *findInput;

  /// \brief pointer to insert button
  QPushButton *insertButton;
  /// \brief pointer to delete button
  QPushButton *deleteButton;
  /// \brief pointer to find button
  QPushButton *findButton;

  /// \brief used in constructor to Initialize the scrollArea
  void initScrollArea();

  /// \brief used in constructor to Initialize the renderArea
  void initRenderArea();

  /// \brief do insertion when insert Button is clicked
  void on_insert_button_clicked();

  /// \brief do deletion when delete Button is clicked
  void on_delete_button_clicked();

  /// \brief do deletion when find Button is clicked
  void on_find_button_clicked();

signals:
};

#endif // MAINWIDGET_HPP

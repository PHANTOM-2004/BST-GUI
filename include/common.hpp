/// \file
/// \brief some constant for global usage
///
#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include <qnamespace.h>
namespace common {
/// \brief the size of mainwindow
enum MAINWINDOW {
  MW_W = 800,
  MW_H = 600,
};

/// \brief the size of render area
enum RENDERAREA {
  RA_W = 2000,
  RA_H = 2000,
};

/// \brief the size of scroll area
enum SCROLLAREA {
  SA_W = MW_W - 10,
  SA_H = MW_H * 4 / 5,
};

/// \brief the shape of node to render
enum {
  FONT_SIZE = 13, // pt
  LINE_WIDTH = 3,
  MAX_INPUT_LEN = 10,
  NODE_RADIUS = 40,
  NODE_H_INTERVAL = 10,
  NODE_V_INTERVAL = 15,
};

enum {
  WAITING_TIME = 1000, // s
};

}; // namespace common
#endif

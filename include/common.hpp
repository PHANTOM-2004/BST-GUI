/// \file
/// \brief some constant for global usage
///
#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__
namespace common {
enum MAINWINDOW {
  MW_W = 800,
  MW_H = 600,
};

enum RENDERAREA {
  RA_W = 1000,
  RA_H = 1000,
};

enum SCROLLAREA {
  SA_W = MW_W - 10,
  SA_H = MW_H * 4 / 5,
};

}; // namespace common
#endif


#include "qbst/QBST.hpp"

using qbst::QBST;
using qbst::QBST_data;
using qbst::QBST_node;


QBST_node *&QBST::search(QBST_data const &val) {
  // TODO:
  QBST_node *&res = QBST_base::search(val);

  // we need to high light the one that is hit

  return res;
}

QBST_node *QBST::insert(QBST_data const &val) {
  // TODO:
  return QBST_base::insert(val);
}

bool QBST::erase(QBST_data const &val) {
  // TODO:
  return QBST_base::erase(val);
}

#ifndef MIC_H
#define MIC_H

#include <InastempStaticConfig.h>
#include <cfloat>
#include <iostream>

#include "arrayview.h"
#include "vector_helper.h"

struct mic {
  template <typename VecType, typename T>
  std::tuple<VecType, VecType, VecType, VecType>
  operator()(const VecType &x1, const VecType &y1, const VecType &z1,
             const VecType &x2, const VecType &y2, const VecType &z2,
             const std::vector<T> & /*box_a*/, const std::vector<T> & /*box_b*/,
             const std::vector<T> & /*box_c*/) {
    // auto rij = rj - ri;
    auto x12 = x2 - x1;
    auto y12 = y2 - y1;
    auto z12 = z2 - z1;

    auto mindist2 = (x12 * x12) + (y12 * y12) + (z12 * z12);
    return {mindist2, x12, y12, z12};
  }
};

#endif // MIC_H

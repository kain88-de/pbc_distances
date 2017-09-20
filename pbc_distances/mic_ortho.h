#ifndef MIC_ORTHO_H
#define MIC_ORTHO_H

#include <InastempStaticConfig.h>
#include <cfloat>
#include <iostream>

#include "arrayview.h"
#include "vector_helper.h"

struct mic_ortho {
  template <typename VecType, typename T>
  std::tuple<VecType, VecType, VecType, VecType>
  operator()(const VecType &x1, const VecType &y1, const VecType &z1,
             const VecType &x2, const VecType &y2, const VecType &z2,
             const std::vector<T> &box_a, const std::vector<T> &box_b,
             const std::vector<T> &box_c) {
    // auto rij = rj - ri;
    auto x12 = x2 - x1;
    auto y12 = y2 - y1;
    auto z12 = z2 - z1;

    // // rij = rij - box_c * std::round(rij[2] / box_c[2]);
    x12 = x12 - box_c[0] * ina_round(VecType(z12 / box_c[2]));
    y12 = y12 - box_c[1] * ina_round(VecType(z12 / box_c[2]));
    z12 = z12 - box_c[2] * ina_round(VecType(z12 / box_c[2]));

    // rij = rij - box_b * std::round(rij[1] / box_b[1]);
    x12 = x12 - box_b[0] * ina_round(VecType(y12 / box_b[1]));
    y12 = y12 - box_b[1] * ina_round(VecType(y12 / box_b[1]));

    // rij = rij - box_a * std::round(rij[0] / box_a[0]);
    x12 = x12 - box_a[0] * ina_round(VecType(x12 / box_a[0]));

    // search in images for minimal distance
    auto mindist2 = (x12 * x12) + (y12 * y12) + (z12 * z12);
    return {mindist2, x12, y12, z12};
  }
};

#endif // MIC_ORTHO

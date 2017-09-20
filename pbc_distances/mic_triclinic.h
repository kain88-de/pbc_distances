#ifndef MIC_TRICLINIC_H
#define MIC_TRICLINIC_H

#include <cfloat>
#include <iostream>

#include "arrayview.h"
#include "inastemp_helper.h"
#include "vector_helper.h"

struct mic_triclinic {
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
    auto mindist2 = VecType(FLT_MAX);
    VecType dx;
    VecType dy;
    VecType dz;
    for (auto x = -1; x < 2; ++x) {
      // const auto ra = rij + box_a * static_cast<double>(x);
      const auto x_ra = x12 + box_a[0] * static_cast<T>(x);
      const auto y_ra = y12;
      const auto z_ra = z12;
      for (auto y = -1; y < 2; ++y) {
        // auto rb = ra + box_b * static_cast<T>(y);
        const auto x_rb = x_ra + box_b[0] * static_cast<T>(y);
        const auto y_rb = y_ra + box_b[1] * static_cast<T>(y);
        const auto z_rb = z_ra;
        for (auto z = -1; z < 2; ++z) {
          // const auto rc = rb + box_c * static_cast<T>(z);
          const auto x_rc = x_rb + box_c[0] * static_cast<T>(z);
          const auto y_rc = y_rb + box_c[1] * static_cast<T>(z);
          const auto z_rc = z_rb + box_c[2] * static_cast<T>(z);

          // choose smallest distance
          const auto dist2 = (x_rc * x_rc) + (y_rc * y_rc) + (z_rc * z_rc);
          dx = VecType::IfElse(dist2 < mindist2, dx, x_rc);
          dy = VecType::IfElse(dist2 < mindist2, dy, y_rc);
          dz = VecType::IfElse(dist2 < mindist2, dz, z_rc);
          mindist2 = VecType::IfElse(dist2 < mindist2, dist2, mindist2);
        }
      }
    }
    return {mindist2, dx, dy, dz};
  }
};


#endif // MIC_TRICLINIC_H

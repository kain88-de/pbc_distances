///////////////////////////////////////////////////////////////////
// pbc_distances - Max Linke - 2017                              //
// Under MIT Licence, please you must read the LICENCE.txt file. //
///////////////////////////////////////////////////////////////////
#ifndef ANGLE_H
#define ANGLE_H

#include "mic.h"
#include "mic_ortho.h"
#include "mic_triclinic.h"

template <typename VecType, typename T, typename pbc_func>
void __angle(const T *a, const T *b, const T *c, const int n, const T *box,
             T *out) {

  const std::vector<T> box_a{{box[0], box[3], box[6]}};
  const std::vector<T> box_b{{box[1], box[4], box[7]}};
  const std::vector<T> box_c{{box[2], box[5], box[8]}};

  const ArrayView<T> a_view(n, 3, a);
  const ArrayView<T> b_view(n, 3, b);
  const ArrayView<T> c_view(n, 3, c);

  const auto last_n = n - (n % VecType::VecLength);

  for (auto i = 0; i < last_n; ++i) {
    const VecType x1 = a_view(i, 0);
    const VecType y1 = a_view(i, 1);
    const VecType z1 = a_view(i, 2);

    const VecType x2 = b_view(i, 0);
    const VecType y2 = b_view(i, 1);
    const VecType z2 = b_view(i, 2);

    const auto res_12 = pbc_func()(x1, y1, z1, x2, y2, z2, box_a, box_b, box_c);
    const auto x12 = std::get<1>(res_12);
    const auto y12 = std::get<2>(res_12);
    const auto z12 = std::get<3>(res_12);

    const VecType x3 = c_view(i, 0);
    const VecType y3 = c_view(i, 1);
    const VecType z3 = c_view(i, 2);

    const auto res_32 = pbc_func()(x3, y3, z3, x2, y2, z2, box_a, box_b, box_c);
    const auto x32 = std::get<1>(res_32);
    const auto y32 = std::get<2>(res_32);
    const auto z32 = std::get<3>(res_32);

    const auto x = x12 * x32 + y12 * y32 + z12 * z32;

    const auto xp_x = y12 * z32 - z12 * y32;
    const auto xp_y = -x12 * z32 + z12 * x32;
    const auto xp_z = x12 * y32 - y12 * x32;

    const auto y = (xp_x * xp_x + xp_y * xp_y + xp_z * xp_z).sqrt();

    const auto angles = atan2(y, x);
    angles.storeInArray(&out[i]);
  }

  // Remainder Loop
  for (auto i = last_n; i < n; ++i) {
    const InaVecSCALAR<T> x1 = a_view(i, 0);
    const InaVecSCALAR<T> y1 = a_view(i, 1);
    const InaVecSCALAR<T> z1 = a_view(i, 2);

    const InaVecSCALAR<T> x2 = b_view(i, 0);
    const InaVecSCALAR<T> y2 = b_view(i, 1);
    const InaVecSCALAR<T> z2 = b_view(i, 2);

    const auto res_12 = pbc_func()(x1, y1, z1, x2, y2, z2, box_a, box_b, box_c);
    const auto x12 = std::get<1>(res_12);
    const auto y12 = std::get<2>(res_12);
    const auto z12 = std::get<3>(res_12);

    const InaVecSCALAR<T> x3 = c_view(i, 0);
    const InaVecSCALAR<T> y3 = c_view(i, 1);
    const InaVecSCALAR<T> z3 = c_view(i, 2);

    const auto res_23 = pbc_func()(x3, y3, z3, x2, y2, z2, box_a, box_b, box_c);
    const auto x32 = std::get<1>(res_32);
    const auto y32 = std::get<2>(res_32);
    const auto z32 = std::get<3>(res_32);

    const auto x = x12 * x32 + y12 * y32 + z12 * z32;

    const auto xp_x = y12 * z32 - z12 * y32;
    const auto xp_y = -x12 * z32 + z12 * x32;
    const auto xp_z = x12 * y32 - y12 * x32;

    const auto y = (xp_x * xp_x + xp_y * xp_y + xp_z * xp_z).sqrt();

    const auto angle = atan2(y, x).getVec();
    out[i] = angle;
  }
}

template <typename T>
void _angle_triclinic(const T *a, const T *b, const T *c, const int n,
                      const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __angle<VecType, T, mic_triclinic>(a, b, c, n, box, out);
}

template <typename T>
void _angle_triclinic_scaler(const T *a, const T *b, const T *c, const int n,
                             const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __angle<VecType, T, mic_triclinic>(a, b, c, n, box, out);
}

template <typename T>
void _angle_ortho(const T *a, const T *b, const T *c, const int n, const T *box,
                  T *out) {
  using VecType = InaVecBestType<T>;
  __angle<VecType, T, mic_ortho>(a, b, c, n, box, out);
}

template <typename T>
void _angle_ortho_scaler(const T *a, const T *b, const T *c, const int n,
                         const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __angle<VecType, T, mic_ortho>(a, b, c, n, box, out);
}

template <typename T>
void _angle(const T *a, const T *b, const T *c, const int n, const T *box,
            T *out) {
  using VecType = InaVecBestType<T>;
  __angle<VecType, T, mic>(a, b, c, n, box, out);
}

template <typename T>
void _angle_ortho(const T *a, const T *b, const T *c, const int n, const T *box,
                  T *out) {
  using VecType = InaVecSCALAR<T>;
  __angle<VecType, T, mic>(a, b, c, n, box, out);
}

#endif // ANGLE_H

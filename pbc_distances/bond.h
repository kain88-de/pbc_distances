///////////////////////////////////////////////////////////////////
// pbc_distances - Max Linke - 2017                              //
// Under MIT Licence, please you must read the LICENCE.txt file. //
///////////////////////////////////////////////////////////////////
#ifndef BOND_H
#define BOND_H

#include "mic.h"
#include "mic_ortho.h"
#include "mic_triclinic.h"

template <typename VecType, typename T, typename pbc_func>
void __bond(const T *a, const T *b, const int n, const T *box, T *out) {

  const std::vector<T> box_a{{box[0], box[3], box[6]}};
  const std::vector<T> box_b{{box[1], box[4], box[7]}};
  const std::vector<T> box_c{{box[2], box[5], box[8]}};

  const ArrayView<T> a_view(n, 3, a);
  const ArrayView<T> b_view(n, 3, b);

  const auto last_n = n - (n % VecType::VecLength);

  for (auto i = 0; i < last_n; ++i) {
    const VecType x1 = a_view(i, 0);
    const VecType y1 = a_view(i, 1);
    const VecType z1 = a_view(i, 2);

    const VecType x2 = b_view(i, 0);
    const VecType y2 = b_view(i, 1);
    const VecType z2 = b_view(i, 2);
    const auto res = pbc_func()(x1, y1, z1, x2, y2, z2, box_a, box_b, box_c);
    const auto mindist2 = std::get<0>(res);
    mindist2.storeInArray(&out[i]);
  }

  // Remainder Loop
  for (auto i = last_n; i < n; ++i) {
    const InaVecSCALAR<T> x1 = a_view(i, 0);
    const InaVecSCALAR<T> y1 = a_view(i, 1);
    const InaVecSCALAR<T> z1 = a_view(i, 2);

    const InaVecSCALAR<T> x2 = b_view(i, 0);
    const InaVecSCALAR<T> y2 = b_view(i, 1);
    const InaVecSCALAR<T> z2 = b_view(i, 2);
    const auto res = pbc_func()(x1, y1, z1, x2, y2, z2, box_a, box_b, box_c);
    const auto mindist2 = std::get<0>(res).getVec();

    out[i] = mindist2;
  }
}

template <typename T>
void _bond_triclinic(const T *a, const T *b, const int n, const T *box,
                     T *out) {
  using VecType = InaVecBestType<T>;
  __bond<VecType, T, mic_triclinic>(a, b, n, box, out);
}

template <typename T>
void _bond_triclinic_scaler(const T *a, const T *b, const int n, const T *box,
                            T *out) {
  using VecType = InaVecSCALAR<T>;
  __bond<VecType, T, mic_triclinic>(a, b, n, box, out);
}

template <typename T>
void _bond_ortho(const T *a, const T *b, const int n, const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __bond<VecType, T, mic_ortho>(a, b, n, box, out);
}

template <typename T>
void _bond_ortho_scaler(const T *a, const T *b, const int n, const T *box,
                        T *out) {
  using VecType = InaVecSCALAR<T>;
  __bond<VecType, T, mic_ortho>(a, b, n, box, out);
}

template <typename T>
void _bond(const T *a, const T *b, const int n, const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __bond<VecType, T, mic>(a, b, n, box, out);
}

template <typename T>
void _bond_scaler(const T *a, const T *b, const int n, const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __bond<VecType, T, mic>(a, b, n, box, out);
}

#endif // BOND_H

#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>

#include "arrayview.h"
#include "inastemp_helper.h"
#include "mic.h"
#include "mic_ortho.h"
#include "mic_triclinic.h"

template <typename VecType, typename T, typename pbc_func>
void pairwise_distance__(const T *a, const int m, const T *b, const int n,
                         const T *box, T *out) {

  const std::vector<T> box_a{{box[0], box[3], box[6]}};
  const std::vector<T> box_b{{box[1], box[4], box[7]}};
  const std::vector<T> box_c{{box[2], box[5], box[8]}};

  const ArrayView<T> a_view(m, 3, a);
  const ArrayView<T> b_view(n, 3, b);

  for (auto i = 0; i < m; ++i) {
    const VecType x1 = a_view(i, 0);
    const VecType y1 = a_view(i, 1);
    const VecType z1 = a_view(i, 2);

    const auto last_n = n - (n - i) % VecType::VecLength;
    for (auto j = i; j < last_n; j += VecType::VecLength) {
      const auto x2 = VecType(&b_view(j, 0));
      const auto y2 = VecType(&b_view(j, 1));
      const auto z2 = VecType(&b_view(j, 2));
      const auto res = pbc_func()(x1, y1, z1, x2, y2, z2, box_a, box_b, box_c);
      const auto mindist2 = std::get<0>(res);
      // store results
      // out[i * m + j] = mindist2;
      mindist2.storeInArray(&out[i * m + j]);
      // out[j * n + i] = mindist2;
      for (auto k = 0; k < VecType::VecLength; ++k) {
        const auto jk = j + k;
        out[jk * n + i] = mindist2.at(k);
      }
    }
    // Remainder Loop
    const InaVecSCALAR<T> sx1 = a_view(i, 0);
    const InaVecSCALAR<T> sy1 = a_view(i, 1);
    const InaVecSCALAR<T> sz1 = a_view(i, 2);
    for (auto j = last_n; j < n; ++j) {
      const auto x2 = InaVecSCALAR<T>(b_view(j, 0));
      const auto y2 = InaVecSCALAR<T>(b_view(j, 1));
      const auto z2 = InaVecSCALAR<T>(b_view(j, 2));
      const auto res =
          pbc_func()(sx1, sy1, sz1, x2, y2, z2, box_a, box_b, box_c);
      const auto mindist2 = std::get<0>(res).getVec();
      out[i * m + j] = mindist2;
      out[j * n + i] = mindist2;
    }
  }
}

template <typename T>
void _pairwise_distance_triclinic(const T *a, const int m, const T *b,
                                  const int n, const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  pairwise_distance__<VecType, T, mic_triclinic>(a, m, b, n, box, out);
}

template <typename T>
void _pairwise_distance_ortho(const T *a, const int m, const T *b, const int n,
                              const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  pairwise_distance__<VecType, T, mic_ortho>(a, m, b, n, box, out);
}

template <typename T>
void _pairwise_distance(const T *a, const int m, const T *b, const int n,
                        const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  pairwise_distance__<VecType, T, mic>(a, m, b, n, box, out);
}

#endif // DISTANCE_H

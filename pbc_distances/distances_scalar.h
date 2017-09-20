#ifndef DISTANCE_SCALAR_H
#define DISTANCE_SCALAR_H

#include "distances.h"

template <typename T>
void _pairwise_distance_triclinic_scalar(const T *a, const int m, const T *b,
                                         const int n, const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  pairwise_distance__<VecType, T, mic_triclinic>(a, m, b, n, box, out);
}

template <typename T>
void _pairwise_distance_ortho_scalar(const T *a, const int m, const T *b,
                                     const int n, const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  pairwise_distance__<VecType, T, mic_ortho>(a, m, b, n, box, out);
}

template <typename T>
void _pairwise_distance_scalar(const T *a, const int m, const T *b, const int n,
                               const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  pairwise_distance__<VecType, T, mic>(a, m, b, n, box, out);
}

#endif // DISTANCE_SCALAR_H

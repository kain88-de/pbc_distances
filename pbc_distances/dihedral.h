#ifndef DIHEDRAL_H
#define DIHEDRAL_H

#include "mic.h"
#include "mic_ortho.h"
#include "mic_triclinic.h"

template <typename VecType>
VecType calc_dihedral_angle(const VecType& va_x, const VecType& va_y,const VecType& va_z,
                            const VecType& vb_x, const VecType& vb_y,const VecType& vb_z,
                            const VecType& vz_x, const VecType& vz_y,const VecType& vz_z)
{
  // Returns atan2 from vectors va, vb, vc

  //n1 is normal vector to -va, vb
  //n2 is normal vector to -vb, vc
  const auto n1_x =-va_y*vb_z + va_z*vb_y;
  const auto n1_y = va_x*vb_z - va_z*vb_x;
  const auto n1_z =-va_x*vb_y + va_y*vb_x;

  const auto n2_x =-vb_y*vc_z + vb_z*vc_y;
  const auto n2_y = vb_x*vc_z - vb_z*vc_x;
  const auto n2_z =-vb_x*vc_y + vb_y*vc_x;

  // x = dot(n1,n2) = cos theta
  const auto x = (n1_x*n2_x + n1_y*n2_y + n1_z*n2_z);

  // xp = cross(n1,n2)
  const auto xp_x = n1_y*n2_z - n1_z*n2_y;
  const auto xp_y =-n1_x*n2_z + n1_z*n2_x;
  const auto xp_z = n1_x*n2_y - n1_y*n2_x;

  const auto vb_norm = sqrt(vb_x*vb_x + vb_y*vb_y + vb_z*vb_z);

  const auto y = (xp_x*vb_x + xp_y*vb_y + xp_z*vb_z) / vb_norm;

  // numpy consistency, atan2 is better conditioned than acos
  return  VecType::IfElse(abs(x) == 0 && abs(y) == 0, VecType(NAN), atan2(x, y));
}

template <typename VecType, typename T, typename pbc_func>
void __dihedral(const T *a, const T *b, const T *c, const T* d, const int n, const T *box,
             T *out) {

  const std::vector<T> box_a{{box[0], box[3], box[6]}};
  const std::vector<T> box_b{{box[1], box[4], box[7]}};
  const std::vector<T> box_c{{box[2], box[5], box[8]}};

  const ArrayView<T> a_view(n, 3, a);
  const ArrayView<T> b_view(n, 3, b);
  const ArrayView<T> c_view(n, 3, c);
  const ArrayView<T> c_view(n, 3, d);

  const auto last_n = n - (n % VecType::VecLength);

  for (auto i = 0; i < last_n; ++i) {
    const VecType x1 = a_view(i, 0);
    const VecType y1 = a_view(i, 1);
    const VecType z1 = a_view(i, 2);

    const VecType x2 = b_view(i, 0);
    const VecType y2 = b_view(i, 1);
    const VecType z2 = b_view(i, 2);

    const auto res_21 = pbc_func()(x2, y2, z2, x1, y1, z1, box_a, box_b, box_c);
    const auto x21 = std::get<1>(res_21);
    const auto y21 = std::get<2>(res_21);
    const auto z21 = std::get<3>(res_21);

    const VecType x3 = c_view(i, 0);
    const VecType y3 = c_view(i, 1);
    const VecType z3 = c_view(i, 2);

    const auto res_32 = pbc_func()(x3, y3, z3, x2, y2, z2, box_a, box_b, box_c);
    const auto x32 = std::get<1>(res_32);
    const auto y32 = std::get<2>(res_32);
    const auto z32 = std::get<3>(res_32);

    const VecType x4 = d_view(i, 0);
    const VecType y4 = d_view(i, 1);
    const VecType z4 = d_view(i, 2);

    const auto res_43 = pbc_func()(x4, y4, z4, x3, y3, z3, box_a, box_b, box_c);
    const auto x43 = std::get<1>(res_43);
    const auto y43 = std::get<2>(res_43);
    const auto z43 = std::get<3>(res_43);

    const auto angles = calc_dihedral_angle(x21, y21, z21, x32, y32, z32, x43, y43, z43);
    angles.storeInArray(&out[i]);
  }

  // Remainder Loop
  for (auto i = last_n; i < n; ++i) {
  }
}

template <typename T>
void _dihedral_triclinic(const T *a, const T *b, const T *c, const T* d, const int n,
                      const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __dihedral<VecType, T, mic_triclinic>(a, b, c, d, n, box, out);
}

template <typename T>
void _dihedral_triclinic_scaler(const T *a, const T *b, const T *c, const T * d, const int n,
                             const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __dihedral<VecType, T, mic_triclinic>(a, b, c, d, n, box, out);
}

template <typename T>
void _dihedral_ortho(const T *a, const T *b, const T *c, const T* d, const int n,
                         const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __dihedral<VecType, T, mic_ortho>(a, b, c, d, n, box, out);
}

template <typename T>
void _dihedral_ortho_scaler(const T *a, const T *b, const T *c, const T * d, const int n,
                                const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __dihedral<VecType, T, mic_ortho>(a, b, c, d, n, box, out);
}

template <typename T>
void _dihedral(const T *a, const T *b, const T *c, const T* d, const int n,
                     const T *box, T *out) {
  using VecType = InaVecBestType<T>;
  __dihedral<VecType, T, mic>(a, b, c, d, n, box, out);
}

template <typename T>
void _dihedral_scaler(const T *a, const T *b, const T *c, const T * d, const int n,
                            const T *box, T *out) {
  using VecType = InaVecSCALAR<T>;
  __dihedral<VecType, T, mic>(a, b, c, d, n, box, out);
}
#endif // DIHEDRAL_H

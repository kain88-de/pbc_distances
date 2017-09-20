#ifndef INASTEMP_HELPER_H
#define INASTEMP_HELPER_H

#include <InastempStaticConfig.h>
#include <SCALAR/InaVecSCALARDouble.hpp>
#include <SCALAR/InaVecSCALARFloat.hpp>

#ifdef INASTEMP_USE_SSE41
#include "SSE41/InaVecSSE41Float.hpp"
#include "SSE41/InaVecSSE41Double.hpp"
InaVecSSE41<float> ina_round(InaVecSSE41<float> inVec){
  return _mm_round_ps (inVec.getVec(), (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
}

InaVecSSE41<double> ina_round(InaVecSSE41<double> inVec){
  return _mm_round_pd (inVec.getVec(), (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
}
#endif

#ifdef INASTEMP_USE_AVX
#include "AVX/InaVecAVXFloat.hpp"
#include "AVX/InaVecAVXDouble.hpp"
InaVecAVX<float> ina_round(InaVecAVX<float> inVec){
  return _mm256_round_ps (inVec.getVec(), (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
}

InaVecAVX<double> ina_round(InaVecAVX<double> inVec){
  return _mm256_round_pd (inVec.getVec(), (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
}
#endif

template<typename T>
InaVecSCALAR<T> ina_round(InaVecSCALAR<T> inVec){
  return std::round(inVec.getVec());
}


#endif // INASTEMP_HELPER_H

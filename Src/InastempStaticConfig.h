///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INASTEMPSTATICCONFIG_H
#define INASTEMPSTATICCONFIG_H

#define INASTEMP_USE_STATIC_CONFIG

#define INASTEMP_USE_SCALAR
#define INASTEMP_STATIC_BEST_TYPE InaVecSCALAR
#include "SCALAR/InaVecSCALARFloat.hpp"
#include "SCALAR/InaVecSCALARDouble.hpp"

#ifdef __SSE3__
#define INASTEMP_USE_SSE3
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecSSE3
#include "SSE3/InaVecSSE3Float.hpp"
#include "SSE3/InaVecSSE3Double.hpp"
#endif

#ifdef __SSSE3__
#define INASTEMP_USE_SSSE3
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecSSSE3
#include "SSSE3/InaVecSSSE3Float.hpp"
#include "SSSE3/InaVecSSSE3Double.hpp"
#endif


#ifdef __SSE4_1__
#define INASTEMP_USE_SSE41
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecSSE41
#include "SSE41/InaVecSSE41Float.hpp"
#include "SSE41/InaVecSSE41Double.hpp"
#endif

#ifdef __SSE4_2__
#define INASTEMP_USE_SSE42
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecSSE42
#include "SSE42/InaVecSSE42Float.hpp"
#include "SSE42/InaVecSSE42Double.hpp"
#endif

#ifdef __AVX__
#define INASTEMP_USE_AVX
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecAVX
#include "AVX/InaVecAVXFloat.hpp"
#include "AVX/InaVecAVXDouble.hpp"
#endif

#ifdef __AVX2__
#define INASTEMP_USE_AVX2
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecAVX2
#include "AVX2/InaVecAVX2Float.hpp"
#include "AVX2/InaVecAVX2Double.hpp"
#endif

#if defined(__AVX512F__) && defined(__AVX512CD__)
#define INASTEMP_USE_AVX512COMMON
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecAVX512COMMON
#include "AVX512COMMON/InaVecAVX512COMMONFloat.hpp"
#include "AVX512COMMON/InaVecAVX512COMMONDouble.hpp"
#endif

#if defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512ER__) && defined(__AVX512PF__)
#define INASTEMP_USE_AVX512KNL
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecAVX512KNL
#include "AVX512KNL/InaVecAVX512KNLFloat.hpp"
#include "AVX512KNL/InaVecAVX512KNLDouble.hpp"
#endif

#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512BW__) && defined(__AVX512CD__) && defined(__AVX512DQ__)
#define INASTEMP_USE_AVX512SKL
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecAVX512SKL
#include "AVX512SKL/InaVecAVX512SKLFloat.hpp"
#include "AVX512SKL/InaVecAVX512SKLDouble.hpp"
#endif

#ifdef __IBMCPP__
#define INASTEMP_USE_ALTIVEC
#define INASTEMP_USE_XL
#undef INASTEMP_STATIC_BEST_TYPE
#define INASTEMP_STATIC_BEST_TYPE InaVecALTIVEC
#include "ALTIVEC/InaVecALTIVECFloat.hpp"
#include "ALTIVEC/InaVecALTIVECDouble.hpp"
#endif

template < class RealType >
using InaVecBestType = INASTEMP_STATIC_BEST_TYPE< RealType >;

using InaVecBestTypeFloat  = INASTEMP_STATIC_BEST_TYPE< float >;
using InaVecBestTypeDouble = INASTEMP_STATIC_BEST_TYPE< double >;

#endif

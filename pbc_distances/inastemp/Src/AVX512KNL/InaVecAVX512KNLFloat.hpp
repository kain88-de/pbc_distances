///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INAVECAVX512KNLFLOAT_HPP
#define INAVECAVX512KNLFLOAT_HPP

#include "InastempGlobal.h"
#include "Common/InaIfElse.hpp"
#include "Common/InaUtils.hpp"
#include "AVX512COMMON/InaVecAVX512COMMONFloat.hpp"

#ifndef INASTEMP_USE_AVX512KNL
#error InaVecAVX512KNL512KNL<float> is included but AVX512KNL is not enable in the configuration
#endif

#include "Common/InaFastExp.hpp"

#include <immintrin.h>

#include <cmath>

// Forward declarations
template <class RealType>
using InaVecMaskAVX512KNL = InaVecMaskAVX512COMMON<RealType>;

// Forward declarations
template <class RealType>
class InaVecAVX512KNL;

template <>
class alignas(InaVecAVX512COMMON<float>::Alignement) InaVecAVX512KNL<float> : public InaVecAVX512COMMON<float> {
    using Parent = InaVecAVX512COMMON<float>;

public:
    using InaVecAVX512COMMON<float>::InaVecAVX512COMMON;

    inline InaVecAVX512KNL(){}

    inline InaVecAVX512KNL(const InaVecAVX512COMMON<float>& other)
        : Parent(other){}

    inline InaVecAVX512KNL rsqrt() const {
        return _mm512_rsqrt28_ps(Parent::vec);
    }

    inline static const char* GetName(){
        return "InaVecAVX512KNL<float>";
    }

    inline static InaIfElse< InaVecAVX512KNL<float> >::ThenClass If(const typename Parent::MaskType& inTest) {
        return InaIfElse< InaVecAVX512KNL<float> >::IfClass().If(inTest);
    }
};




#endif

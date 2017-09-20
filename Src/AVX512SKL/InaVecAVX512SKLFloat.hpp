///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INAVECAVX512SKLFLOAT_HPP
#define INAVECAVX512SKLFLOAT_HPP

#include "InastempGlobal.h"
#include "Common/InaIfElse.hpp"
#include "Common/InaUtils.hpp"
#include "AVX512COMMON/InaVecAVX512COMMONFloat.hpp"

#ifndef INASTEMP_USE_AVX512SKL
#error InaVecAVX512SKL512SKL<float> is included but AVX512SKL is not enable in the configuration
#endif

#include "Common/InaFastExp.hpp"

#include <immintrin.h>

#include <cmath>

// Forward declarations
template <class RealType>
using InaVecMaskAVX512SKL = InaVecMaskAVX512COMMON<RealType>;

// Forward declarations
template <class RealType>
class InaVecAVX512SKL;

template <>
class alignas(InaVecAVX512COMMON<float>::Alignement) InaVecAVX512SKL<float> : public InaVecAVX512COMMON<float> {
    using Parent = InaVecAVX512COMMON<float>;

public:
    using InaVecAVX512COMMON<float>::InaVecAVX512COMMON;

    inline InaVecAVX512SKL(){}

    inline InaVecAVX512SKL(const InaVecAVX512COMMON<float>& other)
        : Parent(other){}

    inline static const char* GetName(){
        return "InaVecAVX512SKL<float>";
    }

    inline static InaIfElse< InaVecAVX512SKL<float> >::ThenClass If(const typename Parent::MaskType& inTest) {
        return InaIfElse< InaVecAVX512SKL<float> >::IfClass().If(inTest);
    }
};

#endif

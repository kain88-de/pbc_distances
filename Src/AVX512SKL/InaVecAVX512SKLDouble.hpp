///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INAVECAVX512SKLDOUBLE_HPP
#define INAVECAVX512SKLDOUBLE_HPP

#include "InastempGlobal.h"
#include "Common/InaIfElse.hpp"
#include "Common/InaUtils.hpp"
#include "AVX512COMMON/InaVecAVX512COMMONDouble.hpp"

#ifndef INASTEMP_USE_AVX512SKL
#error InaVecAVX512SKL<double> is included but AVX512SKL is not enable in the configuration
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
class alignas(InaVecAVX512COMMON<double>::Alignement) InaVecAVX512SKL<double> : public InaVecAVX512COMMON<double> {
    using Parent = InaVecAVX512COMMON<double>;

public:
    using InaVecAVX512COMMON<double>::InaVecAVX512COMMON;

    inline InaVecAVX512SKL(){}

    inline InaVecAVX512SKL(const InaVecAVX512COMMON<double>& other)
        : Parent(other){}

    inline static const char* GetName(){
        return "InaVecAVX512SKL<double>";
    }

    inline static InaIfElse< InaVecAVX512SKL<double> >::ThenClass If(const typename Parent::MaskType& inTest) {
        return InaIfElse< InaVecAVX512SKL<double> >::IfClass().If(inTest);
    }
};

#endif

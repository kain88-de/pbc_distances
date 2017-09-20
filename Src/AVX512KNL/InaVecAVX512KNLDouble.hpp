///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INAVECAVX512KNLDOUBLE_HPP
#define INAVECAVX512KNLDOUBLE_HPP

#include "InastempGlobal.h"
#include "Common/InaIfElse.hpp"
#include "Common/InaUtils.hpp"
#include "AVX512COMMON/InaVecAVX512COMMONDouble.hpp"

#ifndef INASTEMP_USE_AVX512KNL
#error InaVecAVX512KNL<double> is included but AVX512KNL is not enable in the configuration
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
class alignas(InaVecAVX512COMMON<double>::Alignement) InaVecAVX512KNL<double> : public InaVecAVX512COMMON<double> {
    using Parent = InaVecAVX512COMMON<double>;

public:
    using InaVecAVX512COMMON<double>::InaVecAVX512COMMON;

    inline InaVecAVX512KNL(){}

    inline InaVecAVX512KNL(const InaVecAVX512COMMON<double>& other)
        : Parent(other){}

    inline static const char* GetName(){
        return "InaVecAVX512KNL<double>";
    }

    inline static InaIfElse< InaVecAVX512KNL<double> >::ThenClass If(const typename Parent::MaskType& inTest) {
        return InaIfElse< InaVecAVX512KNL<double> >::IfClass().If(inTest);
    }
};



#endif

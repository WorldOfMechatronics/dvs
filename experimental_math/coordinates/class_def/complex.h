#ifndef DVS_MATH_COORDINATES_CLASS_DEF_COMPLEX_H_
#define DVS_MATH_COORDINATES_CLASS_DEF_COMPLEX_H_

#include "dvs/math/misc/forward_decl.h"

namespace dvs
{
template <typename T> struct ComplexCoord
{
    T real;
    T imag;

    ComplexCoord(const T real_, const T imag_);
    ComplexCoord();

    PolarCoord<T> toPolar() const;
    ComplexCoord<T> conjugate() const;
    ComplexCoord<T> inv() const;
    Vec2<T> toVec2() const;
    T abs() const;
};
}  // namespace dvs

#endif // DVS_MATH_COORDINATES_CLASS_DEF_COMPLEX_H_

#ifndef DVS_MATH_GEOMETRY_CLASS_DEF_LINE_3D_H_
#define DVS_MATH_GEOMETRY_CLASS_DEF_LINE_3D_H_

#include "dvs/math/misc/forward_decl.h"

namespace dvs
{
template <typename T> struct Line3D
{
    // Point on line
    Point3<T> p;

    // Vector in line direction
    Vec3<T> v;

    Line3D(const Point3<T>& p_, const Vec3<T>& v_);
    template <typename Y> Line3D(const Line3D<Y>& l);
    Line3D();

    Vec3<T> vectorNormalToLine() const;
    Point3<T> eval(const T t) const;
    Point3<T> closestPointOnLineFromPoint(const Point3<T>& q) const;
    Vec3<T> vectorBetweenClosestPointOnLineAndPoint(const Point3<T>& q) const;
    Line3D<T> translatedLine(const Vec3<T>& v) const;
    std::vector<Point3<T>> closestPointsBetweenLines(const Line3D<T>& line) const;
    std::pair<Point3<T>, Vec3<T>> projectPointAndVectorOntoLine(const Point3<T>& q, const Vec3<T>& v) const;
    Point3<T> rotatePointAroundLine(const Point3<T>& q, const T angle) const;
    Line3D<T> negatedLine() const;
    T pointDistanceFromLine(const Point3<T>& q) const;
    T angleBetweenLines(const Line3D<T>& line) const;
    Line3D<T> rotateLineAroundLine(const Line3D<T>& line_to_be_rotated, const T angle) const;
};
}  // namespace dvs

#endif // DVS_MATH_GEOMETRY_CLASS_DEF_LINE_3D_H_

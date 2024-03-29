
#ifndef DVS_MATH_GEOMETRY_SPHERE_H_
#define DVS_MATH_GEOMETRY_SPHERE_H_

#include <cmath>
#include <vector>

#include "dvs/math/geometry/class_def/sphere.h"
#include "dvs/math/lin_alg.h"

namespace dvs
{
template <typename T> Sphere<T>::Sphere(const T radius_, const Point3<T>& center_)
{
    radius = radius_;
    center = center_;
}
template <typename T> Sphere<T>::Sphere() {}

template <typename T> bool Sphere<T>::doesLineIntersect(const Line3D<T>& line) const
{
    const Point3<T> closest_point = line.closestPointOnLineFromPoint(center);

    // T distance_between_points = (closest_point - c).squaredNorm();
    // return distance_between_points < r * r;

    T distance_between_points = (closest_point - center).norm();
    return distance_between_points < radius;
}

template <typename T> std::pair<Point3<T>, Point3<T>> Sphere<T>::lineIntersectionPoint(const Line3D<T>& line) const
{
    // There are two intersection points
    std::pair<Point3<T>, Point3<T>> intersection_points;

    if (!doesLineIntersect(line))
    {
        intersection_points.first.x = NAN;
        intersection_points.first.y = NAN;
        intersection_points.first.z = NAN;

        intersection_points.second.x = NAN;
        intersection_points.second.y = NAN;
        intersection_points.second.z = NAN;
    }
    else
    {
        const Vec3<T> normalized_line_vector = line.v.normalized();
        const Point3<T> closest_point = line.closestPointOnLineFromPoint(center);

        const T squared_distance_between_points = (closest_point - center).squaredNorm();

        const T cath = std::sqrt(squared_distance_between_points - radius * radius);

        intersection_points[0] = center + cath * normalized_line_vector;
        intersection_points[1] = center - cath * normalized_line_vector;
    }

    return intersection_points;
}

}  // namespace dvs

#endif // DVS_MATH_GEOMETRY_SPHERE_H_

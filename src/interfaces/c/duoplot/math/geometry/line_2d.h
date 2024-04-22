#ifndef DUOPLOT_MATH_GEOMETRY_LINE_2D_H_
#define DUOPLOT_MATH_GEOMETRY_LINE_2D_H_

#include "duoplot/math/vector_low_dim/vec2.h"

typedef struct S_PLine2DD
{
    Point2d p;
    Vec2D v;
} PLine2DD;

typedef struct S_HLine2DD
{
    double a;
    double b;
    double c;
} HLine2DD;

#endif  // DUOPLOT_MATH_GEOMETRY_LINE_2D_H_

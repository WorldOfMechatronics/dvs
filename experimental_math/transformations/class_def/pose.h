#ifndef DVS_MATH_TRANSFORMATIONS_CLASS_DEF_POSE_H_
#define DVS_MATH_TRANSFORMATIONS_CLASS_DEF_POSE_H_

#include "dvs/math/misc/forward_decl.h"

namespace dvs
{
template <typename T> class PoseSE3
{
private:
    Matrix<T> rotation_matrix;
    Vec3<T> translation_vector;

public:
    Matrix<T> getRotationMatrix() const;
    Vec3<T> getTranslationVector() const;
    Matrix<T> getPoseMatrix() const;
    Matrix<T> getInversePoseMatrix() const;
    void invert();

    PoseSE3(const Matrix<T>& rotation_matrix, const Vec3<T>& translation_vector);
    PoseSE3(const Matrix<T>& pose_matrix);
    PoseSE3();
};
}  // namespace dvs

#endif // DVS_MATH_TRANSFORMATIONS_CLASS_DEF_POSE_H_

#include "precompiled.hpp"
#include "ui/property/MatrixProperties.hpp"

namespace balls {

using namespace glm;

template class MatrixProperty<tmat2x2, Vec2Property>;
template class MatrixProperty<tmat2x3, Vec3Property>;
template class MatrixProperty<tmat2x4, Vec4Property>;
template class MatrixProperty<tmat3x2, Vec2Property>;
template class MatrixProperty<tmat3x3, Vec3Property>;
template class MatrixProperty<tmat3x4, Vec4Property>;
template class MatrixProperty<tmat4x2, Vec2Property>;
template class MatrixProperty<tmat4x3, Vec3Property>;
template class MatrixProperty<tmat4x4, Vec4Property>;

template class MatrixProperty<tmat2x2, DVec2Property>;
template class MatrixProperty<tmat2x3, DVec3Property>;
template class MatrixProperty<tmat2x4, DVec4Property>;
template class MatrixProperty<tmat3x2, DVec2Property>;
template class MatrixProperty<tmat3x3, DVec3Property>;
template class MatrixProperty<tmat3x4, DVec4Property>;
template class MatrixProperty<tmat4x2, DVec2Property>;
template class MatrixProperty<tmat4x3, DVec3Property>;
template class MatrixProperty<tmat4x4, DVec4Property>;
}

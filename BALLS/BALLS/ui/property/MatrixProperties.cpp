#include "precompiled.hpp"
#include "ui/property/MatrixProperties.hpp"

namespace balls {

using namespace glm;

template class MatrixProperty<mat2, Vec2Property>;
template class MatrixProperty<mat2x3, Vec3Property>;
template class MatrixProperty<mat2x4, Vec4Property>;
template class MatrixProperty<mat3x2, Vec2Property>;
template class MatrixProperty<mat3, Vec3Property>;
template class MatrixProperty<mat3x4, Vec4Property>;
template class MatrixProperty<mat4x2, Vec2Property>;
template class MatrixProperty<mat4x3, Vec3Property>;
template class MatrixProperty<mat4, Vec4Property>;

template class MatrixProperty<dmat2, DVec2Property>;
template class MatrixProperty<dmat2x3, DVec3Property>;
template class MatrixProperty<dmat2x4, DVec4Property>;
template class MatrixProperty<dmat3x2, DVec2Property>;
template class MatrixProperty<dmat3, DVec3Property>;
template class MatrixProperty<dmat3x4, DVec4Property>;
template class MatrixProperty<dmat4x2, DVec2Property>;
template class MatrixProperty<dmat4x3, DVec3Property>;
template class MatrixProperty<dmat4, DVec4Property>;
}

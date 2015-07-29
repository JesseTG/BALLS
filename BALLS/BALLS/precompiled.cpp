#include "precompiled.hpp"

// Template method instantiations (don't do it for inline methods!)
// None for now

// Template class instantiations
// None for now

// STL template instantiations
namespace std {
template struct array<uint16_t, 3>;

template struct pair<GLenum, GLenum>;
template struct pair<QString, QVariant>;

template class unordered_map<GLenum, GLenum>;

template class vector<float>;
template class vector<uint16_t>;
template class vector<QVector3D>;
}

// glm template instantiations
namespace glm {
template struct tvec2<float, highp>;
template struct tvec2<double, highp>;
template struct tvec2<int, highp>;
template struct tvec2<glm::uint, highp>;

template struct tvec3<float, highp>;
template struct tvec3<double, highp>;
template struct tvec3<int, highp>;
template struct tvec3<glm::uint, highp>;

template struct tvec4<float, highp>;
template struct tvec4<double, highp>;
template struct tvec4<int, highp>;
template struct tvec4<glm::uint, highp>;

template struct tquat<float, highp>;
template struct tquat<double, highp>;

template struct tmat2x2<float, highp>;
template struct tmat2x2<double, highp>;
template struct tmat2x3<float, highp>;
template struct tmat2x3<double, highp>;
template struct tmat2x4<float, highp>;
template struct tmat2x4<double, highp>;
template struct tmat3x2<float, highp>;
template struct tmat3x2<double, highp>;
template struct tmat3x3<float, highp>;
template struct tmat3x3<double, highp>;
template struct tmat3x4<float, highp>;
template struct tmat3x4<double, highp>;
template struct tmat4x2<float, highp>;
template struct tmat4x2<double, highp>;
template struct tmat4x3<float, highp>;
template struct tmat4x3<double, highp>;
template struct tmat4x4<float, highp>;
template struct tmat4x4<double, highp>;
}

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

//template class unordered_map<GLenum, GLenum>;

template class vector<float>;
template class vector<uint16_t>;
template class vector<glm::vec3>;
}

// glm template instantiations
namespace glm {
template struct tvec2<float>;
template struct tvec2<double>;
template struct tvec2<int>;
template struct tvec2<glm::uint>;

template struct tvec3<float>;
template struct tvec3<double>;
template struct tvec3<int>;
template struct tvec3<glm::uint>;

template struct tvec4<float>;
template struct tvec4<double>;
template struct tvec4<int>;
template struct tvec4<glm::uint>;

template struct tquat<float>;
template struct tquat<double>;

template struct tmat2x2<float>;
template struct tmat2x2<double>;
template struct tmat2x3<float>;
template struct tmat2x3<double>;
template struct tmat2x4<float>;
template struct tmat2x4<double>;
template struct tmat3x2<float>;
template struct tmat3x2<double>;
template struct tmat3x3<float>;
template struct tmat3x3<double>;
template struct tmat3x4<float>;
template struct tmat3x4<double>;
template struct tmat4x2<float>;
template struct tmat4x2<double>;
template struct tmat4x3<float>;
template struct tmat4x3<double>;
template struct tmat4x4<float>;
template struct tmat4x4<double>;
}

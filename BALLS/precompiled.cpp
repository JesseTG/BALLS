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

// template class unordered_map<GLenum, GLenum>;

template class vector<float>;
template class vector<uint16_t>;
template class vector<glm::vec3>;
}

// glm template instantiations
namespace glm {
template struct vec<2, double>;
template struct vec<2, float>;
template struct vec<2, int>;
template struct vec<2, glm::uint>;

template struct vec<3, double>;
template struct vec<3, float>;
template struct vec<3, int>;
template struct vec<3, glm::uint>;

template struct vec<4, double>;
template struct vec<4, float>;
template struct vec<4, int>;
template struct vec<4, glm::uint>;

template struct tquat<float>;
template struct tquat<double>;

template struct mat<2, 2, float>;
template struct mat<2, 2, double>;
template struct mat<2, 3, float>;
template struct mat<2, 3, double>;
template struct mat<2, 4, float>;
template struct mat<2, 4, double>;
template struct mat<3, 2, float>;
template struct mat<3, 2, double>;
template struct mat<3, 3, float>;
template struct mat<3, 3, double>;
template struct mat<3, 4, float>;
template struct mat<3, 4, double>;
template struct mat<4, 2, float>;
template struct mat<4, 2, double>;
template struct mat<4, 3, float>;
template struct mat<4, 3, double>;
template struct mat<4, 4, float>;
template struct mat<4, 4, double>;
}

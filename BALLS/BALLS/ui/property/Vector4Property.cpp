#include "precompiled.hpp"
#include "ui/property/Vector4Property.hpp"

namespace balls {
template class Vector4PropertyBase<ivec4>;
template class Vector4PropertyBase<bvec4>;
template class Vector4PropertyBase<uvec4>;
template class Vector4PropertyBase<vec4>;
template class Vector4PropertyBase<dvec4>;
}

#include "precompiled.hpp"
#include "ui/property/Vector3Property.hpp"

namespace balls {
template class Vector3PropertyBase<bvec3>;
template class Vector3PropertyBase<dvec3>;
template class Vector3PropertyBase<ivec3>;
template class Vector3PropertyBase<uvec3>;
template class Vector3PropertyBase<vec3>;
}

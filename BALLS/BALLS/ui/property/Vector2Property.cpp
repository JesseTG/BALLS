#include "precompiled.hpp"
#include "ui/property/Vector2Property.hpp"

namespace balls {
using glm::tvec2;

template class VectorProperty<tvec2, bool>;
template class VectorProperty<tvec2, double>;
template class VectorProperty<tvec2, int>;
template class VectorProperty<tvec2, unsigned int>;
template class VectorProperty<tvec2, float>;
}

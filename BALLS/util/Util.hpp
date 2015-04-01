#ifndef UTIL_HPP
#define UTIL_HPP

namespace balls {
namespace util {
/**
 * @brief sineLUT Rounds the input to
 * @param theta The angle to compute the sine of
 * @return A look-up table approximation
 */
float sinLUT(const float theta) noexcept;

float cosLUT(const float theta) noexcept;
}
}
#endif // UTIL_HPP

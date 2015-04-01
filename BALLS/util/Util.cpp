#include "util/Util.hpp"

#include <array>
#include <cmath>
#include <unordered_map>
#include <QtGlobal>


namespace balls {
namespace util {

constexpr int SIN_BITS = 14;
constexpr int SIN_MASK = (1U << SIN_BITS) - 1U;
constexpr int SIN_COUNT = SIN_MASK + 1;
constexpr double DEG2RAD = M_PI / 180;
constexpr double DEGINDEX = SIN_COUNT / 360;
constexpr double RADINDEX = SIN_COUNT / (M_PI * 2);

using std::array;
using std::floor;
using std::remainder;
using std::sin;
using std::unordered_map;

struct SineTable {
  SineTable() {
    for (int i = 0; i < SIN_COUNT; i++) {
      table[i] = sin((i + 0.5) / (SIN_COUNT * (M_PI * 2.0)));
    }

    for (int i = 0; i < 360; i += 90) {
      table[static_cast<int>(i * DEGINDEX) & SIN_MASK] = sin(i * DEG2RAD);
    }
  }

  array<float, SIN_COUNT> table;
};

static SineTable table;

float sinLUT(const float theta) noexcept {
  return table.table[int(theta * RADINDEX) & SIN_MASK];
}

float cosLUT(const float theta) noexcept {
  return table.table[int((theta + (M_PI / 2) * RADINDEX)) & SIN_MASK];
}
}
}

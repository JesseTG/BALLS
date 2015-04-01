#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <cstdint>
#include <functional>

#include <QOpenGLFunctions>
#include <QVariant>

namespace balls {
namespace config {

struct Setting {
  QVariant value;
  bool changed;

  Setting() : Setting(0) {}
  Setting(const QVariant& var, const bool c) : value(var), changed(c) {}
  Setting(const QVariant& var) : Setting(var, false) {}
};

enum SettingKey {
  WireFrame,
  DepthTestEnabled,
  FaceCullingEnabled,
  Dithering,
  Count,
};
}
}

namespace std {
template <>
struct hash<balls::config::SettingKey> {
  using argument_type = balls::config::SettingKey;
  using result_type = std::size_t;

  result_type operator()(argument_type const& s) const noexcept {
    return static_cast<result_type>(s);
  }
};
}

#endif // OPTIONS_HPP

#include "precompiled.hpp"
#include "config/Settings.hpp"

namespace balls {
namespace config {
namespace SettingKey {
const QString WireFrame = "wireframe";
const QString DepthTestEnabled = "depth-test";
const QString FaceCullingEnabled = "face-culling";
const QString Dithering = "dithering";
const QString ClipDistance = "clip-distance";
};

const char* to_cstring(const BlendFunction e) {
  switch (e) {
  case BlendFunction::None:
    return "None";
  case BlendFunction::Zero:
    return "Zero";
  case BlendFunction::One:
    return "One";
  case BlendFunction::SourceColor:
    return "SourceColor";
  case BlendFunction::OneMinusSourceColor:
    return "OneMinusSourceColor";
  case BlendFunction::DestinationColor:
    return "DestinationColor";
  case BlendFunction::OneMinusDestinationColor:
    return "OneMinusDestinationColor";
  case BlendFunction::SourceAlpha:
    return "SourceAlpha";
  case BlendFunction::OneMinusSourceAlpha:
    return "OneMinusSourceAlpha";
  case BlendFunction::DestinationAlpha:
    return "DestinationAlpha";
  case BlendFunction::OneMinusDestinationAlpha:
    return "OneMinusDestinationAlpha";
  case BlendFunction::ConstantColor:
    return "ConstantColor";
  case BlendFunction::OneMinusConstantColor:
    return "OneMinusConstantColor";
  case BlendFunction::ConstantAlpha:
    return "ConstantAlpha";
  case BlendFunction::OneMinusConstantAlpha:
    return "OneMinusConstantAlpha";
  default:
    Q_UNREACHABLE();
    return "Unknown";
  }
}

const char* to_cstring(const ColorCopyFunction e) {
  switch (e) {
  case ColorCopyFunction::Copy:
    return "Copy";
  case ColorCopyFunction::CopyInverted:
    return "CopyInverted";
  case ColorCopyFunction::Clear:
    return "Clear";
  case ColorCopyFunction::Set:
    return "Set";
  case ColorCopyFunction::NoOp:
    return "NoOp";
  case ColorCopyFunction::Invert:
    return "Invert";
  case ColorCopyFunction::And:
    return "And";
  case ColorCopyFunction::Nand:
    return "Nand";
  case ColorCopyFunction::Or:
    return "Or";
  case ColorCopyFunction::Nor:
    return "Nor";
  case ColorCopyFunction::Xor:
    return "Xor";
  case ColorCopyFunction::Equivalent:
    return "Equivalent";
  case ColorCopyFunction::AndReverse:
    return "AndReverse";
  case ColorCopyFunction::AndInverted:
    return "AndInverted";
  case ColorCopyFunction::OrReverse:
    return "OrReverse";
  case ColorCopyFunction::OrInverted:
    return "OrInverted";
  default:
    Q_UNREACHABLE();
    return "Unknown";
  }
}
}
}

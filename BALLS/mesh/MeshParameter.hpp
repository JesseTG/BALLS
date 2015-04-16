#ifndef MESHPARAMETER_HPP
#define MESHPARAMETER_HPP

#include <cstdint>

#include <QtCore/QtGlobal>
#include <QtCore/QString>

namespace balls {
namespace mesh {

class MeshParameter {
public:
  MeshParameter(const int i, const int min, const int max) Q_DECL_NOEXCEPT
   : min(min),
     max(max) {
    this->set(i);
  }

  MeshParameter(const int i) Q_DECL_NOEXCEPT : MeshParameter(i, 0, 0) {}

  MeshParameter(const float f, const float min, const float max) Q_DECL_NOEXCEPT
   : min(min),
     max(max) {
    this->set(f);
  }
  MeshParameter(const float f) Q_DECL_NOEXCEPT : MeshParameter(f, 0.0f, 0.0f) {}

  MeshParameter(const bool b) Q_DECL_NOEXCEPT : min(0), max(0) { this->set(b); }

  MeshParameter() Q_DECL_NOEXCEPT : min(0), max(0) {
    this->set(static_cast<int>(0));
  }

  enum class Type : std::uint8_t { Integer, Real, Boolean };

  void set(const int i) Q_DECL_NOEXCEPT {
    this->integer = i;
    this->type = Type::Integer;
  }

  void set(const float f) Q_DECL_NOEXCEPT {
    this->real = f;
    this->type = Type::Real;
  }

  void set(const bool b) Q_DECL_NOEXCEPT {
    this->on = b;
    this->type = Type::Boolean;
  }

  float getMin() const Q_DECL_NOEXCEPT { return this->min; }

  float getMax() const Q_DECL_NOEXCEPT { return this->max; }

  void setMin(const float min) Q_DECL_NOEXCEPT { this->min = min; }

  void setMax(const float max) Q_DECL_NOEXCEPT { this->max = max; }

  int getInteger() const Q_DECL_NOEXCEPT {
    Q_ASSERT(this->type == Type::Integer);
    return (this->type == Type::Integer) ? this->integer : 0;
  }

  float getFloat() const Q_DECL_NOEXCEPT {
    Q_ASSERT(this->type == Type::Real);
    return (this->type == Type::Real) ? this->real : 0.0f;
  }

  bool getBool() const Q_DECL_NOEXCEPT {
    Q_ASSERT(this->type == Type::Boolean);
    return (this->type == Type::Boolean) ? this->on : false;
  }

  Type getType() const Q_DECL_NOEXCEPT { return this->type; }

private:
  union {
    int integer;
    float real;
    bool on;
  };

  float min, max;

  Type type;
};

typedef std::unordered_map<QString, MeshParameter> MeshParameters;
}
}
#endif // MESHPARAMETER_HPP

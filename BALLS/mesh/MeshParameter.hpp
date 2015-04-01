#ifndef MESHPARAMETER_HPP
#define MESHPARAMETER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#include <QtGlobal>

namespace balls {
namespace mesh {

class MeshParameter {
public:
  MeshParameter(const int i, const int min, const int max) noexcept : min(min),
                                                                      max(max) {
    this->set(i);
  }

  MeshParameter(const int i) noexcept : MeshParameter(i, 0, 0) {}

  MeshParameter(const float f, const float min, const float max) noexcept
   : min(min),
     max(max) {
    this->set(f);
  }
  MeshParameter(const float f) noexcept : MeshParameter(f, 0.0f, 0.0f) {}

  MeshParameter(const bool b) noexcept : min(0), max(0) { this->set(b); }

  MeshParameter() noexcept : min(0), max(0) { this->set(static_cast<int>(0)); }

  enum class Type : std::uint8_t { Integer, Real, Boolean };

  void set(const int i) noexcept {
    this->integer = i;
    this->type = Type::Integer;
  }

  void set(const float f) noexcept {
    this->real = f;
    this->type = Type::Real;
  }

  void set(const bool b) noexcept {
    this->on = b;
    this->type = Type::Boolean;
  }

  float getMin() const noexcept { return this->min; }

  float getMax() const noexcept { return this->max; }

  void setMin(const float min) noexcept { this->min = min; }

  void setMax(const float max) noexcept { this->max = max; }

  int getInteger() const noexcept {
    Q_ASSERT(this->type == Type::Integer);
    return (this->type == Type::Integer) ? this->integer : 0;
  }

  float getFloat() const noexcept {
    Q_ASSERT(this->type == Type::Real);
    return (this->type == Type::Real) ? this->real : 0.0f;
  }

  bool getBool() const noexcept {
    Q_ASSERT(this->type == Type::Boolean);
    return (this->type == Type::Boolean) ? this->on : false;
  }

  Type getType() const noexcept { return this->type; }

private:
  union {
    int integer;
    float real;
    bool on;
  };

  float min, max;

  Type type;
};

typedef std::unordered_map<std::string, MeshParameter> MeshParameters;
}
}
#endif // MESHPARAMETER_HPP

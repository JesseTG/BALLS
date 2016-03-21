#ifndef MATRIXPROPERTIES_HPP
#define MATRIXPROPERTIES_HPP

#include <QObject>
#include <QString>
#include <QPropertyEditor/Property.h>

#include <glm/fwd.hpp>

#include "ui/property/MatrixProperty.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"

namespace balls {

using namespace glm;

//==============================================================================
// Float matrices
//==============================================================================

extern template class MatrixProperty<tmat2x2, Vec2Property>;
extern template class MatrixProperty<tmat2x3, Vec3Property>;
extern template class MatrixProperty<tmat2x4, Vec4Property>;
extern template class MatrixProperty<tmat3x2, Vec2Property>;
extern template class MatrixProperty<tmat3x3, Vec3Property>;
extern template class MatrixProperty<tmat3x4, Vec4Property>;
extern template class MatrixProperty<tmat4x2, Vec2Property>;
extern template class MatrixProperty<tmat4x3, Vec3Property>;
extern template class MatrixProperty<tmat4x4, Vec4Property>;

// 2-column matrices ///////////////////////////////////////////////////////////
class Mat2Property : public MatrixProperty<tmat2x2, Vec2Property> {
  Q_OBJECT

  Q_PROPERTY(vec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec2 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x2, Vec2Property>::MatrixProperty;
};

class Mat2x3Property : public MatrixProperty<tmat2x3, Vec3Property> {
  Q_OBJECT

  Q_PROPERTY(vec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec3 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x3, Vec3Property>::MatrixProperty;
};

class Mat2x4Property : public MatrixProperty<tmat2x4, Vec4Property> {
  Q_OBJECT

  Q_PROPERTY(vec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec4 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x4, Vec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////

// 3-column matrices ///////////////////////////////////////////////////////////
class Mat3x2Property : public MatrixProperty<tmat3x2, Vec2Property> {
  Q_OBJECT

  Q_PROPERTY(vec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec2 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec2 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x2, Vec2Property>::MatrixProperty;
};

class Mat3Property : public MatrixProperty<tmat3x3, Vec3Property> {
  Q_OBJECT

  Q_PROPERTY(vec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec3 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec3 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x3, Vec3Property>::MatrixProperty;
};

class Mat3x4Property : public MatrixProperty<tmat3x4, Vec4Property> {
  Q_OBJECT

  Q_PROPERTY(vec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec4 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec4 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x4, Vec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////

// 4-column matrices ///////////////////////////////////////////////////////////
class Mat4x2Property : public MatrixProperty<tmat4x2, Vec2Property> {
  Q_OBJECT

  Q_PROPERTY(vec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec2 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec2 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(vec2 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x2, Vec2Property>::MatrixProperty;
};

class Mat4x3Property : public MatrixProperty<tmat4x3, Vec3Property> {
  Q_OBJECT

  Q_PROPERTY(vec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec3 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec3 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(vec3 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x3, Vec3Property>::MatrixProperty;
};

class Mat4Property : public MatrixProperty<tmat4x4, Vec4Property> {
  Q_OBJECT

  Q_PROPERTY(vec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(vec4 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(vec4 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(vec4 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x4, Vec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////



//==============================================================================
// Double matrices
//==============================================================================

extern template class MatrixProperty<tmat2x2, DVec2Property>;
extern template class MatrixProperty<tmat2x3, DVec3Property>;
extern template class MatrixProperty<tmat2x4, DVec4Property>;
extern template class MatrixProperty<tmat3x2, DVec2Property>;
extern template class MatrixProperty<tmat3x3, DVec3Property>;
extern template class MatrixProperty<tmat3x4, DVec4Property>;
extern template class MatrixProperty<tmat4x2, DVec2Property>;
extern template class MatrixProperty<tmat4x3, DVec3Property>;
extern template class MatrixProperty<tmat4x4, DVec4Property>;

// 2-column matrices ///////////////////////////////////////////////////////////
class DMat2Property : public MatrixProperty<tmat2x2, DVec2Property> {
  Q_OBJECT

  Q_PROPERTY(dvec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec2 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x2, DVec2Property>::MatrixProperty;
};

class DMat2x3Property : public MatrixProperty<tmat2x3, DVec3Property> {
  Q_OBJECT

  Q_PROPERTY(dvec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec3 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x3, DVec3Property>::MatrixProperty;
};

class DMat2x4Property : public MatrixProperty<tmat2x4, DVec4Property> {
  Q_OBJECT

  Q_PROPERTY(dvec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec4 col1 READ _gety WRITE _sety STORED false FINAL)

public:
  using MatrixProperty<tmat2x4, DVec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////

// 3-column matrices ///////////////////////////////////////////////////////////
class DMat3x2Property : public MatrixProperty<tmat3x2, DVec2Property> {
  Q_OBJECT

  Q_PROPERTY(dvec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec2 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec2 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x2, DVec2Property>::MatrixProperty;
};

class DMat3Property : public MatrixProperty<tmat3x3, DVec3Property> {
  Q_OBJECT

  Q_PROPERTY(dvec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec3 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec3 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x3, DVec3Property>::MatrixProperty;
};

class DMat3x4Property : public MatrixProperty<tmat3x4, DVec4Property> {
  Q_OBJECT

  Q_PROPERTY(dvec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec4 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec4 col2 READ _getz WRITE _setz STORED false FINAL)

public:
  using MatrixProperty<tmat3x4, DVec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////

// 4-column matrices ///////////////////////////////////////////////////////////
class DMat4x2Property : public MatrixProperty<tmat4x2, DVec2Property> {
  Q_OBJECT

  Q_PROPERTY(dvec2 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec2 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec2 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(dvec2 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x2, DVec2Property>::MatrixProperty;
};

class DMat4x3Property : public MatrixProperty<tmat4x3, DVec3Property> {
  Q_OBJECT

  Q_PROPERTY(dvec3 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec3 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec3 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(dvec3 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x3, DVec3Property>::MatrixProperty;
};

class DMat4Property : public MatrixProperty<tmat4x4, DVec4Property> {
  Q_OBJECT

  Q_PROPERTY(dvec4 col0 READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(dvec4 col1 READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(dvec4 col2 READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(dvec4 col3 READ _getw WRITE _setw STORED false FINAL)

public:
  using MatrixProperty<tmat4x4, DVec4Property>::MatrixProperty;
};
// /////////////////////////////////////////////////////////////////////////////

}

#endif // MATRIXPROPERTIES_HPP

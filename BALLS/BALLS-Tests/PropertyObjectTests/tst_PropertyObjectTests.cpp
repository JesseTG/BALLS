#include "precompiled.hpp"

#include <memory>

#include "util/MetaTypeConverters.hpp"
#include "ui/property/MatrixProperties.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"

#include <QString>
#include <QtTest>
#include <QMetaType>
#include <QVariant>

using namespace balls;

// NOTE: Properties are deleted within the unit tests.  THIS IS OK!  Deleting
// a QObject removes it from its parent, and all of these Property objects are
// made children of an object.  BE SMART WITH DELETE!
class PropertyObjectTests : public QObject {
  Q_OBJECT

private:
  QObject object;

  template<class Prop>
  inline void changeValue_addProp(const typename Prop::Type& t) noexcept {
    const char* name = QMetaType::typeName(qMetaTypeId<typename Prop::Type>());
    QTest::newRow(name)
        << static_cast<Property*>(new Prop(name, &object, &object))
    << QVariant::fromValue(t);
  }

  template<class Prop>
  inline void fromString_add(const QString& input,
                             const typename Prop::Type& expected) noexcept {
    const char* name = QMetaType::typeName(qMetaTypeId<typename Prop::Type>());

    QTest::newRow(name)
        << static_cast<Property*>(new Prop(name, &object, &object))
    << input
    << QVariant::fromValue(expected);
  }

  template<class Prop>
  inline void fromString_add(const QString& name, const QString& input,
                             const typename Prop::Type& expected) noexcept {
    QTest::newRow(qPrintable(name))
        << static_cast<Property*>(new Prop("property", &object, &object))
    << input
    << QVariant::fromValue(expected);
  }

  template<class Prop>
  inline void changeProps_add(
    const QString& name,
    const typename Prop::Type& input,
    const QVariantHash& changes,
    const typename Prop::Type& expected
  ) noexcept {
    QTest::newRow(qPrintable(name))
        << static_cast<Property*>(new Prop("property", &object, &object))
    << QVariant::fromValue(input)
    << changes
    << QVariant::fromValue(expected);
  }
private slots /* general */:
  void initTestCase();

private slots /* functionality */:
  void changeValue();
  void changeValue_data();

  void changeIndividualProperties();
  void changeIndividualProperties_data();

  void fromString();
  void fromString_data();
};

void PropertyObjectTests::initTestCase() {
  balls::registerMetaTypeConverters();
}

void PropertyObjectTests::changeValue_data() {
  QTest::addColumn<Property*>("property");
  QTest::addColumn<QVariant>("value");

  changeValue_addProp<Vec2Property>(vec2(1, 3));
  changeValue_addProp<IVec2Property>(ivec2(4, 5));
  changeValue_addProp<BVec2Property>(bvec2(false, true));
  changeValue_addProp<DVec2Property>(dvec2(7, 8));
  changeValue_addProp<UVec2Property>(uvec2(6, 1));

  changeValue_addProp<Vec3Property>(vec3(6, 1, 3.5));
  changeValue_addProp<IVec3Property>(ivec3(4, 5, -1));
  changeValue_addProp<BVec3Property>(bvec3(false, true, false));
  changeValue_addProp<DVec3Property>(dvec3(7, 8, 5.556));
  changeValue_addProp<UVec3Property>(uvec3(6, 1, 12));

  changeValue_addProp<Vec4Property>(vec4(6, 7, 1, 3));
  changeValue_addProp<IVec4Property>(ivec4(4, 5, 43, 56));
  changeValue_addProp<BVec4Property>(bvec4(false, true, true, true));
  changeValue_addProp<DVec4Property>(dvec4(7, 8, -56.0, 12));
  changeValue_addProp<UVec4Property>(uvec4(6, 1, 6243, 0));

  changeValue_addProp<Mat2Property>(mat2(1, 2, 3, 4));
  changeValue_addProp<Mat2x3Property>(mat2x3(5));
  changeValue_addProp<Mat2x4Property>(mat2x4(0));
  changeValue_addProp<Mat3x2Property>(mat3x2(77));
  changeValue_addProp<Mat3Property>(mat3(6));
  changeValue_addProp<Mat3x4Property>(mat3x4(-3));
  changeValue_addProp<Mat4x2Property>(mat4x2(91));
  changeValue_addProp<Mat4x3Property>(mat4x3(55));
  changeValue_addProp<Mat4Property>(mat4(12));

  changeValue_addProp<DMat2Property>(dmat2(1, 2, 3, 4));
  changeValue_addProp<DMat2x3Property>(dmat2x3(5));
  changeValue_addProp<DMat2x4Property>(dmat2x4(0));
  changeValue_addProp<DMat3x2Property>(dmat3x2(77));
  changeValue_addProp<DMat3Property>(dmat3(6));
  changeValue_addProp<DMat3x4Property>(dmat3x4(-3));
  changeValue_addProp<DMat4x2Property>(dmat4x2(91));
  changeValue_addProp<DMat4x3Property>(dmat4x3(55));
  changeValue_addProp<DMat4Property>(dmat4(12));
}

void PropertyObjectTests::changeValue() {
  QFETCH(Property*, property);
  QFETCH(QVariant, value);

  property->setValue(value);

  QVariant actual = property->value();

  delete property;

  QCOMPARE(actual, value);
}

void PropertyObjectTests::changeIndividualProperties_data() {
  QTest::addColumn<Property*>("property");
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QVariantHash>("changes");
  QTest::addColumn<QVariant>("expected");

  changeProps_add<Vec2Property>("vec2", vec2(1, 5), {{"y", 7}}, vec2(1, 7));
  changeProps_add<Vec3Property>("vec3", vec3(1, 2, 3), {{"x", 0}}, vec3(0, 2, 3));
  changeProps_add<Vec4Property>(
  "vec4", vec4(0, 0, 0, 0), {{"x", 1}, {"y", 4}, {"z", 6}, {"w", 8}}, vec4(1, 4,
  6, 8)
  );
  changeProps_add<Mat2Property>(
  "mat2", mat2(4), {{"col0", QVariant::fromValue(vec2(5, 5))}}, mat2(5, 5, 0, 4)
  );
  changeProps_add<Vec2Property>(
  "lowercase only", vec2(0, 5), {{"X", 7}}, vec2(0, 5)
  );
  changeProps_add<Vec2Property>(
  "uint -> float", vec2(5, 7), {{"y", 10u}}, vec2(5, 10)
  );
  changeProps_add<BVec4Property>(
    "various -> bool",
    bvec4(true, false, false, true),
  {{"x", 5}, {"y", 0u}, {"z", -6.7f}, {"w", -0.0}},
  bvec4(true, false, true, false)
  );
}

void PropertyObjectTests::changeIndividualProperties() {
  QFETCH(Property*, property);
  QFETCH(QVariant, input);
  QFETCH(QVariantHash, changes);
  QFETCH(QVariant, expected);

  property->setValue(input);

  for (const QString& key : changes.keys()) {
    property->setProperty(qPrintable(key), changes[key]);
  }

  QVariant actual = property->value();

  delete property;

  QCOMPARE(actual, expected);
}


void PropertyObjectTests::fromString() {
  QFETCH(Property*, property);
  QFETCH(QString, input);
  QFETCH(QVariant, expected);

  property->setValue(input);

  QVariant actual = property->value();

  delete property;

  QCOMPARE(actual, expected);
}

void PropertyObjectTests::fromString_data() {
  QTest::addColumn<Property*>("property");
  QTest::addColumn<QString>("input");
  QTest::addColumn<QVariant>("expected");

  fromString_add<Vec2Property>("1, 3", vec2(1, 3));
  fromString_add<IVec2Property>("0, -6", ivec2(0, -6));
  fromString_add<DVec2Property>("3.5, 3", dvec2(3.5, 3));
  fromString_add<BVec2Property>("true, true", bvec2(true, true));
  fromString_add<UVec2Property>("4, 6", uvec2(4, 6));

  fromString_add<Vec3Property>("1, 3, 5", vec3(1, 3, 5));
  fromString_add<IVec3Property>("0, -6, 12", ivec3(0, -6, 12));
  fromString_add<DVec3Property>("3.5, 3, 5", dvec3(3.5, 3, 5));
  fromString_add<BVec3Property>("true, true, false", bvec3(true, true, false));
  fromString_add<UVec3Property>("4, 6, 7", uvec3(4, 6, 7));

  fromString_add<Vec4Property>("1, 3, 5, 5", vec4(1, 3, 5, 5));
  fromString_add<IVec4Property>("0, -6, 12, 1", ivec4(0, -6, 12, 1));
  fromString_add<DVec4Property>("3.5, 3, 5, 0", dvec4(3.5, 3, 5, 0));
  fromString_add<BVec4Property>(
    "true, true, false, true", bvec4(true, true, false, true)
  );
  fromString_add<UVec4Property>("4, 6, 7, 8", uvec4(4, 6, 7, 8));

  fromString_add<Vec4Property>("no spaces", "3,3,3,3", vec4(3, 3, 3, 3));

  fromString_add<BVec4Property>(
    "bools from numbers", "1, 0, -1, 12", bvec4(true, false, true, true)
  );
  fromString_add<BVec3Property>(
    "bools from numbers 2", "5, 1, 0", bvec3(true, true, false)
  );

  fromString_add<Vec4Property>(
    "lots of space", "   4,    0   , 12 , 33 ", vec4(4, 0, 12, 33)

  ); // For some reason, I can't put this above "bools from numbers"; its data
  // spills over
  fromString_add<IVec3Property>(
    "5, 1, 0", ivec3(5, 1, 0)
  );
  fromString_add<BVec4Property>(
    "case insensitive bools", "TRUE, fAlSe, TRuE, falsE", bvec4(1, 0, 1, 0)
  );
  fromString_add<Vec2Property>("trailing commas OK", "0, 2,", vec2(0, 2));
  fromString_add<Vec2Property>(
    "too many numbers given", "10, 23, 14, 15", vec2(10, 23)
  );
  fromString_add<Vec2Property>(
    "more than 4 numbers given", "1, 2, 3, 4, 5, 6, 7", vec2(1, 2)
  );
  fromString_add<Vec4Property>(
    "too few numbers given", "5, 6", vec4(5, 6, 0, 0)
  );
  fromString_add<Vec4Property>("empty input", "", vec4(0, 0, 0, 0));
  fromString_add<Vec4Property>("only whitespace", "     ", vec4(0, 0, 0, 0));
  fromString_add<Vec4Property>("commas, no numbers", " , ,,", vec4(0, 0, 0, 0));
  fromString_add<Vec4Property>("commas misplaced", ",2,,3", vec4(0, 2, 0, 3));
  fromString_add<Vec3Property>(
    "words as input", "france, spain, china", vec3(0, 0, 0)
  );
  fromString_add<Vec3Property>("some words", "cheese, 2, 5", vec3(0, 2, 5));
  fromString_add<Vec2Property>("square brackets OK", "[ 1, 4]", vec2(1, 4));
  fromString_add<Vec2Property>("parens OK", "(5, 6)", vec2(5, 6));
  fromString_add<BVec2Property>(
    "curly braces OK", "{true,false}", bvec2(true, false)
  );
  fromString_add<Vec2Property>("angle brackets OK", "<8,0>", vec2(8, 0));
  fromString_add<Vec3Property>("mismatched brackets", "(1,8, 7>", vec3(1, 8, 7));
  // TODO: Support scientific notation for floats
  // TODO: Support hexadecimal/binary/octal for integers
}


QTEST_APPLESS_MAIN(PropertyObjectTests)

#include "tst_PropertyObjectTests.moc"

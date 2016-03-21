#include "precompiled.hpp"
#include "util/MetaTypeConverters.hpp"

#include <QString>
#include <QtTest>
#include <QVariant>
#include <QJsonValue>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_query.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/type_trait.hpp>

using namespace glm;

// To shorten tests
template<class T>
inline QVariant var(const T& t) noexcept {
  return QVariant::fromValue(t);
}

void addVec2Data() noexcept {
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QJsonValue::Type>("type");

  QTest::newRow("bvec2") << var(bvec2 {false, false}) << QJsonValue::Bool;
  QTest::newRow("dvec2") << var(dvec2 {0.7, 34.5432}) << QJsonValue::Double;
  QTest::newRow("ivec2") << var(ivec2 {1337, 0}) << QJsonValue::Double;
  QTest::newRow("vec2") << var(vec2 {1.5f, -0.0f}) << QJsonValue::Double;
  QTest::newRow("uvec2") << var(uvec2 { 14u, 78u}) << QJsonValue::Double;
}

void addVec3Data() noexcept {
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QJsonValue::Type>("type");

  QTest::newRow("bvec3") << var(bvec3 {false, false, true}) << QJsonValue::Bool;
  QTest::newRow("dvec3") << var(dvec3 {0.7, 34.5432, 1e8}) << QJsonValue::Double;
  QTest::newRow("ivec3") << var(ivec3 {1337, 0, 43}) << QJsonValue::Double;
  QTest::newRow("vec3") << var(vec3 {.5f, 1.5f, 3e7f}) << QJsonValue::Double;
  QTest::newRow("uvec3") << var(uvec3 {0u, 14u, 78u}) << QJsonValue::Double;
}

void addVec4Data() noexcept {
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QJsonValue::Type>("type");

  QTest::newRow("bvec4") << var(bvec4 {true, false, false, true}) << QJsonValue::Bool;
  QTest::newRow("dvec4") << var(dvec4 {99., 15.43521, 0.004, 4e-7}) << QJsonValue::Double;
  QTest::newRow("ivec4") << var(ivec4 {21, 23, 0, -5553}) << QJsonValue::Double;
  QTest::newRow("vec4") << var(vec4 {1.4f, 45.f, -0.0f, 1e9f}) << QJsonValue::Double;
  QTest::newRow("uvec4") << var(uvec4 {0u, 14u, 78u, 9755u}) << QJsonValue::Double;
}

void addQuatData() noexcept {
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QJsonValue::Type>("type");

  QTest::newRow("dquat") << var(dquat {99., 15.43521, 0.004, 4e-7}) << QJsonValue::Double;
  QTest::newRow("quat") << var(quat {1.4f, 45.f, -0.0f, 1e9f}) << QJsonValue::Double;
}

void addMatData() noexcept {
  QTest::addColumn<QVariant>("input");
  QTest::addColumn<QJsonValue::Type>("type");
  QTest::addColumn<int>("rows");
  QTest::addColumn<int>("cols");

  // The compiler is subbing these static const variables in for constants,
  // but that means they don't have an address anywhere; I'd better send a PR
  // to GLM later
  // TODO: Send PR to GLM that forces these constants to be compiled in
  QTest::newRow("mat2x2") << var(mat2x2(10)) << QJsonValue::Array << (int)type<tmat2x2>::rows << (int)type<tmat2x2>::cols;
  QTest::newRow("mat2x3") << var(mat2x3(2)) << QJsonValue::Array << (int)type<tmat2x3>::rows << (int)type<tmat2x3>::cols;
  QTest::newRow("mat2x4") << var(mat2x4(3)) << QJsonValue::Array << (int)type<tmat2x4>::rows << (int)type<tmat2x4>::cols;
  QTest::newRow("mat3x2") << var(mat3x2(4)) << QJsonValue::Array << (int)type<tmat3x2>::rows << (int)type<tmat3x2>::cols;
  QTest::newRow("mat3x3") << var(mat3x3(5)) << QJsonValue::Array << (int)type<tmat3x3>::rows << (int)type<tmat3x3>::cols;
  QTest::newRow("mat3x4") << var(mat3x4(6)) << QJsonValue::Array << (int)type<tmat3x4>::rows << (int)type<tmat3x4>::cols;
  QTest::newRow("mat4x2") << var(mat4x2(7)) << QJsonValue::Array << (int)type<tmat4x2>::rows << (int)type<tmat4x2>::cols;
  QTest::newRow("mat4x3") << var(mat4x3(8)) << QJsonValue::Array << (int)type<tmat4x3>::rows << (int)type<tmat4x3>::cols;
  QTest::newRow("mat4x4") << var(mat4x4(9)) << QJsonValue::Array << (int)type<tmat4x4>::rows << (int)type<tmat4x4>::cols;

  QTest::newRow("dmat2x2") << var(dmat2x2(10)) << QJsonValue::Array << (int)type<tmat2x2>::rows << (int)type<tmat2x2>::cols;
  QTest::newRow("dmat2x3") << var(dmat2x3(2)) << QJsonValue::Array << (int)type<tmat2x3>::rows << (int)type<tmat2x3>::cols;
  QTest::newRow("dmat2x4") << var(dmat2x4(3)) << QJsonValue::Array << (int)type<tmat2x4>::rows << (int)type<tmat2x4>::cols;
  QTest::newRow("dmat3x2") << var(dmat3x2(4)) << QJsonValue::Array << (int)type<tmat3x2>::rows << (int)type<tmat3x2>::cols;
  QTest::newRow("dmat3x3") << var(dmat3x3(5)) << QJsonValue::Array << (int)type<tmat3x3>::rows << (int)type<tmat3x3>::cols;
  QTest::newRow("dmat3x4") << var(dmat3x4(6)) << QJsonValue::Array << (int)type<tmat3x4>::rows << (int)type<tmat3x4>::cols;
  QTest::newRow("dmat4x2") << var(dmat4x2(7)) << QJsonValue::Array << (int)type<tmat4x2>::rows << (int)type<tmat4x2>::cols;
  QTest::newRow("dmat4x3") << var(dmat4x3(8)) << QJsonValue::Array << (int)type<tmat4x3>::rows << (int)type<tmat4x3>::cols;
  QTest::newRow("dmat4x4") << var(dmat4x4(9)) << QJsonValue::Array << (int)type<tmat4x4>::rows << (int)type<tmat4x4>::cols;
}

void addVectorJsonData() noexcept {
  QTest::addColumn<QJsonObject>("input");

  QTest::newRow("empty") << QJsonObject();
  QTest::newRow("all null") << QJsonObject {
    { "x", {} },
    { "y", {} },
    { "z", {} },
    { "w", {} },
  };
  QTest::newRow("all ints") << QJsonObject {
    { "x", 1 },
    { "y", 7 },
    { "z", 42 },
    { "w", 56 },
  };
  QTest::newRow("all floats") << QJsonObject {
    { "x", 0.0f },
    { "y", 6.7543f },
    { "z", 77.21f },
    { "w", -531.043f },
  };
  QTest::newRow("all bools") << QJsonObject {
    { "x", true},
    { "y", false },
    { "z", true },
    { "w", true },
  };
  QTest::newRow("all doubles") << QJsonObject {
    { "x", 55.4},
    { "y", 101.9 },
    { "z", 99.88},
    { "w", 1.6e8 },
  };
  QTest::newRow("all uints") << QJsonObject {
    { "x", static_cast<int>(54u)},
    { "y", static_cast<int>(0u) },
    { "z", static_cast<int>(1156u) },
    { "w", static_cast<int>(1443u) },
  };

  QTest::newRow("only x") << QJsonObject {
    { "x", 65.2 },
  };
  QTest::newRow("only xz") << QJsonObject {
    { "x", 6 },
    { "z", 3 },
  };
  QTest::newRow("hetero") << QJsonObject {
    {"x", true},
    {"y", 5},
    {"z", 6.678},
    {"w", 44.5f},
  };
  QTest::newRow("only xw") << QJsonObject {
    {"x", true},
    {"w", false},
  };
  QTest::newRow("hetero with null") << QJsonObject {
    { "x", {} },
    { "y", 57 },
    { "z", 0 },
    { "w", {} },
  };
  QTest::newRow("no caps") << QJsonObject {
    { "X", 6 },
  };
}

void addJsonArrayData() noexcept {
  QTest::addColumn<QJsonArray>("input");
  QTest::addColumn<mat4>("expected");

  QTest::newRow("empty") << QJsonArray() << mat4();

  QTest::newRow("contains empties") << QJsonArray {
    QJsonArray(),
    QJsonArray(),
    QJsonArray(),
    QJsonArray(),
  } << mat4();

  QTest::newRow("zeroes") << QJsonArray {
    QJsonArray { 0, 0, 0, 0 },
    QJsonArray { 0, 0, 0, 0 },
    QJsonArray { 0, 0, 0, 0 },
    QJsonArray { 0, 0, 0, 0 },
  } << mat4({
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
  });

  QTest::newRow("identity 2x2") << QJsonArray {
    QJsonArray { 1, 0 },
    QJsonArray { 0, 1 },
  } << mat4(mat2 {
    { 1, 0 },
    { 0, 1 },
  });

  QTest::newRow("identity 3x3") << QJsonArray {
    QJsonArray { 1, 0, 0 },
    QJsonArray { 0, 1, 0 },
    QJsonArray { 0, 0, 1 },
  } << mat4(mat3 {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 },
  });

  QTest::newRow("identity 4x4") << QJsonArray {
    QJsonArray { 1, 0, 0, 0 },
    QJsonArray { 0, 1, 0, 0 },
    QJsonArray { 0, 0, 1, 0 },
    QJsonArray { 0, 0, 0, 1 },
  } << mat4();

}

class TestJsonConversions : public QObject {
  Q_OBJECT

public:
private slots:
  void initTestCase();

  void objectValueConversion();
  void objectValueConversion_data() {
    addVec2Data();
    addVec3Data();
    addVec4Data();
    addQuatData();
  }

  void arrayValueConversion();
  void arrayValueConversion_data() {
    addMatData();
  }

  void fromVec2();
  void fromVec2_data() { addVec2Data(); }

  void fromVec3();
  void fromVec3_data() { addVec3Data(); }

  void fromVec4();
  void fromVec4_data() {
    addVec4Data();
    addQuatData();
  }

  void toVec2();
  void toVec2_data() { addVectorJsonData(); }

  void toVec3();
  void toVec3_data() { addVectorJsonData(); }

  void toVec4();
  void toVec4_data() { addVectorJsonData(); }

  void fromMat();
  void fromMat_data() { addMatData(); }

  void toMat();
  void toMat_data() { addJsonArrayData(); }
};

void TestJsonConversions::initTestCase() {
  balls::registerMetaTypeConverters();
}

Q_DECLARE_METATYPE(QJsonValue::Type)

void TestJsonConversions::objectValueConversion() {
  QFETCH(QVariant, input);

  QJsonValue val = input.toJsonValue();
  QJsonObject obj = input.toJsonObject();

  QCOMPARE(val.type(), QJsonValue::Object);
  QCOMPARE(val.toObject(), obj);
  QCOMPARE(QJsonValue(obj), val);
  QCOMPARE(input.value<QJsonValue>(), val);
  QCOMPARE(input.value<QJsonObject>(), obj);
}

void TestJsonConversions::arrayValueConversion() {
  QFETCH(QVariant, input);
  QFETCH(QJsonValue::Type, type);
  QFETCH(int, rows);
  QFETCH(int, cols);

  QJsonValue val = input.toJsonValue();
  QJsonArray arr = input.toJsonArray();

  QCOMPARE(val.type(), QJsonValue::Array);
  QCOMPARE(val.toArray(), arr);
  QCOMPARE(QJsonValue(arr), val);
  QCOMPARE(input.value<QJsonValue>(), val);
  QCOMPARE(input.value<QJsonArray>(), arr);
}

void TestJsonConversions::fromVec2() {
  QFETCH(QVariant, input);
  QFETCH(QJsonValue::Type, type);

  QJsonObject obj = input.toJsonObject();

  QVERIFY2(obj.contains("x"), "No x component found");
  QVERIFY2(obj.contains("y"), "No y component found");
  QCOMPARE(obj.size(), 2);
  QCOMPARE(obj["x"].type(), type);
  QCOMPARE(obj["y"].type(), type);
}

void TestJsonConversions::fromVec3() {
  QFETCH(QVariant, input);
  QFETCH(QJsonValue::Type, type);

  QJsonObject obj = input.toJsonObject();

  QVERIFY2(obj.contains("x"), "No x component found");
  QVERIFY2(obj.contains("y"), "No y component found");
  QVERIFY2(obj.contains("z"), "No z component found");
  QCOMPARE(obj.size(), 3);
  QCOMPARE(obj["x"].type(), type);
  QCOMPARE(obj["y"].type(), type);
  QCOMPARE(obj["z"].type(), type);
}

void TestJsonConversions::fromVec4() {
  QFETCH(QVariant, input);
  QFETCH(QJsonValue::Type, type);

  QJsonObject obj = input.toJsonObject();

  QVERIFY2(obj.contains("x"), "No x component found");
  QVERIFY2(obj.contains("y"), "No y component found");
  QVERIFY2(obj.contains("z"), "No z component found");
  QVERIFY2(obj.contains("w"), "No w component found");
  QCOMPARE(obj.size(), 4);
  QCOMPARE(obj["x"].type(), type);
  QCOMPARE(obj["y"].type(), type);
  QCOMPARE(obj["z"].type(), type);
  QCOMPARE(obj["w"].type(), type);
}

template<int I, class BVec, class DVec, class IVec, class Vec, class UVec>
void testConversion(
  const BVec& bvec,
  const DVec& dvec,
  const IVec& ivec,
  const Vec& vec,
  const UVec& uvec,
  const QJsonValue& json
) {
  switch (json.type()) {
  // Undefined or invalid values should just be 0
  case QJsonValue::Undefined:
  case QJsonValue::Object:
  case QJsonValue::Array:
  case QJsonValue::Null:
    QCOMPARE(bvec[I], false);
    QCOMPARE(dvec[I], 0.0);
    QCOMPARE(ivec[I], 0);
    QCOMPARE(vec[I], 0.0f);
    QCOMPARE(uvec[I], 0u);
    break;

  case QJsonValue::Bool:
    QCOMPARE(bvec[I], json.toBool());
    QCOMPARE(dvec[I], double(json.toBool()));
    QCOMPARE(ivec[I], int(json.toBool()));
    QCOMPARE(vec[I], float(json.toBool()));
    QCOMPARE(uvec[I], uint(json.toBool()));
    break;

  case QJsonValue::Double:
    QCOMPARE(bvec[I], bool(qRound(json.toDouble())));
    QCOMPARE(dvec[I], json.toDouble());
    QCOMPARE(ivec[I], int(qRound(json.toDouble())));
    QCOMPARE(vec[I], float(json.toDouble()));
    QCOMPARE(uvec[I], uint(qRound(json.toDouble())));
    break;

  case QJsonValue::String:
    QCOMPARE(bvec[I], bool(json.toString().toInt()));
    QCOMPARE(dvec[I], json.toString().toDouble());
    QCOMPARE(ivec[I], json.toString().toInt());
    QCOMPARE(vec[I], json.toString().toFloat());
    QCOMPARE(uvec[I], json.toString().toUInt());
    break;

  default:
    QFAIL("Unknown QJsonValue::Type; what the fuck?");
  }
}

void TestJsonConversions::toVec2() {
  QFETCH(QJsonObject, input);

  QVariant var = input;

  bvec2 bvec = var.value<bvec2>();
  dvec2 dvec = var.value<dvec2>();
  ivec2 ivec = var.value<ivec2>();
  vec2 vec = var.value<vec2>();
  uvec2 uvec = var.value<uvec2>();

  QJsonValue x = input["x"];
  QJsonValue y = input["y"];

  testConversion<0>(bvec, dvec, ivec, vec, uvec, x);
  testConversion<1>(bvec, dvec, ivec, vec, uvec, y);
}

void TestJsonConversions::toVec3() {
  QFETCH(QJsonObject, input);

  QVariant var = input;

  bvec3 bvec = var.value<bvec3>();
  dvec3 dvec = var.value<dvec3>();
  ivec3 ivec = var.value<ivec3>();
  vec3 vec = var.value<vec3>();
  uvec3 uvec = var.value<uvec3>();

  QJsonValue x = input["x"];
  QJsonValue y = input["y"];
  QJsonValue z = input["z"];

  testConversion<0>(bvec, dvec, ivec, vec, uvec, x);
  testConversion<1>(bvec, dvec, ivec, vec, uvec, y);
  testConversion<2>(bvec, dvec, ivec, vec, uvec, z);
}

void TestJsonConversions::toVec4() {
  QFETCH(QJsonObject, input);

  QVariant var = input;

  bvec4 bvec = var.value<bvec4>();
  dvec4 dvec = var.value<dvec4>();
  ivec4 ivec = var.value<ivec4>();
  vec4 vec = var.value<vec4>();
  uvec4 uvec = var.value<uvec4>();
  // TODO: Add quaternions to this test

  QJsonValue x = input["x"];
  QJsonValue y = input["y"];
  QJsonValue z = input["z"];
  QJsonValue w = input["w"];

  testConversion<0>(bvec, dvec, ivec, vec, uvec, x);
  testConversion<1>(bvec, dvec, ivec, vec, uvec, y);
  testConversion<2>(bvec, dvec, ivec, vec, uvec, z);
  testConversion<3>(bvec, dvec, ivec, vec, uvec, w);
}

void TestJsonConversions::fromMat() {
  QFETCH(QVariant, input);
  QFETCH(glm::length_t, rows);
  QFETCH(glm::length_t, cols);

  QJsonArray arr = input.toJsonArray();

  QCOMPARE(arr.size(), cols);

  for (const QJsonValue& col : arr) {
    QCOMPARE(col.type(), QJsonValue::Array);
    QCOMPARE(col.toArray().size(), rows);
  }
}

void TestJsonConversions::toMat() {
  QFETCH(QJsonArray, input);
  QFETCH(mat4x4, expected);

  QVariant v = input;
  mat2x2 m22 = v.value<mat2x2>();
  mat2x3 m23 = v.value<mat2x3>();
  mat2x4 m24 = v.value<mat2x4>();
  mat3x2 m32 = v.value<mat3x2>();
  mat3x3 m33 = v.value<mat3x3>();
  mat3x4 m34 = v.value<mat3x4>();
  mat4x2 m42 = v.value<mat4x2>();
  mat4x3 m43 = v.value<mat4x3>();
  mat4x4 m44 = v.value<mat4x4>();

  dmat2x2 dm22 = v.value<dmat2x2>();
  dmat2x3 dm23 = v.value<dmat2x3>();
  dmat2x4 dm24 = v.value<dmat2x4>();
  dmat3x2 dm32 = v.value<dmat3x2>();
  dmat3x3 dm33 = v.value<dmat3x3>();
  dmat3x4 dm34 = v.value<dmat3x4>();
  dmat4x2 dm42 = v.value<dmat4x2>();
  dmat4x3 dm43 = v.value<dmat4x3>();
  dmat4x4 dm44 = v.value<dmat4x4>();

  QCOMPARE(m22, mat2x2(expected));
  QCOMPARE(m23, mat2x3(expected));
  QCOMPARE(m24, mat2x4(expected));
  QCOMPARE(m32, mat3x2(expected));
  QCOMPARE(m33, mat3x3(expected));
  QCOMPARE(m34, mat3x4(expected));
  QCOMPARE(m42, mat4x2(expected));
  QCOMPARE(m43, mat4x3(expected));
  QCOMPARE(m44, mat4x4(expected));

  QCOMPARE(dm22, dmat2x2(expected));
  QCOMPARE(dm23, dmat2x3(expected));
  QCOMPARE(dm24, dmat2x4(expected));
  QCOMPARE(dm32, dmat3x2(expected));
  QCOMPARE(dm33, dmat3x3(expected));
  QCOMPARE(dm34, dmat3x4(expected));
  QCOMPARE(dm42, dmat4x2(expected));
  QCOMPARE(dm43, dmat4x3(expected));
  QCOMPARE(dm44, dmat4x4(expected));
}


QTEST_APPLESS_MAIN(TestJsonConversions)

#include "tst_TestJSONConversionsTest.moc"

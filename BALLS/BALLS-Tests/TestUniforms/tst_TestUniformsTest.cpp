#include "precompiled.hpp"
#include "util/MetaTypeConverters.hpp"
#include "util/TypeInfo.hpp"

#include <initializer_list>
#include <utility>
#include <QString>
#include <QtTest>
#include <QList>
#include <QCoreApplication>
#include "ui/Uniforms.hpp"
#include "util/Logging.hpp"

using std::tuple;
using std::get;
using std::initializer_list;
using namespace glm;
using balls::Uniforms;
using balls::UniformCollection;
using balls::UniformInfo;

struct UniformTestDatum {
  template<class T>
  UniformTestDatum(const UniformInfo& u, const T& v) :
    uniform(u), value(QVariant::fromValue(v)) {}
  UniformInfo uniform;
  QVariant value;
};

struct UniformTestData {
  UniformTestData() = default;

  UniformTestData(const initializer_list<UniformTestDatum>& init) {
    for (const UniformTestDatum& i : init) {
      uniforms.push_back(i.uniform);
      values[i.uniform.name] = i.value;
    }
  }

  UniformCollection uniforms;
  QVariantMap values;
};

Q_DECLARE_METATYPE(UniformTestData)

// TODO: Add values to the uniform test cases (to properly test conversions and
// retyped values)
class TestUniformsTest : public QObject {
  Q_OBJECT

private slots /* general testing */:
  void initTestCase();

private slots /* general functionality */:
  void receiveUniforms();
  void receiveUniforms_data();

  void filterInvalidTypes();
  void filterInvalidTypes_data();

  void filtersEvents();
  void designableIsUpdated();

private slots /* static properties (aka built-in uniforms) */:
  void elapsedTimeIncreases();
  void elapsedTimeIsUInt();
  void mouseCoordinates();
  void mouseCoordinates_data();
  void canvasSize();
  void canvasSize_data();
};

void TestUniformsTest::initTestCase() {
  QLoggingCategory::setFilterRules("uniform*=false");
  balls::registerMetaTypeConverters();
  balls::util::types::init();

  QVERIFY(balls::util::types::info.size() > 0);
  QVERIFY(QMetaType::type("vec2") != QMetaType::UnknownType);
}

void TestUniformsTest::filterInvalidTypes_data() {
  QTest::addColumn<UniformTestData>("invalid");
  QTest::addColumn<UniformTestData>("expected");

  QTest::newRow("one invalid")
  << UniformTestData {
    { {"france", 0, 1}, 0},
  }
  << UniformTestData {

  };

  QTest::newRow("multiple invalid")
  << UniformTestData {
    { {"france", 0, 1}, 0},
    { {"spain", 12, 16}, 32},
  }
  << UniformTestData {
  };

  QTest::newRow("valid at beginning")
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
    { { "bad", 17, 17 }, 32 },
    { { "nah", 21, 16 }, 12 },
  }
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
  };

  QTest::newRow("valid in middle")
  << UniformTestData {
    { { "bad", 17, 17 }, 32 },
    { { "wow", GL_INT, 1 }, 42 },
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "nah", 21, 16 }, 12 },
  }
  << UniformTestData {
    { { "wow", GL_INT, 1 }, 42 },
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
  };

  QTest::newRow("valid at end")
  << UniformTestData {
    { { "bad", 17, 17 }, 32 },
    { { "nah", 21, 16 }, 12 },
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
  }
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
  };

  QTest::newRow("valid interleaved")
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "bad", 17, 17 }, 32 },
    { { "wow", GL_INT, 1 }, 42 },
    { { "nah", 21, 16 }, 12 },
  }
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
  };

  QTest::newRow("valid at edges")
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "bad", 17, 17 }, 32 },
    { { "nah", 21, 16 }, 12 },
    { { "wow", GL_INT, 1 }, 42 },
  }
  << UniformTestData {
    { { "mat", GL_FLOAT_MAT4, 1 }, mat4() },
    { { "wow", GL_INT, 1 }, 42 },
  };
}

void TestUniformsTest::filterInvalidTypes() {
  QFETCH(UniformTestData, invalid);
  QFETCH(UniformTestData, expected);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  uniforms.receiveUniforms(invalid.uniforms);

  QCOMPARE(uniforms.uniformInfo(), expected.uniforms);
}

void TestUniformsTest::designableIsUpdated() {
  Uniforms uniforms;
  QObject object;

  object.installEventFilter(&uniforms);

  const QMetaObject* meta = uniforms.metaObject();
  QMetaProperty matrix = meta->property(meta->indexOfProperty("matrix"));
  QMetaProperty mousePos = meta->property(meta->indexOfProperty("mousePos"));

  Q_ASSERT(matrix.isValid());
  Q_ASSERT(mousePos.isValid());

  uniforms.receiveUniforms({
    UniformInfo {"matrix", GL_FLOAT_MAT4, 1}
  });

  QVERIFY(matrix.isDesignable(&uniforms));
  QVERIFY(!mousePos.isDesignable(&uniforms));

  uniforms.receiveUniforms({
    UniformInfo {"mousePos", GL_INT_VEC2, 1}
  });

  QVERIFY(!matrix.isDesignable(&uniforms));
  QVERIFY(mousePos.isDesignable(&uniforms));

  uniforms.receiveUniforms({
    UniformInfo {"matrix", GL_FLOAT_MAT4, 1},
    UniformInfo {"mousePos", GL_INT_VEC2, 1},
  });

  QVERIFY(matrix.isDesignable(&uniforms));
  QVERIFY(mousePos.isDesignable(&uniforms));

  uniforms.receiveUniforms({});

  QVERIFY(!matrix.isDesignable(&uniforms));
  QVERIFY(!mousePos.isDesignable(&uniforms));
}


void TestUniformsTest::receiveUniforms_data() {
  QTest::addColumn<UniformTestData>("before");
  QTest::addColumn<UniformTestData>("after");

  QTest::newRow("empty -> empty")
      << UniformTestData {}
      << UniformTestData {};

  QTest::newRow("empty -> one")
  << UniformTestData {
  }
  << UniformTestData {{
      { {"mat", GL_FLOAT_MAT4, 1}, mat4() }
    }
  };

  QTest::newRow("one -> empty")
  << UniformTestData {{
      { {"mat", GL_FLOAT_MAT4, 1}, mat4() }
    }
  }
  << UniformTestData {
  };

  QTest::newRow("matrix -> vector")
  << UniformTestData {{
      { {"mat", GL_FLOAT_MAT4, 1}, mat4(4) }
    }
  }
  << UniformTestData {{
      { {"mat", GL_FLOAT_VEC4, 1}, vec4(4, 0, 0, 0) }
    }
  };

  QTest::newRow("rearrange")
  << UniformTestData {{
      { {"mat", GL_DOUBLE_MAT4, 1}, dmat4()},
      { {"scale", GL_FLOAT, 1}, 1.0f},
      { {"available", GL_BOOL, 1}, true},
    }
  }
  << UniformTestData {{
      { {"available", GL_BOOL, 1}, true},
      { {"mat", GL_DOUBLE_MAT4, 1}, dmat4()},
      { {"scale", GL_FLOAT, 1}, 1.0f},
    }
  };

  QTest::newRow("rearrange and change types")
  << UniformTestData {{
      { {"mvp", GL_FLOAT_MAT3, 1}, mat3() },
      { {"color", GL_FLOAT_VEC4, 1}, vec4(0.5, 0.0, 0.0, 0.0) },
      { {"repetitions", GL_INT, 1}, 74 },
      { {"seed", GL_INT_VEC2, 1}, ivec2(16, 14)},
    }
  }
  << UniformTestData {{
      { {"color", GL_DOUBLE_VEC4, 1}, dvec4(0.5, 0.0, 0.0, 0.0) },
      { {"seed", GL_UNSIGNED_INT, 1}, 16u },
      { {"mvp", GL_FLOAT_MAT3x4, 1}, mat3x4() },
      { {"repetitions", GL_UNSIGNED_INT, 1}, 74u },
    }
  };

  QTest::newRow("unsupported types")
  << UniformTestData {{
      { {"coords", GL_FLOAT_VEC2, 1}, vec2() },
      { {"threshold", GL_FLOAT, 1}, 1.0f },
    }
  }
  << UniformTestData {{
      { {"threshold", GL_FLOAT, 1}, 1.0f },
      { {"texture", GL_SAMPLER_2D, 1}, 0 },
      { {"coords", GL_FLOAT_VEC2, 1}, vec2() },
      { {"palette", GL_INT_SAMPLER_1D, 1}, 1 },
    }
  };
}

void TestUniformsTest::receiveUniforms() {
  QFETCH(UniformTestData, before);
  QFETCH(UniformTestData, after);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  uniforms.receiveUniforms(before.uniforms);

  QCOMPARE(uniforms.uniformInfo(), before.uniforms);

  uniforms.receiveUniforms(after.uniforms);

  QCOMPARE(uniforms.uniformInfo(), after.uniforms);

  for (const UniformInfo& u : uniforms.uniformInfo()) {
    QCOMPARE(uniforms.property(qPrintable(u.name)), after.values[u.name]);
  }
}

void TestUniformsTest::mouseCoordinates_data() {
  QTest::addColumn<QList<QPoint>>("points");

  using QPointList = QList<QPoint>;
  QTest::newRow("basic") << QPointList {{1, 1}, {42, 43}, {100, 99}};
  QTest::newRow("one motion") << QPointList {{0, 0}, {77, 74}};
  QTest::newRow("not moving") << QPointList {{0, 0}, {0, 0}, {0, 0}};
  QTest::newRow("negative") << QPointList {{ -1, -43}, { -119, -32}, { -55, -22}};
  QTest::newRow("change signs") << QPointList {{0, 0}, {34, -66}, { -22, 78}, { -99, -101}, {0, 0}, {1, 0}};
}

void TestUniformsTest::mouseCoordinates() {
  QFETCH(QList<QPoint>, points);
  Q_ASSERT(points.length() >= 2);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  for (const QPoint& p : points) {
    QMouseEvent event(QEvent::MouseMove, p, Qt::NoButton, Qt::NoButton,
                      Qt::NoModifier);
    QCoreApplication::sendEvent(&object, &event);
    // WORKAROUND: QTest::mouseMove doesn't actually fire a QMouseEvent (it just sets the mouse cursor)
  }

  ivec2 mousePos = uniforms.property("mousePos").value<ivec2>();
  ivec2 lastMousePos = uniforms.property("lastMousePos").value<ivec2>();

  const QPoint& pos = points.last();
  const QPoint& lastPos = points[points.length() - 2];

  QCOMPARE(mousePos.x, pos.x());
  QCOMPARE(mousePos.y, pos.y());

  QCOMPARE(lastMousePos.x, lastPos.x());
  QCOMPARE(lastMousePos.y, lastPos.y());
}

void TestUniformsTest::canvasSize_data() {
  QTest::addColumn<QList<QSize>>("sizes");

  using QSizeList = QList<QSize>;
  QTest::newRow("basic") << QSizeList {{1, 1}, {42, 43}, {100, 99}};
  QTest::newRow("one resize") << QSizeList {{1, 1}, {77, 74}};
  QTest::newRow("grow then shrink") << QSizeList {{1, 1}, {45, 76}, {12, 100}, {34, 99}};
}

void TestUniformsTest::canvasSize() {
  QFETCH(QList<QSize>, sizes);
  Q_ASSERT(sizes.length() >= 2);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  for (int i = 1; i < sizes.length(); ++i) {
    QResizeEvent event(sizes[i], sizes[i - 1]);
    QCoreApplication::sendEvent(&object, &event);
  }

  uvec2 canvasSize = uniforms.property("canvasSize").value<uvec2>();
  uvec2 lastCanvasSize = uniforms.property("lastCanvasSize").value<uvec2>();
  uint canvasWidth = uniforms.property("canvasWidth").value<uint>();
  uint canvasHeight = uniforms.property("canvasHeight").value<uint>();

  const QSize& size = sizes.last();
  const QSize& lastSize = sizes[sizes.length() - 2];

  QCOMPARE(canvasWidth, canvasSize.x);
  QCOMPARE(canvasHeight, canvasSize.y);

  QCOMPARE(int(canvasSize.x), size.width());
  QCOMPARE(int(canvasSize.y), size.height());

  QCOMPARE(int(lastCanvasSize.x), lastSize.width());
  QCOMPARE(int(lastCanvasSize.y), lastSize.height());
}

void TestUniformsTest::filtersEvents() {
  QObject object;
  Uniforms uniforms;
  QSize size {100, 100};
  QResizeEvent resize {size, {2, 2}};

  object.installEventFilter(&uniforms);
  QCoreApplication::sendEvent(&object, &resize);

  ivec2 canvasSize = uniforms.property("canvasSize").value<ivec2>();

  QCOMPARE(canvasSize.x, size.width());
  QCOMPARE(canvasSize.y, size.height());
}

void TestUniformsTest::elapsedTimeIsUInt() {
  Uniforms uniforms;

  QVariant a = uniforms.property("elapsedTime");
  QCOMPARE(a.type(), QVariant::UInt);
}

void TestUniformsTest::elapsedTimeIncreases() {
  Uniforms uniforms;

  QTest::qSleep(50);
  uint a = uniforms.property("elapsedTime").toUInt();
  QTest::qSleep(50);
  uint b = uniforms.property("elapsedTime").toUInt();
  QTest::qSleep(50);
  uint c = uniforms.property("elapsedTime").toUInt();

  QVERIFY(a != 0);
  QVERIFY(b != 0);
  QVERIFY(c != 0);
  QVERIFY(b > a);
  QVERIFY(c > b);
}

QTEST_MAIN(TestUniformsTest)

#include "tst_TestUniformsTest.moc"

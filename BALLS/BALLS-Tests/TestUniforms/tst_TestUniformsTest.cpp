#include "precompiled.hpp"
#include "util/MetaTypeConverters.hpp"
#include "util/TypeInfo.hpp"

#include <QString>
#include <QtTest>
#include <QList>
#include <QCoreApplication>
#include "ui/Uniforms.hpp"
#include "util/Logging.hpp"

using namespace glm;
using balls::Uniforms;
using balls::UniformCollection;
using balls::UniformInfo;

class TestUniformsTest : public QObject {
  Q_OBJECT

private slots:
  void initTestCase();

  void elapsedTimeIncreases();
  void elapsedTimeIsUInt();
  void filtersEvents();
  void mouseCoordinates();
  void mouseCoordinates_data();
  void receiveUniforms();
  void receiveUniforms_data();
};

void TestUniformsTest::initTestCase() {
  QLoggingCategory::setFilterRules("uniform*=false");
  balls::registerMetaTypeConverters();
  balls::util::types::init();

  QVERIFY(balls::util::types::info.size() > 0);
  QVERIFY(QMetaType::type("vec2") != QMetaType::UnknownType);
}

void TestUniformsTest::receiveUniforms_data() {
  QTest::addColumn<UniformCollection>("beforeCompile");
  QTest::addColumn<UniformCollection>("afterCompile");

  QTest::newRow("empty -> empty") << UniformCollection {} << UniformCollection {};

}

void TestUniformsTest::receiveUniforms() {
  QFETCH(UniformCollection, beforeCompile);
  QFETCH(UniformCollection, afterCompile);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  uniforms.receiveUniforms(beforeCompile);

  QCOMPARE(uniforms.uniformInfo(), beforeCompile);

  uniforms.receiveUniforms(afterCompile);


}

void TestUniformsTest::mouseCoordinates_data() {
  QTest::addColumn<QList<QPoint>>("points");

  using QPointList = QList<QPoint>;
  QTest::newRow("basic") << QPointList {{1, 1}, {42, 43}, {100, 99}};
  QTest::newRow("not moving") << QPointList {{0, 0}, {0, 0}, {0, 0}};
  QTest::newRow("negative") << QPointList {{-1, -43}, {-119, -32}, {-55, -22}};
  QTest::newRow("change signs") << QPointList {{0, 0}, {34, -66}, {-22, 78}, {-99, -101}, {0, 0}, {1, 0}};
}

void TestUniformsTest::mouseCoordinates() {
  QFETCH(QList<QPoint>, points);
  Q_ASSERT(points.length() >= 2);

  QObject object;
  Uniforms uniforms;

  object.installEventFilter(&uniforms);

  for (const QPoint& p : points) {
    QMouseEvent event(QEvent::MouseMove, p, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
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
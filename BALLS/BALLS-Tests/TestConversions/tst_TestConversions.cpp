#include "precompiled.hpp"
#include "util/MetaTypeConverters.hpp"

#include <QString>
#include <QtTest>
#include <QMetaType>

#include <boost/mpl/for_each.hpp>

template<typename From>
struct other_handler {
  template<typename To>
  inline void operator()(To&) noexcept {
    if (!balls::types::is_builtin_conv<From, To>()) {
    // If this isn't one of the default conversions within QVariant...

    auto from = qMetaTypeId<From>();
    auto to = qMetaTypeId<To>();

    QString tag;
    tag
    .append(QMetaType::typeName(from))
    .append(" -> ")
    .append(QMetaType::typeName(to));

    QTest::newRow(qPrintable(tag)) << from << to;
    }
  }
};

template<typename FromSeq>
struct handler {
  template<typename To>
  inline void operator()(To&) noexcept {
    boost::mpl::for_each<FromSeq>(other_handler<To>());
  }
};


/// Register a conversion from every type in SeqA to every type in SeqB
template<class SeqA, class SeqB>
inline void _makeTests() noexcept {
  boost::mpl::for_each<SeqA>(handler<SeqB>());
}

class TestConversions : public QObject {
  Q_OBJECT
private Q_SLOTS:
  void initTestCase();
  void typeConversions();
  void typeConversions_data();
};

void TestConversions::initTestCase()
{
  balls::registerMetaTypeConverters();
}

void TestConversions::typeConversions_data() {
  using namespace glm;
  using namespace balls;

  QTest::addColumn<int>("from");
  QTest::addColumn<int>("to");

  _makeTests<types::Scalars, types::Scalars>();
  _makeTests<types::Scalars, types::qt::Vecs>();
  _makeTests<types::Scalars, types::glm::VecsQuats>();

  _makeTests<types::qt::Vecs, types::Scalars>();
  _makeTests<types::qt::Vecs, types::glm::VecsQuats>();
  _makeTests<types::glm::VecsQuats, types::Scalars>();
  _makeTests<types::glm::VecsQuats, types::qt::Vecs>();
  _makeTests<types::glm::VecsQuats, types::glm::VecsQuats>();
  _makeTests<types::all::Mats, types::all::Mats>();
}

void TestConversions::typeConversions() {
  QFETCH(int, from);
  QFETCH(int, to);

  QVariant v(from, nullptr);

  QCOMPARE(static_cast<int>(v.userType()), from);
  QVERIFY(v.canConvert(to));

}

QTEST_APPLESS_MAIN(TestConversions)

#include "tst_TestConversions.moc"

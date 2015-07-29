#include <QString>
#include <QtTest>

class TestJSONConversionsTest : public QObject
{
  Q_OBJECT

public:
  TestJSONConversionsTest();

private Q_SLOTS:
  void testCase1();
};

TestJSONConversionsTest::TestJSONConversionsTest()
{
}

void TestJSONConversionsTest::testCase1()
{
  QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestJSONConversionsTest)

#include "tst_TestJSONConversionsTest.moc"

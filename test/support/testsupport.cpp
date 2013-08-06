
#include <QtTest/QtTest>

#include "../../support.h"

class TestSupport : public QObject {
	Q_OBJECT
private slots:
	void _timestring();
};

/** \brief Macro for seconds */
#define	S(x)	(x)
/** \brief Macro for minutes */
#define	M(x)	(x * 60)
/** \brief Macro for hours */
#define	H(x)	(x * 60 * 60)

void TestSupport::_timestring() {

	QCOMPARE(timestring(0), QString("00:00:00"));
	QCOMPARE(timestring(59), QString("00:00:59"));
	QCOMPARE(timestring(60), QString("00:01:00"));
	QCOMPARE(timestring(600), QString("00:10:00"));
	QCOMPARE(timestring(H(1)), QString("01:00:00"));
	/* 3601 -> 01:00:01 - The value from issue #1 */
	QCOMPARE(timestring(3601), QString("01:00:01"));
	QCOMPARE(timestring(H(23) + M(59) + S(59)), QString("23:59:59"));
	/* 24:00:00 -> BUG */
	QCOMPARE(timestring(H(24)), QString("24:00:00"));
}

QTEST_MAIN(TestSupport)
#include "testsupport.moc"

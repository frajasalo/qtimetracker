#include <QString>
#include <QtTest>

#include "../support.h"

class QttTestSupport : public QObject
{
    Q_OBJECT
    
public:
    QttTestSupport();
    
private Q_SLOTS:
    void testCaseTimeStringToSeconds1();
    void testCaseSecondsToTimeString1();
};

QttTestSupport::QttTestSupport()
{
}

/** \brief Test timestringtoseconds function
 *
 * This will test the function with some valid and invalid arguments.
 * For the valid args the correct value is expected and for the invalid
 * a value of zero should be delivered.
 */
void QttTestSupport::testCaseTimeStringToSeconds1() {

    /* test some valid arguments */
    QVERIFY(25 == timestringtoseconds(QString("00:00:25")));
    QVERIFY(1825 == timestringtoseconds(QString("00:30:25")));
    QVERIFY(43525 == timestringtoseconds(QString("12:05:25")));
    QVERIFY(145225 == timestringtoseconds(QString("40:20:25")));
    QVERIFY(1083565 == timestringtoseconds(QString("300:59:25")));
    /* now some invalid */
    QVERIFY(0 == timestringtoseconds(QString("d:00:25")));
    QVERIFY(0 == timestringtoseconds(QString("00:W0:25")));
    QVERIFY(0 == timestringtoseconds(QString("00:00:2E")));
    QVERIFY(0 == timestringtoseconds(QString("00:0:25")));
    QVERIFY(0 == timestringtoseconds(QString("00:00:5")));
    QVERIFY(0 == timestringtoseconds(QString("00:0:5")));
    QVERIFY(0 == timestringtoseconds(QString("0:00:50")));
    QVERIFY(0 == timestringtoseconds(QString("He dude !")));
}

/** \brief Test secondstotimestring function
 */
void QttTestSupport::testCaseSecondsToTimeString1() {
    /* test some known arguments ;) */
    QVERIFY(secondstotimestring(0) == QString("00:00:00"));
    QVERIFY(secondstotimestring(25) == QString("00:00:25"));
    QVERIFY(secondstotimestring(1825) == QString("00:30:25"));
    QVERIFY(secondstotimestring(43525) == QString("12:05:25"));
    QVERIFY(secondstotimestring(145225) == QString("40:20:25"));
    QVERIFY(secondstotimestring(1083565) == QString("300:59:25"));

    QVERIFY(secondstotimestring(60) == QString("00:01:00"));
    QVERIFY(secondstotimestring(3600) == QString("01:00:00"));
}

QTEST_APPLESS_MAIN(QttTestSupport)

#include "tst_qtttestsupport.moc"

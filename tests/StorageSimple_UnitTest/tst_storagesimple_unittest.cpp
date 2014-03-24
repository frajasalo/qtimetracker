#include <QString>
#include <QtTest>
#include <QTest>

#include "../../storagesimpletext.h"

class StorageSimple_UnitTest : public QObject
{
    Q_OBJECT

public:
    StorageSimple_UnitTest();

private:
    void pushTask2Vector(std::vector<task_t> &, uint32_t, QString, bool = true);
    void saveVector(std::vector<task_t>, QString = "");

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase_SetFileName();
    void testCase_GetName1();
    void testCase_AddTask();
    void testCase_GetName2();
    void testCase_DelTask();
    void testCase_SaveSingle();
    void testCase_SaveMultiple();
    void testCase_LoadFailures();
    void testCase_LoadSingle();
    void testCase_LoadMultiple();
    void testCase_Update();
};

StorageSimple_UnitTest::StorageSimple_UnitTest() {}

/** @brief helper function: store a task into a vector of tasks
 *  @param tv the vector for storin the new task into
 *  @param id ID of the task
 *  @param time time of the task
 *  @param complete
 *
 * this function creates a new task and store it into the vector tv.
 */
void StorageSimple_UnitTest::pushTask2Vector(std::vector<task_t> &tv, uint32_t id, QString time, bool complete/* = true*/) {
    task_t tt;
    tt.id = id;
    tt.time = time.toStdString();
    tt.complete = complete;
    /* add the task to the vector */
    tv.push_back(tt);
}

void StorageSimple_UnitTest::initTestCase() {}

void StorageSimple_UnitTest::cleanupTestCase() {}

/** @brief tests the SetFileName function
 *
 * it test the default filename first.
 * then it sets a new filename and test against this.
 */
void StorageSimple_UnitTest::testCase_SetFileName() {

    StorageSimpleText to;
    QCOMPARE(to.SetFileName("").c_str(), "qtimetracker.txt");
    to.SetFileName("Mr.Boo");
    QCOMPARE(to.SetFileName("").c_str(), "Mr.Boo");
}

/** @brief test the getting the name function of a non existing task from the
 * storage */
void StorageSimple_UnitTest::testCase_GetName1() {

    StorageSimpleText out;
    std::string n = out.GetTaskName(0);
    QCOMPARE(std::string(), n);
}

/** @brief test the addition of several tasks from the storage */
void StorageSimple_UnitTest::testCase_AddTask() {

    StorageSimpleText out;
    QVERIFY(0 != out.AddTask("test1"));
    QVERIFY(0 != out.AddTask("test2", 0));
    QVERIFY(0 == out.AddTask("test3", 1));
}

/** @brief test the getting the name function of a task from the storage */
void StorageSimple_UnitTest::testCase_GetName2() {

    StorageSimpleText out;
    uint32_t t1 = out.AddTask("test1");
    uint32_t t2 = out.AddTask("test2");
    uint32_t t3 = out.AddTask("test3");

    QCOMPARE(std::string("test1"), out.GetTaskName(t1));
    QCOMPARE(std::string("test2"), out.GetTaskName(t2));
    QCOMPARE(std::string("test3"), out.GetTaskName(t3));
    QCOMPARE(std::string("test1"), out.GetTaskName(t1));
}

/** @brief test the deletion of several tasks from the storage */
void StorageSimple_UnitTest::testCase_DelTask() {

    StorageSimpleText out;
    uint32_t t1 = out.AddTask("test1");
    uint32_t t2 = out.AddTask("test2");
    /*uint32_t t3 = */out.AddTask("test3");

    QCOMPARE(false, out.DelTask(0));
    /* Not 100% sucessfull, because it could be ... */
    QCOMPARE(false, out.DelTask(t1 + 1));
    QCOMPARE(true, out.DelTask(t1));
    QCOMPARE(false, out.DelTask(t1));
    QCOMPARE(std::string(), out.GetTaskName(t1));
    QCOMPARE(true, out.DelTask(t2));
}

/** @brief test the saving of a vector containing only one task. */
void StorageSimple_UnitTest::testCase_SaveSingle() {

    /* Object Under Test */
    StorageSimpleText out;
    /* add a task */
    uint32_t t1 = out.AddTask("test1");
    /* test vector that data shall be saved */
    std::vector<task_t> tv;
    /* test task 1 */
    this->pushTask2Vector(tv, t1, "00:03:23");
    /* save the vector to the (default) file via the Object Under Test */
    out.Save(tv);

    /* now read back and compare the saved file */
    QFile tf("qtimetracker.txt");
    if (!tf.open(QIODevice::ReadOnly)) {
       QFAIL("can not open the test file\n");
    }
    QTextStream in(&tf);
    QString line_name = in.readLine();
    QCOMPARE(line_name, QString("test1"));
    QString line_time = in.readLine();
    QCOMPARE(line_time, QString("00:03:23"));
    QVERIFY(tf.atEnd());
    tf.close();
}

/** @brief test the saving of a vector with multiple tasks. */
void StorageSimple_UnitTest::testCase_SaveMultiple() {
    /* Object under Test */
    StorageSimpleText out;
    /* test vector that data shall be saved */
    std::vector<task_t> tv;
    /* test tasks */
    this->pushTask2Vector(tv, out.AddTask("test1"), "00:03:23");
    this->pushTask2Vector(tv, out.AddTask("test2"), "01:12:45");
    this->pushTask2Vector(tv, out.AddTask("test3"), "02:04:59");
    this->pushTask2Vector(tv, out.AddTask("test4"), "03:01:00", false);
    this->pushTask2Vector(tv, out.AddTask("test5"), "00:33:17");
    /* save the vector to the (default) file */
    out.Save(tv);

    /* now read back and compare the saved file */
    QFile tf("qtimetracker.txt");
    if (!tf.open(QIODevice::ReadOnly)) {
       QFAIL("can not open the test file\n");
    }
    QTextStream in(&tf);

    QString line = in.readLine();
    QCOMPARE(line, QString("test1"));
    line = in.readLine();
    QCOMPARE(line, QString("00:03:23"));
    line = in.readLine();
    QCOMPARE(line, QString("complete"));

    line = in.readLine();
    QCOMPARE(line, QString("test2"));
    line = in.readLine();
    QCOMPARE(line, QString("01:12:45"));
    line = in.readLine();
    QCOMPARE(line, QString("complete"));

    line = in.readLine();
    QCOMPARE(line, QString("test3"));
    line = in.readLine();
    QCOMPARE(line, QString("02:04:59"));
    line = in.readLine();
    QCOMPARE(line, QString("complete"));

    line = in.readLine();
    QCOMPARE(line, QString("test4"));
    line = in.readLine();
    QCOMPARE(line, QString("03:01:00"));
    line = in.readLine();
    QCOMPARE(line, QString("incomplete"));

    line = in.readLine();
    QCOMPARE(line, QString("test5"));
    line = in.readLine();
    QCOMPARE(line, QString("00:33:17"));
    line = in.readLine();
    QCOMPARE(line, QString("complete"));

    QVERIFY(tf.atEnd());
    tf.close();
}

/** @brief test the failure of loading from file. */
void StorageSimple_UnitTest::testCase_LoadFailures() {

    /* try to load a non-existing file */
    StorageSimpleText to;
    remove(to.SetFileName().c_str());
    std::vector<task_t> tv;
    QVERIFY("" != to.Load(tv));
    QVERIFY("could not open file for reading" == to.Load(tv));

    /* try to load a broken file */
    QFile tf(QString("qtimetracker.txt"));
    if (!tf.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
        QFAIL("Could not open file");
    tf.write("test1\n");
    tf.write("00:41:33");
    tf.close();
    QVERIFY("" != to.Load(tv));
    QVERIFY("file looks broken" == to.Load(tv));
}

/** @brief test the loading of a single task. */
void StorageSimple_UnitTest::testCase_LoadSingle() {

    StorageSimpleText sto;
    uint32_t t1 = sto.AddTask("test1");
    /* save test vector */
    std::vector<task_t> stv;
    /* push a single task to vector and save to file */
    this->pushTask2Vector(stv, t1, "00:03:23");
    sto.Save(stv);

    /* load test object */
    StorageSimpleText lto;
    /* load test vector */
    std::vector<task_t> ltv;
    /* load from file */
    lto.Load(ltv);
    /* compare the size of save and load vector */
    QCOMPARE(stv.size(), ltv.size());
    /* compare the content of the vectors */
    for (unsigned int i = 0; i < stv.size(); ++i) {
        task_t stt = stv.at(i);
        task_t ltt = ltv.at(i);
        QCOMPARE(sto.GetTaskName(stt.id), lto.GetTaskName(ltt.id));
        QCOMPARE(stt.time, ltt.time);
        QCOMPARE(stt.complete, ltt.complete);
    }
}

/** @brief test the loading of multiple tasks. */
void StorageSimple_UnitTest::testCase_LoadMultiple() {

    StorageSimpleText sto;
    /* save test vector */
    std::vector<task_t> stv;
    /* push some tasks into the vector and save to file */
    this->pushTask2Vector(stv, sto.AddTask("test1"), "00:03:23");
    this->pushTask2Vector(stv, sto.AddTask("test2"), "01:12:45");
    this->pushTask2Vector(stv, sto.AddTask("test3"), "02:04:59");
    this->pushTask2Vector(stv, sto.AddTask("test4"), "03:01:00", false);
    this->pushTask2Vector(stv, sto.AddTask("test5"), "00:33:17");
    sto.Save(stv);

    /* load test object */
    StorageSimpleText lto;
    /* load test vector */
    std::vector<task_t> ltv;
    /* load from file */
    lto.Load(ltv);
    /* compare the size of save and load vector */
    QCOMPARE(stv.size(), ltv.size());
    /* compare the content of the vectors */
    for (unsigned int i = 0; i < stv.size(); ++i) {
        task_t stt = stv.at(i);
        task_t ltt = ltv.at(i);
        QCOMPARE(sto.GetTaskName(stt.id), lto.GetTaskName(ltt.id));
        QCOMPARE(stt.time, ltt.time);
        QCOMPARE(stt.complete, ltt.complete);
    }
}

void StorageSimple_UnitTest::testCase_Update() {

    StorageSimpleText out;
    uint32_t t1 = out.AddTask("test1");
    QCOMPARE(std::string("not supported"), out.AddTaskPeriod(t1, 0, 0));
}

QTEST_APPLESS_MAIN(StorageSimple_UnitTest)

#include "tst_storagesimple_unittest.moc"

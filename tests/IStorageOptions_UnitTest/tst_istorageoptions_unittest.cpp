/** @file tst_istorageoptions_unittest.cpp
 *  @author Frank Bergmann
 *  @date 2014
 *  @copyright GNU Public License.
 *
 * qtimetracker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qtimetracker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtimetracker.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QString>
#include <QtTest>

#include "../../storageoptions.h"

class IStorageOptions_UnitTest : public QObject
{
    Q_OBJECT

public:
    IStorageOptions_UnitTest();

private Q_SLOTS:
    void testCase_AddOption();
    void testCase_GetOptionValue();
    void testCase_SetOptionValue();
};

IStorageOptions_UnitTest::IStorageOptions_UnitTest() {}

void IStorageOptions_UnitTest::testCase_AddOption() {

    IStorageOptions uut;
    QCOMPARE(0, (int)uut.GetOptions().size());

    StoreOption_t opt1;
    opt1.name = "test";
    opt1.value = "test";
    QCOMPARE(true, uut.AddOption(opt1));
    QCOMPARE(1, (int)uut.GetOptions().size());

    StoreOption_t opt2;
    opt2.name = "tset";
    opt2.value = "tset";
    QCOMPARE(true, uut.AddOption(opt2));
    QCOMPARE(2, (int)uut.GetOptions().size());

    QCOMPARE(false, uut.AddOption(opt1));
    QCOMPARE(2, (int)uut.GetOptions().size());
    opt2.name = "test";
    QCOMPARE(false, uut.AddOption(opt2));
    QCOMPARE(2, (int)uut.GetOptions().size());
}

void IStorageOptions_UnitTest::testCase_GetOptionValue() {

    IStorageOptions uut;
    StoreOption_t opt;
    opt.name = "aaa";
    opt.value = "aaa";
    QCOMPARE(true, uut.AddOption(opt));
    opt.name = "bbb";
    opt.value = "bbb";
    QCOMPARE(true, uut.AddOption(opt));
    opt.name = "ccc";
    opt.value = "ccc";
    QCOMPARE(true, uut.AddOption(opt));

    QCOMPARE(std::string("bbb"), uut.GetOptionValue("bbb"));
    QCOMPARE(std::string("aaa"), uut.GetOptionValue("aaa"));
    QCOMPARE(std::string(), uut.GetOptionValue("abc"));
}

void IStorageOptions_UnitTest::testCase_SetOptionValue() {

    IStorageOptions uut;
    StoreOption_t opt;
    opt.name = "aaa";
    opt.value = "aaa";
    QCOMPARE(true, uut.AddOption(opt));
    opt.name = "bbb";
    opt.value = "bbb";
    QCOMPARE(true, uut.AddOption(opt));
    opt.name = "ccc";
    opt.value = "ccc";
    QCOMPARE(true, uut.AddOption(opt));

    QCOMPARE(std::string("bbb"), uut.GetOptionValue("bbb"));
    QCOMPARE(std::string("xyz"), uut.SetOptionValue("bbb", "xyz"));
    QCOMPARE(std::string("xyz"), uut.GetOptionValue("bbb"));
    QCOMPARE(std::string("aaa"), uut.GetOptionValue("aaa"));
    QCOMPARE(std::string(), uut.GetOptionValue("abc"));
}

QTEST_APPLESS_MAIN(IStorageOptions_UnitTest)

#include "tst_istorageoptions_unittest.moc"

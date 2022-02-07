/// \file
/// \author 
///
/// \brief Implementation of tests for the VersionNumber class.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include <XMiLib/VersionNumber/VersionNumber.h>
#include "XMiLibTest.h"


using namespace xmilib;


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void XMiLibTest::versionNumberTest()
{
   VersionNumber const invalidVersion;
   QVERIFY(invalidVersion.major() == -1);
   QVERIFY(invalidVersion.minor() == -1);
   QVERIFY(!invalidVersion.isValid());

   VersionNumber v(1, 2);
   QVERIFY(v.major() == 1);
   QVERIFY(v.minor() == 2);
   QVERIFY(v.isValid());

   v.setMajor(3);
   v.setMinor(4);
   QVERIFY(v.major() == 3);
   QVERIFY(v.minor() == 4);

   QCOMPARE(VersionNumber(v), v);
   QCOMPARE(VersionNumber(v), v);
   VersionNumber w(0, 1);
   w = v;
   QCOMPARE(v, w);
   VersionNumber x(1, 0);
   x = std::move(w);
   QCOMPARE(v, x);
   VersionNumber const y(std::move(x));
   QCOMPARE(v, y);

   QCOMPARE(v == VersionNumber(3,4), true);
   QCOMPARE(v == VersionNumber(3,3), false);
   QCOMPARE(v == VersionNumber(2,4), false);
   QCOMPARE(v == VersionNumber(2,2), false);

   QCOMPARE(v != VersionNumber(3,2), true);
   QCOMPARE(v != VersionNumber(2,4), true);
   QCOMPARE(v != VersionNumber(2,2), true);
   QCOMPARE(v != VersionNumber(3,4), false);

   QCOMPARE(v < VersionNumber(3,5), true);
   QCOMPARE(v < VersionNumber(4,0), true);
   QCOMPARE(v < VersionNumber(3,4), false);
   QCOMPARE(v < VersionNumber(2,5), false);
   QCOMPARE(v < VersionNumber(1,0), false);

   QCOMPARE(v <= VersionNumber(3,5), true);
   QCOMPARE(v <= VersionNumber(4,0), true);
   QCOMPARE(v <= VersionNumber(3,4), true);
   QCOMPARE(v <= VersionNumber(2,5), false);
   QCOMPARE(v <= VersionNumber(1,0), false);

   QCOMPARE(v > VersionNumber(3,5), false);
   QCOMPARE(v > VersionNumber(4,0), false);
   QCOMPARE(v > VersionNumber(3,4), false);
   QCOMPARE(v > VersionNumber(2,5), true);
   QCOMPARE(v > VersionNumber(1,0), true);

   QCOMPARE(v >= VersionNumber(3,5), false);
   QCOMPARE(v >= VersionNumber(4,0), false);
   QCOMPARE(v >= VersionNumber(3,4), true);
   QCOMPARE(v >= VersionNumber(2,5), true);
   QCOMPARE(v >= VersionNumber(1,0), true);

   QCOMPARE(VersionNumber(1, 0).toString(), "1.0");
   QCOMPARE(VersionNumber(1, 1).toString(), "1.1");
   QCOMPARE(VersionNumber(2, 4).toString(), "2.4");

   bool ok = false;
   v = VersionNumber::fromString("1.0", &ok);
   QVERIFY(ok);
   QCOMPARE(v, VersionNumber(1, 0));
   v = VersionNumber::fromString("3.2", &ok);
   QVERIFY(ok);
   QCOMPARE(v, VersionNumber(3, 2));
   v = VersionNumber::fromString("a1.0", &ok);
   QVERIFY(!ok);
   v = VersionNumber::fromString("2", &ok);
   QVERIFY(!ok);
}


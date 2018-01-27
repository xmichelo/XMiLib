/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the XMiLib random number generator utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/RandomNumberGenerator.h>
#include <XMiLib/Exception.h>
#include <vector>


using namespace xmilib;


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::randomNumberGenerator_range_data()
{
   QTest::addColumn<qint32>("minValue");
   QTest::addColumn<qint32>("maxValue");
   QTest::addColumn<bool>("shouldThrowException");
   QTest::newRow("Byte range") << 0 << 255 << false;
   QTest::newRow("Negative and positive") <<  -100000 << 20 << false;
   QTest::newRow("All positives") << 0 << std::numeric_limits<int>::max() << false;
   QTest::newRow("Single number") << 8 << 8 << false;
   QTest::newRow("Invalid range") << 2 << 1 << true;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::randomNumberGenerator_range()
{
   qint32 const sampleCount = 1000;
   // ReSharper disable CppLocalVariableMayBeConst
   QFETCH(qint32, minValue);
   QFETCH(qint32, maxValue);
   QFETCH(bool, shouldThrowException);
   // ReSharper restore CppLocalVariableMayBeConst
   try
   {
      RandomNumberGenerator rng(minValue, maxValue);
      for (qint32 i = 0; i < sampleCount; ++i)
      {
         qint32 const value = rng.get();
         QVERIFY2((value >= minValue) && (value <= maxValue), "The generated value is not is the specified range");
      }
      if (shouldThrowException)
         QFAIL("The test should have thrown an exception, but did not.");
   }
   catch (xmilib::Exception const&)
   {
      if (!shouldThrowException)   	
         QFAIL("The test threw an unexpected exception");
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::randomNumberGenerator_randomness()
{
   qint32 const sampleCount = 1000; 
   qint32 const maxValue = 10; 
   qint32 const testCount = 20; 
   for (int j = 0; j < testCount; ++j)
   {
      std::vector<qint32> accum(maxValue + 1, 0);
      RandomNumberGenerator rng(0, maxValue);

      /// we count all the values we get from the generator
      for (int i = 0; i < sampleCount * (maxValue + 1); ++i)
         ++accum[rng.get()];

      /// we check they are more or less evenly distributed
      float const minRatio = float(*std::min_element(accum.begin(), accum.end()) / float(sampleCount));
      float const maxRatio = float(*std::max_element(accum.begin(), accum.end()) / float(sampleCount));
      QVERIFY2((minRatio > 0.75) && (maxRatio < 1.25), "The distribution of random values is not even");
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::randomNumberGenerator_seed()
{
   try
   {
      qint32 const seedTestCount = 100;
      qint32 const seedCheckDistance = 200;
      qint32 const minVal = -100;
      qint32 const maxVal = 100;
      for (int n = 0; n < seedTestCount; ++n)
      {
         quint32 const seed = std::random_device()();
         RandomNumberGenerator rng1(seed, minVal, maxVal), rng2(seed, minVal, maxVal), rng3(seed + 1, minVal, maxVal);
         std::vector<qint32> val1, val2, val3;
         val1.reserve(seedCheckDistance);
         val2.reserve(seedCheckDistance);
         val3.reserve(seedCheckDistance);
         for (int i = 0; i < seedCheckDistance; ++i)
         {
            val1.push_back(rng1.get());
            val2.push_back(rng2.get());
            val3.push_back(rng3.get());
         }
         QVERIFY2(val1 == val2, "Two generators with the same seed led to differents generated values");
         QVERIFY2(val1 != val3, "Two generators with different seeds led to identical generated values");
      }
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }   
}





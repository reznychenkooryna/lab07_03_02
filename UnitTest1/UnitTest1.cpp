#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_03_02/Lab_07_03_02.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestMethod1)
        {
            const int rowCount = 4;
            const int colCount = 3;

            int** a = new int* [rowCount];
            a[0] = new int[colCount] { 1, 2, 3 };
            a[1] = new int[colCount] { 0, 2, 2 };
            a[2] = new int[colCount] { 4, 2, 2 };
            a[3] = new int[colCount] { 5, 6, 7 };

            int expectedZeroRows = 1;
            int actualZeroRows = CountRowsWithZero(a, rowCount, colCount);
            Assert::AreEqual(expectedZeroRows, actualZeroRows, L"Incorrect zero row count");

            int expectedSeriesLength = 3;
            int actualSeriesLength = MaxSeriesLengthInColumn(a, rowCount, 2);
            Assert::AreEqual(expectedSeriesLength, actualSeriesLength, L"Incorrect max series length in column");

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }
	};
}

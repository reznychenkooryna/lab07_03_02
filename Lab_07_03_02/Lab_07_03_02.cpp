// Lab_7_3.cpp 
// < Резниченко Орина > 
// Лабораторна робота № 7.3. 
// Опрацювання динамічних багатовимірних масивів. Рекурсивний спосіб. 
// Варіант 18

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

bool HasZeroInRow(int** a, const int rowNo, const int colCount, int colNo)
{
    if (a[rowNo][colNo] == 0) return true;
    if (colNo < colCount - 1)
        return HasZeroInRow(a, rowNo, colCount, colNo + 1);
    return false;
}

int CountRowsWithZero(int** a, const int rowCount, const int colCount, int rowNo)
{
    if (rowNo >= rowCount) return 0;
    int add = HasZeroInRow(a, rowNo, colCount, 0) ? 1 : 0;
    return add + CountRowsWithZero(a, rowCount, colCount, rowNo + 1);
}

int ColumnSeriesLength(int** a, const int rowCount, const int colNo,
    int rowNo, int currLen, int maxLen)
{
    if (rowNo >= rowCount) return maxLen;
    if (a[rowNo][colNo] == a[rowNo - 1][colNo]) currLen++;
    else currLen = 1;
    if (currLen > maxLen) maxLen = currLen;
    return ColumnSeriesLength(a, rowCount, colNo, rowNo + 1, currLen, maxLen);
}

void FindColumnWithLongestSeries(int** a, const int rowCount, const int colCount,
    int& bestCol, int& bestLen, int colNo)
{
    if (colNo >= colCount) return;
    int len = ColumnSeriesLength(a, rowCount, colNo, 1, 1, 1);
    if (len > bestLen)
    {
        bestLen = len;
        bestCol = colNo;
    }
    FindColumnWithLongestSeries(a, rowCount, colCount, bestCol, bestLen, colNo + 1);
}

int main()
{
    srand((unsigned)time(NULL));

    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    int count = CountRowsWithZero(a, rowCount, colCount, 0);
    if (count > 0)
        cout << "Rows with at least one zero: " << count << endl;
    else
        cout << "No zero elements in any row." << endl;

    int bestCol = -1, bestLen = 0;
    FindColumnWithLongestSeries(a, rowCount, colCount, bestCol, bestLen, 0);
    cout << "Column with the longest series: " << bestCol << " (length = " << bestLen << ")" << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

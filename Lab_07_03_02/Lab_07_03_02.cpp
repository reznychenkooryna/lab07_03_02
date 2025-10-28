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
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

int CountZerosInRow(int* row, int colCount, int colNo = 0)
{
    if (row[colNo] == 0)
        return 1;
    if (colNo < colCount - 1)
        return CountZerosInRow(row, colCount, colNo + 1);
    return 0;
}

int CountRowsWithZero(int** a, int rowCount, int colCount, int rowNo = 0)
{
    int count = CountZerosInRow(a[rowNo], colCount);
    if (rowNo < rowCount - 1)
        return count + CountRowsWithZero(a, rowCount, colCount, rowNo + 1);
    return count;
}

int MaxSeriesLengthInColumn(int** a, int rowCount, int colNo, int rowNo = 1, int currentLen = 1, int maxLen = 1)
{
    if (rowNo < rowCount)
    {
        if (a[rowNo][colNo] == a[rowNo - 1][colNo])
            currentLen++;
        else
            currentLen = 1;

        if (currentLen > maxLen)
            maxLen = currentLen;

        return MaxSeriesLengthInColumn(a, rowCount, colNo, rowNo + 1, currentLen, maxLen);
    }
    return maxLen;
}

void FindMaxSeriesColumn(int** a, int rowCount, int colCount)
{
    int maxLen = 0;
    int maxCol = 0;

    for (int col = 0; col < colCount; col++)
    {
        int len = MaxSeriesLengthInColumn(a, rowCount, col);
        if (len > maxLen)
        {
            maxLen = len;
            maxCol = col;
        }
    }

    cout << "Column with longest series of equal elements: " << maxCol
        << " (length = " << maxLen << ")" << endl;
}

int main()
{
    srand((unsigned)time(NULL));

    int rowCount, colCount;
    cout << "Enter number of rows (k): "; cin >> rowCount;
    cout << "Enter number of columns (n): "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    cout << "\nInput matrix elements:\n";
    InputRows(a, rowCount, colCount, 0);

    cout << "\nMatrix:\n";
    PrintRows(a, rowCount, colCount, 0);

    int zeroRowCount = CountRowsWithZero(a, rowCount, colCount);
    cout << "\nNumber of rows with at least one zero element: " << zeroRowCount << endl;

    FindMaxSeriesColumn(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
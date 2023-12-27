#include <vector>
#include <iostream>

using namespace std;



bool IsColumnValid(int rowToAnalice, int colToAnalice, vector<int>& columnValuePerRow)
{
    for (int row = 0; row <= rowToAnalice; ++row)    // we have to study only the previous column values
    {
        if (columnValuePerRow[row] == colToAnalice 
            or (row + columnValuePerRow[row] == rowToAnalice + colToAnalice)
            or (row - columnValuePerRow[row] == rowToAnalice - colToAnalice)
            )
        {
            return false;
        }
    }
    return true;
}

int CalculateColumnValuePerRow(int numTrees, vector<int>& columnValuePerRow, int row)
{
    for (int col = columnValuePerRow[row] + 1; col < numTrees; ++col)
    {
        if (IsColumnValid(row, col, columnValuePerRow))
        {
            return columnValuePerRow[row] = col;
        }
    }
    columnValuePerRow[row] = -1;    // case we arrive at the end and we didnt find a solution, we reset to -1 because
                                    // could be we had a value
    return columnValuePerRow[row];
}

void CalculateTreeCoordinates(int numTrees, vector<int>& columnValuePerRow, int initRow = 0)
{
    // We have to find the column value for each row. We will use backtracking.
    // That means that if we don't find a solution for these values we will go to a previous row
    // and continue searching from the column value it had.
    // So on until you find a solution or explore all the possibilities.

    for (int row = initRow; row < numTrees; ++row)
    {
        CalculateColumnValuePerRow(numTrees, columnValuePerRow, row);
        if (columnValuePerRow[row] == -1) //if we didnt find a value for this row, we have to continue in a previous row and next column value
        { 
            CalculateTreeCoordinates(numTrees, columnValuePerRow, row - 1); 
            return;
        }
    }
    
}

void PrintTreeCoordinates(int numTrees, vector<int> columnValuePerRow)
{
    for (int row = 0; row < numTrees; ++row)
    {
        for (int col = 0; col < numTrees; ++col)
        {
            if (columnValuePerRow[row] == col) cout << " O ";
            else cout << " - ";
        }
        cout << endl;
    }

}

int main() {
    const int numTrees = 9;
    vector<int> columnValuePerRow(numTrees, -1);

    CalculateTreeCoordinates(numTrees, columnValuePerRow);
    PrintTreeCoordinates(numTrees, columnValuePerRow);
    return 0;
}

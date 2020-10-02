#include <bits/stdc++.h>
using namespace std;
//Size of Sudoku
#define N ;
int grid[N][N];

void getinput()
{
    // cout << "\n\t\tENTER SUDOKU Size\t\t";
    // cin >> N;
    cout << "\n\t\tENTER SUDOKU : \t\t";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
        }
        cout << "\t\t\t\t\t";
    }
}

void printSolution()
{
    cout << "\n\n\t\tTHE SOLUTION IS : \t";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
        cout << "\t\t\t\t\t";
    }
}

bool isSafe_RC(int row, int col, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num)
            return false;
        if (grid[i][col] == num)
            return false;
    }
    return true;
}

bool isSafe_Box(int row, int col, int num)
{
    int boxx = row / 3;
    int boxy = col / 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (grid[boxx * 3 + i][boxy * 3 + j] == num)
                return false;
        }
    return true;
}

bool isSafe(int i, int j, int num)
{
    return isSafe_RC(i, j, num) && isSafe_Box(i, j, num);
}

bool get_RC(int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

bool solveSudoku()
{
    int i, j;

    if (get_RC(i, j))
    {
        for (int num = 1; num <= N; num++)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                if (solveSudoku())
                    return true;
                else
                    grid[i][j] = 0;
            }
        }
    }
    else
        return true;
    return false;
}

void solve()
{
    if (solveSudoku())
        printSolution();
    else
        cout << "This Sudoku cannot be solved 😌" << endl;
}

int main()
{
    getinput();
    solve();
    system("pause");
    return 0;
}

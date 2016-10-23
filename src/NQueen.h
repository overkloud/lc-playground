#include "Solution.h"

using namespace std;

class NQueen: public  solution {

public:

    typedef vector<string> board;


    //bool placeQueen(board & b, set<pair<int, int>>& blanks, int i, int j, set<pair<int,int>>&stepsTaken)
    //{
    //    auto pos = mkp(i, j);
    //    if (b[i][j] == '.')
    //    {
    //        const int N = b.size();
    //        for (int k = 0; k < N; k++)
    //        {
    //            if (k != j)
    //            {
    //                if (b[i][k] == '.')
    //                {
    //                    b[i][k] = 'X';
    //                    stepsTaken.insert(mkp(i, k));
    //                }
    //            }

    //            if (k != i)
    //            {
    //                if (b[k][j] == '.')
    //                {
    //                    b[k][j] = 'X';
    //                    stepsTaken.insert(mkp(k, j));
    //                }
    //            }
    //        }

    //        pii start(i - std::min(i, j), j - std::min(i, j));
    //        rangen(k,N)
    //        {
    //            int p = start.first + k;
    //            int q = start.second + k;
    //            if (p < N && q < N && (p != i))
    //            {
    //                if (b[p][q] == '.')
    //                {
    //                    b[p][q] = 'X';
    //                    stepsTaken.emplace(p, q);
    //                }
    //            }
    //        }

    //        rangen(k, N)
    //        {
    //            int p = i + k;
    //            int q = j - k;
    //            if (k >= 1 && p < N && q >= 0)
    //            {
    //                if (b[p][q] == '.')
    //                {
    //                    b[p][q] = 'X';
    //                    stepsTaken.emplace(p,q);
    //                }
    //            }
    //            p = i - k;
    //            q = j + k;
    //            if (k >= 1 && p >= 0 && q < N)
    //            {
    //                if (b[p][q] == '.')
    //                {
    //                    stepsTaken.emplace(p, q);
    //                    b[p][q] = 'X';
    //                }
    //            }
    //        }

    //        b[i][j] = 'Q';
    //        blanks.erase(pos);

    //        for (auto taken : stepsTaken)
    //        {
    //            blanks.erase(taken);
    //        }

    //        return true;
    //    }
    //    return false;
    //}

    //bool solve(board &b, int count, set<pair<int, int>> & blanks, vt<vt<string>> & allsols)
    //{
    //    const int n = b.size();
    //    if (n == count)
    //    {
    //        allsols.push_back(b);
    //        return true;
    //    }

    //    set<pair<int, int>>::iterator it = blanks.begin();
    //    while(it != blanks.end())
    //    {
    //        pair<int, int> pos = *it;
    //        set<pair<int, int>> steps;
    //        if (placeQueen(b, blanks, it->first, it->second, steps))
    //        {
    //            solve(b, count + 1, blanks, allsols);
    //        }

    //        {
    //            //revert prev. step
    //            b[pos.first][pos.second] = '.';
    //            for (auto step : steps)
    //            {
    //                b[step.first][step.second] = '.';
    //                blanks.emplace(step.first, step.second);
    //            }
    //            blanks.emplace(pos.first, pos.second);
    //            it = blanks.find(pos);
    //            ++it;
    //        }
    //    }
    //    return false;
    //}



    //vt<vt<string>> solveNQueens2(int n) {
    //    vt<board> result;


    //    const string const_row(n, '.');

    //    board one_sol;
    //    set<pair<int, int>> blanks;
    //    range(n)
    //    {
    //        one_sol.push_back(const_row);
    //    }
    //    range(n)
    //    {
    //        rangen(j, n)
    //        {
    //            blanks.emplace(i, j);
    //        }
    //    }

    //    vt<board> allsols;
    //    solve(one_sol, 0, blanks, allsols);
    //    if (allsols.size())
    //    {
    //        for (board& onesol : allsols)
    //        {
    //            range(n)
    //            {
    //                rangen(j, n)
    //                {
    //                    if (onesol[i][j] == 'X')
    //                    {
    //                        onesol[i][j] = '.';
    //                    }
    //                }
    //            }
    //        }
    //    }


    //    return allsols;
    //}



// only have to check left side of col
bool safePlace(board &b, const int row, const int col)
{
    for (int i = 0; i <= col; i++)
    {
        if (b[row][i] == 'Q')
            return false;
    }

    const int n = (int) b.size();
    for (int i = 1; i <=col ; i++)
    {
        int x = row - i;
        int y = col - i;
        if (x >= 0 && y >= 0 && b[x][y] == 'Q')
        {
            return false;
        }

        x = row + i;
        if (x < n && y >= 0 && b[x][y] == 'Q')
        {
            return false;
        }
    }

    return true;
}


    void solve(board & b, int col, vt<board> & allsols)
    {
        if (col == b.size())
        {
            allsols.push_back(b);
        }
        else
        {
            for (int i = 0; i < b.size(); i++)
            {
                if (safePlace(b, i, col))
                {
                    b[i][col] = 'Q';
                    solve(b, col + 1, allsols);
                }
                b[i][col] = '.';
            }
        }
    }

    vt<vt<string>> solveNQueens(int n) {
        vt<board> allsols;

        board b;
        const string row(n, '.');
        range(n)
        {
            b.push_back(row);
        }

        solve(b, 0, allsols);
        return allsols;
    }



    virtual void test()
    {
        testUtil::timer t;
        t.start();
        auto result = solveNQueens(8);

        for (auto sol : result)
        {
            for (auto row : sol)
            {
                cout << row << endl;
            }
            cout << endl;
        }
        cout << t.stop() << "ms" << endl;
    }
};

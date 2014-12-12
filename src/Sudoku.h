#include "Solution.h"
#include <queue>
#include <sstream>


struct SudokuUnit
{
    int i;
    int j;
    int score;


    SudokuUnit(int i, int j, int s)
    {
        this->i = i;
        this->j = j;
        score = s;
    }

    static bool compare (const SudokuUnit & lhs, const SudokuUnit &rhs)
    {
        return lhs.score < rhs.score;
    }

};


//template <typename T>
class toString
{
public:
    string operator ()(set<char> s)
    {
        //string ret = "";
        stringstream ss;
         for_each(s.begin(), s.end(), [&ss](char c){ ss << c << "\t"; });
        return ss.str();
    }
};

struct CompareSudokuUnit
{
    bool operator () (const SudokuUnit & lhs, const SudokuUnit &rhs)
    {
        return lhs.score < rhs.score;
    }
};

class Sudoku : public solution
{

public:
    static bool is_sudoku_element_valid(set<char> & s, const char & c)
    {
        if (c == '.')
            return true;
        else if (c >= '1' && c <= '9')
        {
            if(s.find(c) != s.end())
            {
                return false;
            }
            else
            {
                //s.insert(c);
                return true;
            }
        }
        return false;
    }

    // check 3*3 square start at v[i][j] is valid
    static bool is_sudoku_sq_valid(const vector<vector<char>> & v, int i, int j)
    {
        set<char> sqSet;
        for(int p = i; p < i + 3; p++)
        {
            for(int q = j; q < j + 3; q++)
            {
                if(is_sudoku_element_valid(sqSet, v[p][q]))
                {
                    sqSet.insert(v[p][q]);
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool isValidSudoku()
    {
        return isValidSudoku(v);
    }

    static bool isValidSudoku(vector<std::vector<char> > &v)
    {

        if(v.size() != 9) return false;

        // first scan all rows
        for(auto it = v.begin(); it != v.end(); it++)
        {
            vector <char> & row = *it;
            if(row.size() != 9) return false;
            set<char> rowSet;
            for(auto iit = row.begin(); iit != row.end(); iit++)
            {
                char & c = *iit;
                if(is_sudoku_element_valid(rowSet, c))
                {
                    rowSet.insert(c);
                }
                else
                    return false;
            }

        }

        // check the cols
        for(int i = 0; i < 9; i++)
        {
            set<char>colSet;
            for(int j = 0; j < 9; j++)
            {
                char & c = v[j][i];
                if(is_sudoku_element_valid(colSet, c))
                {
                    colSet.insert(c);
                }
                else
                {
                    return false;
                }
            }
        }


        // now check all 9 squares
        for(int i = 0; i < 9; i = i + 3)
        {
            //set<char>sqSet;
            for(int j = 0; j < 9; j = j + 3)
            {
                if(is_sudoku_sq_valid(v, i, j) == false)
                    return false;
            }
        }

        return true;
    }


public:
    Sudoku(vector<vector<char>> &v)
    {
        this->v = v;
    }

    typedef priority_queue < SudokuUnit, vector<SudokuUnit>, CompareSudokuUnit > ScoreQuene;
    Sudoku() {};

    Sudoku(vector<vector<char>> &v, ScoreQuene &q)
    {
        this->v = v;
        this->scoreQueue = q;
    }

    vector<vector<char>> v;
    //int scoreMap[3][9];
    ScoreQuene scoreQueue;

    void print()
    {
        for (auto i = v.begin(); i != v.end(); i++)
        {
            for(auto j = i->begin(); j != i->end(); j++)
            {
                cout << *j << "\t";       
            }
            cout << endl;
        }
    }

    static void Solve(Sudoku & s)
    {
        int maxScore;
        if (s.scoreQueue.empty())
        {
            maxScore = s.getMaxScore().score;
        }

        if(maxScore == 0) {
            s.print();
            return;
        }

        SudokuUnit u = s.scoreQueue.top();
        //s.scoreQueue.pop();

        // sq
        if (u.i != -1 && u.j != -1)
        {
                        //for (auto c = a.begin(); c != a.end(); c++)
                        //{
                        //    Sudoku n(s.v, s.scoreQueue);
                        //}
        }
        // row
        else if (u.i != -1)
        {

        }
        // col
        else
        {

        }
    }


    set<char> getPossible(int i, int j)
    {
        set<char> a({ '1', '2', '3', '4', '5', '6', '7', '8', '9' });

        int sq_i = (i / 3) * 3;
        int sq_j = (j / 3) * 3;


        for (int m = sq_i; m < sq_i + 3; m++)
        {
            for (int n = sq_j; n < sq_j + 3; n++)
            {
                if (v[m][n] != '.') a.erase(v[m][n]);
            }
        }

        for_each(v[i].begin(), v[i].end(), [&a](char i){ if (i != '.') a.erase(i); });

        for_each(v.begin(), v.end(), [&a, &j](vector<char>& s) {if (s[j] != '.') a.erase(s[j]); });

        return a;
    }

    SudokuUnit getMaxScore()
    {
        int maxScore  = 0;
        int posI = -1;
        int posJ = -1;

        // score of rows
        for(int i = 0;  i < 9; i++)
        {
            int s = getRowScore(i);
            scoreQueue.emplace(i, -1, s);
            if (s > maxScore)
            {
                maxScore = s;
                posI = i;
                posJ = -1;
            }
        }

        for(int i = 0;  i < 9; i++)
        {
            int s = getColScore(i);
            scoreQueue.emplace(-1, i, s);
            if (s > maxScore)
            {
                maxScore = s;
                posJ = i;
                posI = -1;
            }
        }

        for(int i = 0; i < 9; i = i + 3)
        {
            for (int j = 0; j < 9; j = j + 3)
            {
                int s = getSqScore(i, j);
                scoreQueue.emplace(i, j, s);
                if(s >= maxScore)
                {
                    maxScore = s;
                    posI = i;
                    posJ = j;
                }
            }
        }

        return SudokuUnit(posI, posJ, maxScore);
    }

    int getRowScore(int i)
    {
        int score = 0;
        for_each(v[i].begin(), v[i].end(), [&score](const char & c){ if (c == '.') score++;}
            );
        return score;
    }

    int getColScore(int i)
    {
        int score = 0;
        for(vector<char> & row : v)
        {
            if(row[i] == '.') score++;
        }
        return score;
    }

    int getSqScore(int i, int j)
    {
        int score = 0;

        for (int p = i; p < i + 3; p++)
        {
            for (int q = j; q < j + 3; q++)
            {
                if(v[p][q] == '.')
                {
                    score++;
                }
            }
        }


        return score;
    }

    void test()
    {
        vector<vector<char>> v;

        v.push_back({'5',    '3',    '.',    '.',    '7',    '.',    '.',    '.',    '.'});
        v.push_back({'6',    '.',    '.',    '1',    '9',    '5',    '.',    '.',    '.'});
        v.push_back({'.',    '9',    '8',    '.',    '.',    '.',    '.',    '6',    '.'});
        v.push_back({'8',    '.',    '.',    '.',    '6',    '.',    '.',    '.',    '3'});
        v.push_back({'4',    '.',    '.',    '8',    '.',    '3',    '.',    '.',    '1'});
        v.push_back({'7',    '.',    '.',    '.',    '2',    '.',    '.',    '.',    '6'});
        v.push_back({'.',    '6',    '.',    '.',    '.',    '.',    '2',    '8',    '.'});
        v.push_back({'.',    '.',    '8',    '4',    '1',    '9',    '.',    '.',    '5'});
        v.push_back({'.',    '.',    '.',    '.',    '8',    '.',    '.',    '7',    '9'});


        Sudoku s(move(v));
        s.print();
        /*cout << s.isValidSudoku() << endl;
        for (int i = 0; i < 9; i++)
            cout << s.getRowScore(i) << "\t";
        cout << endl;
        for (int i = 0; i < 9; i++)
            cout << s.getColScore(i) << "\t";
        cout << endl;
        for (int i = 0; i < 9; i = i + 3)
            for (int j = 0; j < 9; j = j + 3)
                cout << "(" << i << ", " << j << ")=" << s.getSqScore(i, j) << endl;*/

        toString ts;
        string s1(ts(s.getPossible(0, 0)));
        cout << "Possible for (0,0)" << s1 << endl;
        cout << "Possible for (8,8)" << ts(s.getPossible(8, 8)) << endl;
    }

};


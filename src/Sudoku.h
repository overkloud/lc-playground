#include "Solution.h"


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
            for(int j = 0; j < 0; j++)
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
    Sudoku(const vector<vector<char>> &&v)
    {
        this->v = v;
    }

    Sudoku() {};

    vector<vector<char>> v;

    int scoreMap[3][9];


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
        int maxScore = s.getMaxScore();

        if(maxScore == 0) {
            s.print();
            return;
        }

        
    }

    int getMaxScore()
    {
        int maxScore  = 0;

        // score of rows
        for(int i = 0;  i < 9; i++)
        {
            int s = getRowScore(i);
            if(s > maxScore)
                maxScore = s;
        }

        for(int i = 0;  i < 9; i++)
        {
            int s = getColScore(i);
            if(s > maxScore)
                maxScore = s;
        }

        for(int i = 0; i < 9; i = i + 3)
        {
            for (int j = 0; j < 9; j = j + 3)
            {
                int s = getSqScore(i, j);
                if(s >= maxScore)
                {
                    maxScore = s;
                }
            }
        }

        return maxScore;
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
                if(q == '.')
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
        v.push_back({'.',    '.',    '.',    '4',    '1',    '9',    '.',    '.',    '5'});
        v.push_back({'.',    '.',    '.',    '.',    '8',    '.',    '.',    '7',    '9'});


        Sudoku s(move(v));
        s.print();
        cout << s.isValidSudoku() << endl;
    }

};


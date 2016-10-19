#include "Solution.h"
#include <queue>
#include <list>
#include <sstream>
#include <chrono>

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

    vector<pair<int, int>> getAllV()
    {

        vector<pair<int, int>> ret;
        if(i == -1)
        {
            for(int k = 0; k < 9; k++)
            {
                ret.push_back(make_pair(k, j));
            }
        }

        else if (j == -1)
        {
            for(int k = 0; k < 9; k++)
            {
                ret.push_back(make_pair(i, k));
            }
        }

        else
        {
            for(int p = i; p < i + 3; p++)
            {
                for (int q = j; q < j + 3; q++)
                {
                    ret.push_back(make_pair(p, q));
                }
            }
        }

        return ret;
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

    Sudoku(vector<vector<char>> v, int i, int j, char c)
    {
        this->v = v;
        this->v[i][j] = c;
    }

    // typedef priority_queue < SudokuUnit, vector<SudokuUnit>, CompareSudokuUnit > ScoreQuene;
    Sudoku() {};

    // Sudoku(vector<vector<char>> &v, ScoreQuene &q)
    // {
    //     this->v = v;
    //     this->scoreQueue = q;
    // }

    vector<vector<char>> v;
    //int scoreMap[3][9];
    // ScoreQuene scoreQueue;

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

    char getV(pair<int, int> p)
    {
        return v[p.first][p.second];
    }

    string toString()
    {
        stringstream ss;
        for(int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                ss << v[i][j];
            }
        }

        return ss.str();
    }

    static vector<vector<char>> Solve(Sudoku & s)
    {
        //int visited [9][9][9];
        set<string> visited;

        int searched = 0;
        int skipped = 0;
        size_t total = 0;

        typedef vector<vector<char>> SV;
        std::list<Sudoku> Q;


        Q.push_back(s);

        while(!Q.empty())
        {
            Sudoku &v = Q.front();
            //Q.pop_front();
            SudokuUnit su = v.getMinScore();
            //cout << "Solving: " << su.i << "\t" << su.j << "\t" << su.score << endl;
            //v.print();
            if(su.score == 9*9)
            {
                cout << "======================"<< endl;
                v.print();

                cout << total << ":\t " << skipped << "/" << searched << endl;
                return v.v;
            }
            vector<pair<int, int>> p = su.getAllV();
            for (auto it = p.begin(); it != p.end(); it++)
            {
                if(v.getV(*it) != '.') continue;

                //if(!visited[it->first][it->second])
                {
                    vector<char> possible = v.getPossible(it->first, it->second);
                    total += possible.size();
                    for(auto ij = possible.begin(); ij != possible.end(); ij++)
                    {
                        {
                            //cout << "(" << it->first << "," << it->second << ") = " << *ij << endl; 
                            Sudoku newS (v.v, it->first, it->second, *ij);
                            if(su.score <= 3)
                            {
                                string key = newS.toString();
                                if(visited.find(key) == visited.end())
                                {
                                    visited.insert(key);
                                }
                                else
                                {
                                    skipped++;
                                    continue;
                                }
                            }
                            
                            //newS.print();
                            Q.push_back(newS);
                            searched++;
                            //visited[it->first][it->second][c] = 1;   
                        }
                       
                    }
                    //visited[it->first][it->second] = 1;
                }
            }
            Q.pop_front();
        }
        return s.v;
    }


    vector<char> getPossible(int i, int j)
    {
        //set<char> a({ '1', '2', '3', '4', '5', '6', '7', '8', '9' });

        char a[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        int sq_i = (i / 3) * 3;
        int sq_j = (j / 3) * 3;


        for (int m = sq_i; m < sq_i + 3; m++)
        {
            for (int n = sq_j; n < sq_j + 3; n++)
            {
                //if (v[m][n] != '.') a.erase(v[m][n]);
                if (v[m][n] != '.') a[v[m][n] - '1'] = '0';
            }
        }

        //for_each(v[i].begin(), v[i].end(), [&a](char i){ if (i != '.') a.erase(i); });
        for_each(v[i].begin(), v[i].end(), [&a](char i) { if (i != '.') a[i - '1'] = '0'; });

        for_each(v.begin(), v.end(), [&a, &j](vector<char>& s) {if (s[j] != '.') a[s[j] - '1'] = '0'; });


        vector<char> s;
        for (char i : a)
        {
            if (i != '0') s.push_back(i);
        }
        return s;
    }

    SudokuUnit getMinScore()
    {
        int minScore = 9 * 9;
        int posI = -1;
        int posJ = -1;

        // score of rows
        for (int i = 0; i < 9; i++)
        {
            int s = getRowScore(i);
            //scoreQueue.emplace(i, -1, s);
            if (s > 0 && s < minScore)
            {
                minScore = s;
                posI = i;
                posJ = -1;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            int s = getColScore(i);
            //scoreQueue.emplace(-1, i, s);
            if (s > 0 && s < minScore)
            {
                minScore = s;
                posJ = i;
                posI = -1;
            }
        }

        for (int i = 0; i < 9; i = i + 3)
        {
            for (int j = 0; j < 9; j = j + 3)
            {
                int s = getSqScore(i, j);
                //scoreQueue.emplace(i, j, s);
                if (s > 0 && s < minScore)
                {
                    minScore = s;
                    posI = i;
                    posJ = j;
                }
            }
        }

        return SudokuUnit(posI, posJ, minScore);
    }

    int getRowScore(int i)
    {
        int score = 0;
        for_each(v[i].begin(), v[i].end(), [&score](const char & c) { if (c == '.') score++; }
        );
        return score;
    }

    int getColScore(int i)
    {
        int score = 0;
        for (vector<char> & row : v)
        {
            if (row[i] == '.') score++;
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
                if (v[p][q] == '.')
                {
                    score++;
                }
            }
        }


        return score;
    }


    bool solve_bt (vt<vt<char>> & v, int count )
    {
        if (count == 9*9)
        {
            cout << "--------------***-----------------" << endl;
            print();
            return true;
        }
        //cout << "-------------------------------" << endl;
        //print();
        //cout << count << endl;
        int maxPossible = 9;

        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                if (v[i][j] == '.')
                {
                    auto possibles = getPossible(i, j);
                    maxPossible = std::min((int)possibles.size(), maxPossible);
                }
            }
        }
        
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                if (v[i][j] == '.')
                {
                    auto possibles = getPossible(i, j);
                    if (possibles.size() == 0) return false;
                    if ((int)possibles.size() <= maxPossible)
                    {
                        for (auto c : possibles)
                        {
                            //cout << "(" << i << "," << j << ")=" << c << endl;
                            v[i][j] = c;
                            if (solve_bt(v, count + 1))
                            {
                                return true;
                            }
                            else
                            {
                                v[i][j] = '.';
                            }
                        }
                        return false;
                    }
                }
            }
        }

        return false;
    }


    void solve_bt(vt<vt<char>> & v)
    {
        assert(v.size() == 9 && v[0].size() == 9);
        this->v = v;
        int count = 0;
        for (auto row : v)
        {
            for (auto c : row)
            {
                if (c != '.')
                {
                    count++;
                }
            }
        }

        solve_bt(this->v, count);
    }


    void test()
    {
        vector<vector<char>> v;

        v.push_back({'.',    '.',    '.',   '.',    '.',    '8',    '.',    '.',    '7'});
        v.push_back({'.',    '2',    '.',   '.',    '.',    '.',    '9',    '8',    '.'});
        v.push_back({'.',    '5',    '.',   '.',    '4',    '.',    '.',    '.',    '3'});
        v.push_back({'.',    '6',    '.',   '.',    '5',    '3',    '.',    '.',    '.'});
        v.push_back({'9',    '.',    '.',   '2',    '.',    '6',    '.',    '.',    '4'});
        v.push_back({'.',    '.',    '.',   '4',    '1',    '.',    '.',    '5',    '.'});
        v.push_back({'5',    '.',    '.',   '.',    '7',    '.',    '.',    '9',    '.'});
        v.push_back({'.',    '3',    '7',   '.',    '.',    '.',    '.',    '2',    '.'});
        v.push_back({'8',    '.',    '.',   '1',    '.',    '.',    '.',    '.',    '.'});

        vt<vt<char>> v1(v);
        vt<vt<char>> v2(v);
        Sudoku s_org(v1);
        Sudoku s_bt(v2);

        testUtil::timer t;
        t.start();
        Sudoku::Solve(s_org);
        std::cout << "Original method took " << t.stop() << " ms." << endl;
        t.reset();
        s_bt.solve_bt(v2);
        std::cout << "BT method took " << t.stop() << " ms." << endl;

        v.clear();
        v.push_back({'.',    '.',    '.',   '.',    '.',    '7',    '.',    '.',    '9'});
        v.push_back({'.',    '4',    '.',   '.',    '8',    '1',    '2',    '.',    '.'});
        v.push_back({'.',    '.',    '.',   '9',    '.',    '.',    '.',    '1',    '.'});
        v.push_back({'.',    '.',    '5',   '3',    '.',    '.',    '.',    '7',    '2'});
        v.push_back({'2',    '9',    '3',   '.',    '.',    '.',    '.',    '5',    '.'});
        v.push_back({'.',    '.',    '.',   '.',    '.',    '5',    '3',    '.',    '.'});
        v.push_back({'8',    '.',    '.',   '.',    '2',    '3',    '.',    '.',    '.'});
        v.push_back({'7',    '.',    '.',   '.',    '5',    '.',    '.',    '4',    '.'});
        v.push_back({'5',    '3',    '1',   '.',    '7',    '.',    '.',    '.',    '.'});
        v1 = v;
        v2 = v;
        Sudoku s_org2(v1);
        Sudoku s_bt2(v2);
        t.reset();
        Sudoku::Solve(s_org2);
        std::cout << "Original method took " << t.stop() << " ms." << endl;
        t.reset();
        s_bt2.solve_bt(v2);
        std::cout << "BT method took " << t.stop() << " ms." << endl;
    }

};


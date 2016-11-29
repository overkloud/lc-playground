#include "Solution.h"

using namespace std;

class SumQuery2DMutable: public  solution {

public:

    class TwoDBIT
    {
    public:
        TwoDBIT(vvint &v)
        {
            if (v.size())
            {
                max_x = calcSize(v.size());
                max_y = calcSize(v[0].size());

                t = new vector<vint>(max_x + 1, vector<int>(max_y + 1, 0));
                for (szt i = 0; i < v.size(); i++)
                {
                    for (szt j = 0; j < v[0].size(); j++)
                    {
                        update(i, j, v[i][j]);
                    }
                }
            }
        }

        // read cumulative val of (x,y)
        // x and y are 0 index'd
        int read(int x, int y)
        {
            x++; y++;
            int sum = 0;
            while (x > 0 && x <= max_x)
            {
                szt y1 = y;
                while (y1 > 0 && y1 <= max_y)
                {
                    sum += (*t)[x][y1];
                    y1 -= (y1 & -y1);
                }
                x -= (x & -x);
            }
            return sum;
        }

        int readSingle(int x, int y)
        {
            int sum = 0;
            if (x >= 0 && x < max_x && y >= 0 && y < max_y)
            {
                sum = read(x, y);
                if (x - 1 >= 0)
                {
                    sum -= read(x - 1, y);
                    if (y - 1 >= 0)
                    {
                        sum += read(x-1, y - 1);
                    }
                }
                if (y - 1 >= 0)
                {
                    sum -= read(x, y - 1);
                }
            }
            return sum;
        }

        void update(szt x, szt y, int val)
        {
            x++; y++;
            szt y1;
            while (x <= max_x)
            {
                // update y
                y1 = y;
                while (y1 <= max_y)
                {
                    (*t)[x][y1] += val;
                    y1 += (y1 & -y1);
                }
                x += (x & -x);
            }
        }

        void debug()
        {
            print(*t);
        }

    private:
        vvint *t;
        szt max_x = 0;
        szt max_y = 0;
        szt calcSize(const szt n)
        {
            return (szt)std::pow(2, (szt)std::ceil(log(n) / log(2)));
        }

    };

    class NumMatrix {
    public:
        NumMatrix(vector<vector<int>> &matrix) {
            bt = new TwoDBIT(matrix);
        }

        void update(int row, int col, int val) {
            //bt->debug();
            int diff = val - bt->readSingle(row, col);
            bt->update(row, col, diff);
            //bt->debug();
        }

        int sumRegion(int row1, int col1, int row2, int col2) {
            if (row2 >= row1 && col2 >= col1 && row1 >=0 && col1>=0)
            {
                int sum = bt->read(row2, col2);
                if (row1 - 1 >= 0)
                {
                    sum -= bt->read(row1 - 1, col2);
                    if (col1 - 1 >= 0)
                    {
                        sum += bt->read(row1 - 1, col1 - 1);
                    }
                }
                if (col1 - 1 >= 0)
                {
                    sum -= bt->read(row2, col1 - 1);
                }
                return sum;
            }
            return 0;
        }
    private:
        TwoDBIT * bt;
    };



    virtual void test()
    {
        vvint a = {
            { 1, 0, 1, 4, 2 },
            { 5, 6, 3, 2, 1 },
            { 1, 2, 0, 1, 5 },
            { 4, 1, 0, 1, 7 },
            { 1, 0, 3, 0, 5 }
        };
        //TwoDBIT tbt(a);
        NumMatrix m(a);
        assert(8 == m.sumRegion(2, 1, 4, 3 ));
        m.update(3, 2, 2);
        assert(10 == m.sumRegion(2, 1, 4, 3 ));

        vvint a2;
        NumMatrix m2(a2);
        assert(0 == m2.sumRegion(2, 1, 4, 3 ));
        m2.update(3, 2, 2);
        assert(0 == m2.sumRegion(2, 1, 4, 3 ));

        vvint a3 = { {1,2,3,4,5} };
        NumMatrix m3(a3);
        assert(0 == m3.sumRegion(2, 1, 4, 3));
        assert(10 == m3.sumRegion(0, 0, 0, 3));
        m3.update(3, 2, 2);
        assert(0 == m3.sumRegion(2, 1, 4, 3));
        assert(10 == m3.sumRegion(0, 0, 0, 3));
        m3.update(0, 0, 2);
        assert(0 == m3.sumRegion(2, 1, 4, 3));
        assert(11 == m3.sumRegion(0, 0, 0, 3));
    }
};

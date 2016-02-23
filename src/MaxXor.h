#include "Solution.h"

using namespace std;

class MaxXor: public  solution {

public:

    int max(int a, int b)
    {
        assert(a <= 1024 && b <= 1024);

        if (a == b) return 0;

        int shift = 10;
        int i = 1;
        int x, y;
        do {
            x = a >> (shift - i);
            y = b >> (shift - i);
            i++;
        } while (x == y && i<=9);
        

        return (int)pow(2, shift - i + 2) - 1;
    }

    int max2(int a, int b)
    {
        int max = 0;
        for (int i = a; i < b; i++)
        {
            for (int j = i + 1; j <= b; j++)
            {
                max = std::max(max, j^i);
            }
        }
        return max;
    }

    void run(istream & in)
    {
        int l = readInt(in);
        int r = readInt(in);
        cout << max(l, r) << endl;
        cout << max2(l, r) << endl;
    }
};

#include "Solution.h"

using namespace std;

class CurrencyArb: public  solution {

public:

    virtual void run(istream & in)
    {
        int n = readInt(in);
        for (int i = 0; i < n; i++)
        {
            vector<double> vin = readDoubles(in);
            double sum = 100000;
            for (double i : vin)
            {
                sum /= i;
            }

            if (sum > 100000)
            {
                ll profit = (ll)sum - 100000;
                if (sum - 100000 - profit >= 0.5)
                    profit++;
                cout << profit << endl;
            }
            else cout << 0 << endl;

        }
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};

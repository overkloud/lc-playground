#include "Solution.h"

using namespace std;


//Say you have an array for which the ith element is the price of a given stock on day i.
//
//Design an algorithm to find the maximum profit.You may complete as many transactions as you like
//(ie, buy one and sell one share of the stock multiple times).However, you may not engage in multiple transactions at the same time(ie, you must sell the stock before you buy again).
class BuySellStockII : public  solution {
private:
    BuySellStockII(const solution&){};
public:
    BuySellStockII(){};

    int maxProfit(vector<int> &&prices) {
        int sum = 0;
        bool hasStock = false;
        int buyPrice = 0;

        if (prices.empty()) return 0;

        for (unsigned int i = 0; i < prices.size() - 1; i++)
        {
            int today = prices[i];
            int tmr = prices[i + 1];

            if (!hasStock)
            {
                if (today <= tmr)
                {
                    buyPrice = today;
                    hasStock = true;
                }
            }

            else
            {
                if (today > tmr)
                {
                    sum += (today - buyPrice);
                    buyPrice = -1;
                    hasStock = false;
                }
            }
        }

        if (hasStock)
        {
            sum += (prices[prices.size() - 1] - buyPrice);
        }

        return sum;
    }

    virtual void test()
    {
        assert(maxProfit({  }) == 0);
        assert(maxProfit({ 0 }) == 0);
        assert(maxProfit({ 0, 1, 2 }) == 2);
        assert(maxProfit({ 2, 1, 0 }) == 0);
        assert(maxProfit({ 0, 2, 4, 2, 0 ,4 }) == 8);
    }
};

#include "Solution.h"

using namespace std;
using namespace dataStructure;
class SumQueryMutable: public  solution {

public:
    
    class NumArray {
    public:
        BIT* bt;
        NumArray(vector<int> &nums) {
            bt = new BIT(nums);
        }

        void update(int i, int val) {
            int prev = bt->readSingle(i);
            int diff = val - prev;
            bt->update(i, diff);
        }

        int sumRange(int i, int j) {
            if (i <= j)
            {
                return bt->read(j) - bt->read(i) + bt->readSingle(i);
            }
            return 0;
        }
    };

    virtual void test()
    {
        vint v = {1,3,5,100};
        NumArray ar(v);
        assert(9 == ar.sumRange(0, 2));
        ar.update(1, 2);
        assert(8 == ar.sumRange(0, 2));
        assert(0 == ar.sumRange(4, 2));

        vint v2 = {};
        NumArray ar2(v2);
        assert(0 == ar2.sumRange(0, 2));
        ar2.update(2, 100);
        assert(0 == ar2.sumRange(0, 2));
    }
};

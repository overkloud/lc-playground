// LeetCodeSolutions.cpp : Defines the entry point for the console application.
//

#include <iostream>


#include "Solution.h"
#include "BuyStock.h"
#include "ClimbStairs.h"
#include "PascalTree.h"
#include "MaxDepth.h"
#include "SearchInsertPosition.h"
#include "SingleNumber.h"
#include "IsSameTree.h"
#include "ReverseInteger.h"
#include "AddTwoNumbers.h"
#include "Sudoku.h"
#include "LongestParenthese.h"
#include "GrayCode.h"
#include "KthSmallest.h"
#include "SampleHeader.h"

using namespace std;

class NextRightPointer : public solution
{
public:
    struct TreeLinkNode {
        int val;
        TreeLinkNode *left, *right, *next;
        TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
        
    };

    void connect(TreeLinkNode *root) {

    }

};

class TestTemplate
{
public: 

    vector<shared_ptr<solution>> tests;

    TestTemplate()
    {
        //t.test();
    }

    void runTest()
    {
        for (int i = 0; i < tests.size(); i++)
        {
            tests[i]->test();
        }
    }


    template <typename T>
    void addTest(bool add = true)
    {
        T t;
        if (add)
        {
            tests.push_back(make_shared<T>(t));
        }
    }
};


int main(int argc, char * argv[])
{
    TestTemplate tt;
    tt.addTest<BuySellStockII>(false);
    tt.addTest<SearchInsertPosition>(false);
    tt.addTest<ClimbStairs>(false);
    tt.addTest<AddTwoNumbers>(false);
    tt.addTest<Sudoku>(false);
    tt.addTest<LongestParenthese>(false);
    tt.addTest<GrayCode>(false);
    tt.addTest<KthSmallest>(true);
    tt.runTest();
    return 0;
}


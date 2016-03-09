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
#include "MissingNumber.h"
#include "LongestParenthese.h"
#include "GrayCode.h"
#include "KthSmallest.h"
#include "TimeConversion.h"
#include "SearchGrid.h"
#include "MatrixRotation.h"
#include "QuickSort.h"
#include "ExtraLongFactorials.h"
#include "CountSort.h"
#include "InsertSort.h"
#include "FixTheCircle.h"
#include "TwoRobots.h"
#include "ScalarProduct.h"
#include "SumMinInterval.h"
#include "MaxSumModuleSubarray.h"
#include "TwoEqualSubArrays.h"
#include "SimilarPair.h"
#include "HuffmanDecode.h"
#include "SwapNodes.h"
#include "MaxXor.h"
#include "Cipher.h"
#include "FriendCircle.h"
#include "LongestChain.h"
#include "QHeap1.h"
#include "SampleHeader.h"
#include "FindMinInRotateSortedArray.h"
#include "RotateImage.h"
#include "UniquePaths.h"
#include "Permutation.h"
#include "NextRightNode.h" 


using namespace std;

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

#ifdef _WIN32
LARGE_INTEGER testUtil::timer::Frequency;
#endif

int main(int argc, char * argv[])
{
    if (argc <= 1) {
        TestTemplate tt;
        tt.addTest<BuySellStockII>(false);
        tt.addTest<SearchInsertPosition>(false);
        tt.addTest<ClimbStairs>(false);
        tt.addTest<AddTwoNumbers>(false);
        tt.addTest<Sudoku>(false);
        tt.addTest<LongestParenthese>(false);
        tt.addTest<GrayCode>(false);
        tt.addTest<KthSmallest>(false);
        tt.addTest<MissingNumber>(false);
        tt.addTest<FindMinInRotateSortedArray>(false);
        tt.addTest<RotateImage>(false);
        tt.addTest<UniquePaths>(false);
        tt.addTest<Permutation>(false);
        tt.addTest<KthSmallest>(false);
        tt.addTest<MatrixRotation>(false);
        tt.addTest<QuickSort>(false);
        tt.addTest<ExtraLongFactorials>(false);
        tt.addTest<CountSort>(false);
        tt.addTest<InsertSort>(false);
        tt.addTest<FixTheCircle>(false);
        tt.addTest<TwoRobots>(false);
        tt.addTest<ScalarProduct>(false);
        tt.addTest<SumMinInterval>(false);
        tt.addTest<MaxSumModuleSubarray>(false);
        tt.addTest<TwoEqualSubArrays>(false);
        tt.addTest<SimilarPair>(false);
        tt.addTest<HuffmanDecode>(false);
        tt.addTest<SwapNodes>(false);
        tt.addTest<Cipher>(false);
        tt.addTest<MaxXor>(false);
        tt.addTest<FriendCircle>(false);
        tt.addTest<LongestChain>(false);
        tt.addTest<QHeap1>(true);
        tt.addTest<Sample>(false);
        tt.runTest();
    }
    else
    {
        string arg1(argv[1]);
        cout << "here" << endl;
        if (arg1 == "--random")
        {
            int size = atoi(argv[2]);
            int range= atoi(argv[3]);
            testUtil::randomGen(size, range);
            //print(v);
        }
    }
    return 0;
}


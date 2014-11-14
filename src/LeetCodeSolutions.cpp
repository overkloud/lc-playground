// LeetCodeSolutions.cpp : Defines the entry point for the console application.
//
#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <queue>
#include <cmath>
#include <memory>


using namespace std;

class BuySellStockII;

class solution
{
public:
    virtual void test(){};
    solution(){};
//private:
    solution(const BuySellStockII &){};
    solution & operator = (const BuySellStockII &){};
};


class SingleNumber : public  solution {
    /***
    Given an array of integers, every element appears twice except for one. Find that single one.
    Note:
    Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
    ***/
public:
    int singleNumber(int A[], int n) {
        using namespace std;
        map<int, int> m;

        int min = 0;
        for (int i = 0; i < n; i++)
        {
            if (A[i] < min) min = A[i];
        }
        min--;

        for (int i = 0; i < n; i++)
        {
            if (m.find(A[i]) == m.end())
            {
                m[A[i]] = i;
            }
            else
            {
                int pos = m.find(A[i])->second;
                A[i] = min;
                A[pos] = min;
            }
        }

        int ret;
        for (int i = 0; i < n; i++)
        {
            if (A[i] != min) ret = A[i];
        }

        return ret;
    }

    void test()
    {
        //std::vector<std::tuple<std::initializer_list<int>, int, int> >tests;
        //int y[] = (int[]){ 1, 2, 33 };
        //tests.emplace_back(std::initializer_list<int>({ 1, 2, 3 }), 1, 1);

        
        assert(-1 == singleNumber(std::vector < int > {-1}.data(), 1));
        assert(1 == singleNumber(std::vector < int > {1, 2, 2}.data(), 3));
        assert(0 == singleNumber(std::vector < int > {1, 0, -2, 1, -2}.data(), 5));
        //assert(-1 == singleNumber(std::vector < int > {-1}.data(), 1));
    }

};


/**
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class MaxDepth : public  solution {
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

public:
    int maxDepth(TreeNode *root) {
        using namespace std;
        root->val = 1;
        queue<TreeNode*> Q;
        Q.push(root);
        int maxDepth = 1;
        while (!Q.empty())
        {
            auto node = Q.front();
            Q.pop();
            auto left = node->left;
            auto right = node->right;

            if (left)
            {
                left->val = node->val + 1;
                Q.push(left);
                if (left->val > maxDepth) maxDepth = left->val;
            }
            if (right)
            {
                right->val = node->val + 1;
                Q.push(right);
                if (right->val > maxDepth) maxDepth = right->val;
            }
        }

        return maxDepth;
    }

    void test()
    {
        TreeNode t1(0); 
        assert(1 == maxDepth(&t1));


        TreeNode t2(0);
        TreeNode t3(0);
        TreeNode t4(0);
        t2.left = &t3;
        t2.right= &t4;
        assert(2 == maxDepth(&t2));
    }
};


/**
Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class IsSameTree : public  solution {
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        
    };
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        using namespace std;

        if (!p && !q) return true;
        if (p && !q) return false;
        if (q && !p) return false;
        
        queue<TreeNode *>  Q;
        Q.push(q);

        queue<TreeNode *>  P;
        P.push(p);
        while (!P.empty())
        {
            if (Q.empty()) return false;
            TreeNode * p_node = P.front();
            P.pop();
            TreeNode * q_node = Q.front();
            Q.pop();

            if (p_node->val != q_node->val) return false;

            if ((p_node->left && !q_node->left) || (!p_node->left && q_node->left))
            {
                return false;
            }

            if ((p_node->right && !q_node->right) || (!p_node->right && q_node->right))
            {
                return false;
            }

            if (p_node->left && q_node->left)
            {
                P.push(p_node->left);
                Q.push(q_node->left);
            }

            if (p_node->right && q_node->right)
            {
                P.push(p_node->right);
                Q.push(q_node->right);
            }

        }

        if (P.empty() && !Q.empty()) return false;

        return true;
    }

    void test()
    {
        TreeNode p1_1(1);
        TreeNode p1_2(2);
        TreeNode p1_3(3);
        p1_1.left = &p1_2;
        p1_1.right= &p1_3;


        TreeNode q1_1(1);
        TreeNode q1_2(2);
        TreeNode q1_3(3);
        q1_1.left =  &q1_2;
        q1_1.right = &q1_3;

        assert(isSameTree(&p1_1, &q1_1));

        p1_3.val = 0;
        assert(!isSameTree(&p1_1, &q1_1));

        q1_1.right = NULL;
        assert(!isSameTree(&p1_1, &q1_1));

        p1_2.left = &p1_3;
        p1_1.right = NULL;
        q1_2.left = &q1_3;

        assert(!isSameTree(&p1_1, &q1_1));

        p1_3.val = 3;
        assert(isSameTree(&p1_1, &q1_1));
        return;
    }
};



//Reverse digits of an integer.
//
//Example1: x = 123, return 321
//Example2 : x = -123, return -321
class ReverseInteger : public  solution {
public:
    int reverse(int x) {
        using namespace std;

        if (x == 0) return 0;

        
        bool negative = (x < 0);
        vector<int> V;

        if (negative) x = x * -1;

        int s = x;
        while (s != 0)
        {
            V.push_back(s % 10);
            s = s / 10;
        }

        int ret = 0;
        for (unsigned int i = 0; i < V.size(); i++)
        {
            const int power = V.size() - i - 1;
            ret = ret + (int)(V[i] * pow(10, power));
        }

        if (negative) ret = ret * -1;

        return ret;
    }


    void test()
    {
        assert(1 == reverse(1));
        assert(1 == reverse(100));
        assert(-1 == reverse(-100));
        assert(-123 == reverse(-321));
        assert(-123 == reverse(-3210));
    }
};



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

//Given a sorted array and a target value, return the index if the target is found.If not, return the index where it would be if it were inserted in order.
//
//You may assume no duplicates in the array.
//
//Here are few examples.
//[1, 3, 5, 6], 5 ¡ú 2
//[1, 3, 5, 6], 2 ¡ú 1
//[1, 3, 5, 6], 7 ¡ú 4
//[1, 3, 5, 6], 0 ¡ú 0

class SearchInsertPosition : public solution
{

public:
    int searchInsert(int A[], int n, int target) {
        int firstLargerPos = -1;

        if (n == 0) return 1;

        for (int i = 0; i < n; i++)
        {
            if (A[i] == target) return i;

            if (A[i] > target)
            {
                firstLargerPos = i;
                break;
            }
        }

        if (firstLargerPos == -1)
            return n;
        return firstLargerPos;
    }

    void test()
    {
        assert(1 == searchInsert(vector<int>({}).data(), 0, 5));
        assert(0 == searchInsert(vector<int>({1}).data(), 1, 0));
        assert(1 == searchInsert(vector<int>({ 1 }).data(), 1, 2));
        assert(2 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 5));
        assert(1 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 2));
        assert(4 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 7));
        assert(0 == searchInsert(vector<int>({ 1, 3, 5, 6 }).data(), 4, 0));
    }
};


/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
class ClimbStairs : public solution
{
public:
    int climbStairs(int n) {
        if (n == 0) return 0;

        if (n == 1)
            return 1;
        else if (n == 2)
            return 2;
        /*
        else
        {
            return climbStairs(n - 1) + climbStairs(n - 2);
        }*/


        vector <int> A;
        A.reserve(n);
        A.push_back(1);
        A.push_back(2);
        for (int i = 2; i < n; i++)
        {
            A.push_back(A[i - 1] + A[i - 2]);
        }

        return A[n - 1];
    }

    void test()
    {
        assert(0 == climbStairs(0));
        assert(1 == climbStairs(1));
        assert(2 == climbStairs(2));
        assert(3 == climbStairs(3));
        assert(5 == climbStairs(4));
        assert(8 == climbStairs(5));
    }
};



//Given numRows, generate the first numRows of Pascal's triangle.
//
//For example, given numRows = 5,
//Return
//
//[
//    [1],
//    [1, 1],
//    [1, 2, 1],
//    [1, 3, 3, 1],
//    [1, 4, 6, 4, 1]
//]
class PascalTree : public solution
{
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int>> V;

        for (int i = 1; i <= numRows; i++)
        {
            vector<int> row;

            double midPoint = i / 2.0;
            for (int j = 0; j < i; j++)
            {
                vector<int> lastRow = V.back();
                if (0 == j || i - 1 == j)
                {
                    row.push_back(1);
                    continue;
                }

                // odd number of elements in this row
                if (i % 2 == 1)
                {
                    if (j == floor(midPoint))
                    {
                        
                    }
                
                }
                else
                {

                }


            }
        }



        return V;
    }
};




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


int _tmain(int argc, _TCHAR* argv[])
{
    //SingleNumber s;
    //s.test();

    /*MaxDepth m;
    m.test();*/

    /*IsSameTree i;
    i.test();*/

    //ReverseInteger r;
    //r.test();

    //BuySellStockII bs2;
    //bs2.test();

    TestTemplate tt;
    tt.addTest<BuySellStockII>(false);
    tt.addTest<SearchInsertPosition>(false);
    tt.addTest<ClimbStairs>(true);
    
    tt.runTest();
    return 0;
}


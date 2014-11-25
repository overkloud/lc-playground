#include "Solution.h"


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



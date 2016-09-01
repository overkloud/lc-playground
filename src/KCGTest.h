#include "Solution.h"

using namespace std;

class KCGTest : public  solution {

public:

    int task1(vector< vector<int> > &A) {
        // write your code in C++11 (g++ 4.8.2)
        int N = A.size();
        if (0 == N) return 0;
        int M = A[0].size();
        if (0 == M)  return 0;


        int result = 0;
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < M - 1; j++) {
                if (i + 1 < N && i - 1 >= 0 && j + 1 < M && j - 1 >= 0)
                {
                    int cur = A[i][j];
                    int left = i - 1;
                    int right = i + 1;
                    int up = j - 1;
                    int down = j + 1;
                    if ((cur < A[left][j] && cur < A[right][j] && cur > A[i][up] && cur > A[i][down]) ||
                        (cur > A[left][j] && cur > A[right][j] && cur < A[i][up] && cur < A[i][down]))
                    {
                        result++;
                    }
                }
            }
        }
        return result;
    }

    int solution(vector< vector<int> > &A) {
        // write your code in C++11 (g++ 4.8.2)
        return task1(A);
    }


    struct tree {
        int x;
        tree *l; 
        tree * r;
        tree(int x, tree* l, tree* r)
        {
            this->x = x;
            this->l = l;
            this->r = r;
        }
    };

    int solution(tree * T) {
        // write your code in C++11 (g++ 4.8.2)
        return task2(T);
    }


    struct tree_with_height 
    {
        tree* t;
        int h;
        tree_with_height(tree *tree, int height) {
            this->t = tree;
            h = height;
        }

    };
    typedef tree_with_height twh;

    int task2(tree * T)
    {
        if (T == nullptr) return 0;

        int result = 1;
        queue<tree*> q;
        map<tree*, int> depth;
        q.push(T);
        //int MAX_NUM_NODE = 50000;
        //vector<int> v(MAX_NUM_NODE, -1);
        depth.emplace(T, 0);
        int height = 0;
        while (q.empty() == false)
        {
            tree* cur = q.front();
            q.pop();
            int dep = depth[cur];
            if (cur->l) {
                q.push(cur->l);
                depth.emplace(cur->l, dep + 1);
            }
            if (cur->r) {
                q.push(cur->r);
                depth.emplace(cur->r, dep + 1);
            }
            height = std::max(dep, height);
        }

        map<int, int> max;
        for (int i = 0; i < height; i++)
        {
            max.emplace(i, INT_MIN);
        }
        max[0] = T->x;
        stack<tree*> s;
        s.push(T);
        int prev_dep = -1;
        
        while (s.empty() == false)
        {
            tree* cur = s.top();
            s.pop();
            int dep = depth[cur];

            if (dep != 0)
            {
                int prev_max = max[dep - 1];
                if (cur->x >= prev_max)
                {
                    result++;
                    max[dep] = cur->x;
                }
                else
                {
                    max[dep] = prev_max;
                }
            }

            if (cur->l) s.push(cur->l);
            if (cur->r) s.push(cur->r);
            prev_dep = dep;
        }

        return result;
    }


    int calc(vector<int> & A, int n, int & K, int & diff, int & min, int &max)
    {
        if (n < 2) return 0;
        if (2 == n)
        {
            K = 0;
            diff = std::abs(A[0] - A[1]);
            if (A[0] < A[1])
            {
                min = 0;
                max = 1;
            }
            else
            {
                min = 1;
                max = 0;
            }
        }
        else
        {
            int min = 0; 
            int max = 0;
            int K = 0;
            int diff = 0;
            calc(A, n - 1, K, diff, min, max);
            int cur = A[n];

        }
    }

    int task3(vector<int> &A) {
        // write your code in C++11 (g++ 4.8.2)
        int min = INT_MAX;
        int max = INT_MIN;
        for (auto i : A)
        {
            if (i < min) min = i;
            if (i > max) max = i;
        }
        return abs(min - max);
    }


    virtual void test()
    {
        tree* t1 = new tree(8, 0, 0);
        tree* t2 = new tree(7, 0, 0);
        tree* t3 = new tree(2, t1, t2);
        tree* t4 = new tree(6, 0, 0);
        tree* t5 = new tree(8, t3, t4);
        int i = solution(t5);
    }



    virtual void test1()
    {
        vector<vint> a = { {0,1,9,3}, {7,5,8,3}, {9,2,9,4}, {4,6,7,1} };
        int i = solution(a);


         a = { { 0,1,9,3 }};
        i = solution(a);

         a = { { 0 } };
        i = solution(a);

         a = { { 0,1 }, {1,0} };
        i = solution(a);

        a = { { 0,0, 0},{0, 1,0 },{0,0,0} };
        i = solution(a);

        a = { { 0, 2, 0 },{ 0, 1, 0 },{ 0,2,0 } };
        i = solution(a);
    }
};

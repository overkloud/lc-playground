#include "Solution.h"

using namespace std;

class Permutation2: public  solution {

public:
    vint mediRes;
    vvint res;
    vector<vector<int> > permute_tree(vector<int> &num) {
        mediRes.clear();
        res.clear();
        sort(num.begin(), num.end());
        permuII2(num);
        return res;
    }

    void permuII2(vector<int> &num)
    {
        int m = (int)num.size();
        if (m == 1)
        {
            mediRes.push_back(num[0]);
            res.push_back(mediRes);
            //toStream(cout, mediRes);
            mediRes.pop_back();
            return;
        }
        for (int i = 0; i < m; i++)
        {
            while (i < m - 1 && num[i] == num[i + 1]) i++;
            mediRes.push_back(num[i]);
            vector<int> cur = num;
            cur.erase(cur.begin() + i);
            permuII2(cur);
            mediRes.pop_back();
        }
    }


    vvint result;
    int N;
    void permute(vint & v, int n)
    {
        static int i = 0;
        if (n == N)
        {
            //assert(vector_find<vint>(result, v) == result.end());
            result.push_back(v);
            //vector2Stream(cout, v);
        }
        else
        {
            set<int> s;
            for (int i = n; i < N; i++)
            {
                if(s.find(v[i]) == s.end())
                {
                    s.insert(v[i]);
                    swap(v[i], v[n]);
                    permute(v, n + 1);
                    swap(v[n], v[i]);
                }
            }
        }
    }

    vvint permute_recursive(vint & v)
    {
        result.clear();
        sort(v.begin(), v.end());
        N = (int)v.size();
        permute(v, 0);
        return result;
    }

    void helper(vector<vector<int> > &results,
        vector<int> &permutation,
        vector<int> &nums,
        vt<bool> &used) {
        if (nums.size() == permutation.size()) {
            results.push_back(permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            if (i > 0 && used[i - 1] == false && nums[i] == nums[i - 1]) {
                continue;
            }

            used[i] = true;
            permutation.push_back(nums[i]);
            helper(results, permutation, nums, used);
            permutation.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int> > permuteUnique(vector<int> &nums) {
        vector<vector<int> > results;
        vector<int> permutation;
        vt<bool> used(nums.size(), false);

        sort(nums.begin(), nums.end());

        helper(results, permutation, nums, used);
        return results;
    }

    virtual void test()
    {
        vint v1 = {1,1,2,2,3,3};
        //auto r1 = permute_slow(v1);
        auto r3 = permute_tree(v1);
        auto r1 = permute_recursive(v1);
        //cout << r1.size() << endl;

        assert(r3.size() == r1.size());
        for (auto i3 = r3.begin(); i3 != r3.end(); i3++)
        {
            assert(vector_find<vint>(r1, *i3) != r1.end());
        }
        //vint v2 = { 1,1,1,1,1,1,1,2,2,3,3,4,6};
        int NumTestCases = 5;
        for (int j = 7; j < 8; j++ ){
            range(NumTestCases)
            {
                cout << "------------------" << endl;
                vint v2 = testUtil::randomGen(12, j, false);
                vector2Stream<int>(cout, v2);
                testUtil::timer t;
                t.start();
                auto r2 = permute_tree(v2);
                cout << t.stop() << endl;
                t.reset();
                auto r1 = permute_recursive(v2);
                cout << t.stop() << endl;
                t.reset();
                auto r3 = permuteUnique(v2);
                cout << t.stop() << endl;

                //assert(r3 == r1);
                assert(r3.size() == r1.size());
                sort(r3.begin(), r3.end());
                sort(r1.begin(), r1.end());
                assert(r3 == r1);
                /*for (auto i3 = r3.begin(); i3 != r3.end(); i3++)
                {
                    assert(vector_find<vint>(r1, *i3) != r1.end());
                }*/
            }
        }
    }
};

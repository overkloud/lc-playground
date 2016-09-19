#include "Solution.h"

using namespace std;

class KPairsSmallestSum: public  solution {

public:


    //map<pair<int, int>, set<pair<int, int>, std::function<bool(const pair<int, int>&, const  pair<int, int> &)> >> M;
    //// this will return the index of the pairs not pairs itself
    //set<pair<int, int>, std::function<bool(const pair<int, int>&, const  pair<int, int> &)>> kSmallestPairs(vector<int>& v1, vector<int>& v2, int k, int s1, int e1, int s2, int e2) {
    //    std::function<bool(const pair<int, int>&, const  pair<int, int> &)> comp = [&v1, &v2](const pair<int, int> & l, const pair<int, int> & r) {
    //        if (v1[l.first] + v2[l.second] != v1[r.first] + v2[r.second])
    //            return v1[l.first] + v2[l.second] < v1[r.first] + v2[r.second];
    //        else return l < r;
    //    };

    //    set<pair<int, int>, decltype(comp)> result (comp);
    //    if (s1 < e1 && s2 < e2)
    //    {
    //        if (k == 1)
    //        {
    //            auto p = mkp(s1, s2);
    //            result.insert(p);
    //        }
    //        else
    //        {
    //            auto p = mkp(s1, s2);
    //            if (M.find(p) != M.end())
    //                result = M[p];
    //            else
    //            {
    //                result.insert(p); k--;
    //                auto p1 = mkp(s1 + 1, s2);
    //                auto p2 = mkp(s1, s2 + 1);
    //                if (M.find(p1) == M.end())
    //                {
    //                    M.emplace(p1, kSmallestPairs(v1, v2, k, s1 + 1, e1, s2, e2));
    //                }
    //                if (M.find(p2) == M.end())
    //                {
    //                    M.emplace(p2, kSmallestPairs(v1, v2, k, s1, e1, s2 + 1, e2));
    //                }
    //                auto k1 = M[p1];
    //                auto k2 = M[p2];
    //                const decltype(k1) & kvt1 = k1;
    //                const decltype(k2) & kvt2 = k2;
    //                auto  k1_start = kvt1.begin();
    //                for (auto it : kvt2)
    //                {
    //                    if (k == 0) break;
    //                    auto insertPosition = kvt1.lower_bound(it);
    //                    for (auto ij = k1_start; ij != insertPosition; ij++)
    //                    {
    //                        result.insert(*ij);
    //                        k--;
    //                        if (k == 0) break;
    //                    }
    //                    k1_start = insertPosition;
    //                    if (k > 0 && (insertPosition == kvt1.end() || (insertPosition != kvt1.end() && *insertPosition != it)))
    //                    {
    //                        result.insert(it);
    //                        k--;
    //                    }
    //                }

    //                while (k > 0 && k1_start != kvt1.end())
    //                {
    //                    result.insert(*k1_start);
    //                    k1_start++;
    //                    k--;
    //                }
    //                M.emplace(p, result);
    //            }
    //        }
    //    }

    //    return result;
    //}

    //vector<pair<int, int>> kSmallestPairs_slow(vector<int>& nums1, vector<int>& nums2, int k) {
    //    M.clear();
    //    auto r = kSmallestPairs(nums1, nums2, k, 0, nums1.size(), 0, nums2.size());
    //    vector<pair<int, int>> result;
    //    for (auto it : r)
    //    {
    //        result.push_back(mkp(nums1[it.first], nums2[it.second]));
    //    }

    //    return result;
    //}

    vector<pair<int, int>> kSmallestPairs_fast(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> result;
        if (nums1.empty() || nums2.empty() || k <= 0)
            return result;
        auto comp = [&nums1, &nums2](pair<int, int> a, pair<int, int> b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> min_heap(comp);
        min_heap.emplace(0, 0);
        while (k-- > 0 && min_heap.size())
        {
            auto idx_pair = min_heap.top(); min_heap.pop();
            result.emplace_back(nums1[idx_pair.first], nums2[idx_pair.second]);
            if (idx_pair.first + 1 < nums1.size())
                min_heap.emplace(idx_pair.first + 1, idx_pair.second);
            if (idx_pair.first == 0 && idx_pair.second + 1 < nums2.size())
                min_heap.emplace(idx_pair.first, idx_pair.second + 1);
        }
        return result;
    }


    typedef  pair<int, int> pii;
    typedef  tuple<int, int, int> tii;
    vector<pair<int, int>> kSmallestPairs_2(vector<int>& v1, vector<int>& v2, int k) {
        std::function <bool(const tii &, const tii &)> comp2 = [&v1, &v2](const tii &l, const tii &r){
            return std::get<0>(l) > std::get<0>(r);
        };
        pq<tii, vt<tii>, decltype(comp2)> q(comp2);

        vt<pii> result;
        szt size2 = v2.size();
        if (k != 0 && v1.size() != 0 && v2.size() != 0)
        {
            for (int i = 0; i < v1.size(); i++)
            {
                q.push(make_tuple(v1[i] + v2[0], i, 0));
            }
            ull count = std::min((ull)k, v1.size() * v2.size());
            while (result.size() < count)
            {
                auto tuple = q.top(); q.pop();
                int index1 = std::get<1>(tuple);
                int index2 = std::get<2>(tuple);
                result.emplace_back(v1[index1], v2[index2]);
                if (index2 + 1 < size2)
                {
                    q.push(make_tuple(v1[index1] + v2[index2 + 1], index1, index2 + 1));
                }
            }
        }

        return result;
    }

    vector<pair<int, int>> kSmallestPairs(vector<int>& v1, vector<int>& v2, int k) {
        vt<pii> result;
        std::function <bool(const tii &, const tii &)> comp2 = [&v1, &v2](const tii &l, const tii &r) {
            return std::get<0>(l) > std::get<0>(r);
        };
        pq<tii, vt<tii>, decltype(comp2)> q(comp2);

        std::function <void(int, int)> pushq = [&result, & v1, &v2, &q](int i, int j)
        {
            auto tuple = make_tuple(v1[i] + v2[j], i, j);
            q.push(tuple);
        };


        if (k != 0 && v1.size() != 0 && v2.size() != 0)
        {
            pushq(0, 0);
            szt size1 = v1.size();
            szt size2 = v2.size();
            szt count = std::min((szt)k, v1.size()*v2.size());
            while (count > 0)
            {
                auto tuple = q.top(); q.pop();
                int index1 = std::get<1>(tuple);
                int index2 = std::get<2>(tuple);
                result.emplace_back(v1[index1], v2[index2]); count--;
                if(index2+1 < size2)
                    pushq(index1, index2 + 1);  
                if (index2 == 0)
                {
                    if(index1 + 1 < size1)
                        pushq(index1 + 1, index2);
                }

            }
        }
        
        return result;
    }

    virtual void test()
    {
        vint v1 = { 1,7,11 };
        vint u1 = { 2,4,6};
        auto r1 = kSmallestPairs(v1, u1, 3);

        vint v2 = { 1,1,2 };
        vint u2 = { 1,2,3 };
        auto r2 = kSmallestPairs(v2, u2, 2);

        vint v3 = { 1,2 };
        vint u3 = {3};
        auto r3 = kSmallestPairs(v3, u3, 3);

        vint v4 = { 1,1,2 };
        vint u4 = { 1,2,3 };
        auto r4 = kSmallestPairs(v4, u4, 10);

        testUtil::timer t;
        t.start();
        vint v5 = { 34, 774, 1640, 1814, 2364, 2733, 2872, 3556, 4310, 4344, 4850, 5158, 6062, 6778, 7542, 8115, 8590, 9071, 9204, 10021, 10288, 10987, 11850, 12773, 12948, 13940, 14475, 14572, 15254, 15730, 16287, 17010, 17698, 18014, 18128, 18692, 18804, 19283, 19804, 20386, 20763, 20808, 21600, 22144, 22982, 23535, 23861, 23982, 24938, 25251, 25663, 26298, 26939, 27077, 27419, 27997, 28809, 28975, 29904, 30717, 30886, 31853, 32433, 33338, 33878, 33881, 34266, 34685, 35239, 35455, 36153, 36493, 36650, 37184, 37310, 38178, 38304, 39298, 40029, 40430, 41145, 41288, 41395, 41633, 42625, 43613, 43798, 44733, 45332, 45470, 45944, 46657, 47307, 48232, 48463, 49443, 49736, 50240, 51119, 52041 };
        vint u5 = { 801, 933, 1093, 1498, 2384, 2665, 3310, 4119, 4786, 4975, 5292, 6132, 6344, 6818, 7448, 8264, 8904, 9118, 10053, 10745, 11671, 12517, 12558, 12819, 12843, 13750, 13765, 14481, 14787, 14922, 15824, 15892, 16879, 17151, 18100, 18208, 18866, 19414, 20372, 20551, 20856, 21547, 21917, 22879, 23389, 24317, 24974, 25051, 25367, 26047, 26942, 27711, 28453, 28629, 28972, 29587, 30559, 31377, 32077, 33036, 33784, 34480, 35178, 35640, 36386, 37225, 37482, 38338, 38481, 39286, 39680, 40533, 41354, 41965, 42268, 42619, 43027, 43631, 44109, 44191, 44245, 45240, 45303, 46106, 46810, 47282, 47859, 48212, 48378, 48549, 49229, 49548, 50354, 50521, 51411, 52322, 52792, 53256, 53388, 53571 };
        auto r5 = kSmallestPairs(v5, u5, 1000);
        cout << "finished in " << t.stop() << endl;

        t.reset();
        auto r6 = kSmallestPairs_fast(v5, u5, 1000);
        cout << "finished in " << t.stop() << endl;

        t.reset();
        auto r7 = kSmallestPairs_2(v5, u5, 1000);
        cout << "finished in " << t.stop() << endl;
    }
};

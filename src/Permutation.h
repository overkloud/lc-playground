#include "Solution.h"

using namespace std;

class Permutation : public  solution {

public:


    string getKey(list<int> L)
    {
        stringstream ss;
        for(auto i : L)
        {
            ss << i << '|';
        }
        return ss.str();
    }

    typedef vector<vector<int>> Perms;
    typedef vector<int> Perm;

    map<string, Perms> M;


    Perms permute(list<int> & L)
    {
        Perms p;

        if(L.size() == 0) return p;
        
        if(L.size() == 1)
        {
            Perm one_p (L.begin(), L.end());
            p.push_back(one_p);       
            return p;     
        }

        for(int i = 0; i < L.size(); i++)
        {
            list<int> l = L;
            auto it = l.begin();
            advance(it, i);
            auto current = *it;
            l.erase(it);

            string K = getKey(l);

            if(M.find(K) != M.end())
            {
                Perms pp = M[K];
                for(auto &p1 : pp)
                {
                    Perm one_p = p1;
                    one_p.push_back(current);
                    p.push_back(one_p);    
                }

            }

            else
            {
                Perms p_l = permute(l);
                //M.emplace((make_pair(K, p_l)));
                for(auto &p1 : p_l)
                {
                    Perm one_p = p1;
                    one_p.push_back(current);
                    p.push_back(one_p);    
                }
            }

        }

        string K = getKey(L);
        M.emplace(K, p);

        return p;
    }

 

    vector<vector<int>> permute(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        list<int> L(nums.begin(), nums.end());

        return permute(L);
    }



    void test()
    {
        Permutation P;
        Perm p({1,2,3,4,5});
        Perms pp = P.permute(p);
        print(pp);
    }
};
#include "Solution.h"

using namespace std;

class LongestCommonSubstring: public  solution {

public:

    class Solution_DP
    {
        unordered_map<szt, list<pair<int,int>>> M;
    public:
        void findLongestCommonSubstring(const string &s, const string &t, szt pos)
        {
            M.emplace(pos, list<pair<int,int>>());

            if(M.count(pos-1) != 0)
            {
                for(auto prev : M[pos-1])
                {
                    if(s[prev.first+prev.second] == t[pos])
                    {
                        M[pos].emplace_back(prev.first, prev.second+1);
                    }
                }
            }

            for(szt i = 0; i < s.size(); i++)
            {
                if(s[i] == t[pos])
                {
                    M[pos].emplace_back(i, 1);
                }
            }

            if(pos < t.size() - 1)
            {
                findLongestCommonSubstring(s, t, pos+1);
            }
        }

        string findLongestCommonSubstring(const string &s, const string &t)
        {
            M.clear();
            findLongestCommonSubstring(s, t, 0);

            pair<int,int> max(0,0);
            for(auto it : M)
            {
                for(auto pair:it.second)
                {
                    if(pair.second > max.second)
                    {
                        max = pair;
                    }
                }
            }

            string result = "";
            if(max.second != 0)
            {
                result = s.substr(max.first, max.second);
            }

            return result;
        }

        szt findLCSLength(const string &s, const string &t)
        {
            return findLongestCommonSubstring(s,t).size();
        }
    };
    
    virtual void test()
    {
         string s  = "OldSite:GeeksforGeeks.org";
         string t  = "NewSite:GeeksQuiz.com";
         Solution_DP s1;
         cout << s1.findLongestCommonSubstring(s,t) << endl;
    }
};

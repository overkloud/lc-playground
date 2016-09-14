#include "Solution.h"

using namespace std;

class GroupAnagrams: public  solution {

public:

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vt<string>> map;
        vt<vt<string>> result;

        for (auto s : strs)
        {
            vt<char> chars;
            for (char c : s)
            {
                chars.push_back(c);
            }
            sort(chars.begin(), chars.end());
            string key(chars.begin(), chars.end());

            auto it = map.find(key);
            if (it != map.end())
            {
                it->second.push_back(s);
            }
            else
            {
                vt<string> v(1, s);
                map.emplace(key, v);
            }
        }

        for (auto i : map)
        {
            result.push_back(i.second);
        }

        return result;
    }

    virtual void test()
    {
        vt<string> v1 = { "eat", "tea", "tan", "ate", "nat", "bat" };
        auto r1 = groupAnagrams(v1);
    }
};

#include "Solution.h"
#include <queue>
#include <list>
#include <sstream>




// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.

// The matching should cover the entire input string (not partial).

// The function prototype should be:
// bool isMatch(const char *s, const char *p)

// Some examples:
// isMatch("aa","a") -> false
// isMatch("aa","aa") -> true
// isMatch("aaa","aa") -> false
// isMatch("aa", "a*") -> true
// isMatch("aa", ".*") -> true
// isMatch("ab", ".*") -> true
// isMatch("aab", "c*a*b") -> true

class RegexMatch : public solution{
public:

    // c = [a-z] or .
    bool match(const string & s, int &pos, char c)
    {
        assert(pos < s.size());
        if (c == '.')
        {
            pos++;
            return true;
        }
        return s[pos++] == c;
    }


    // *c = [a-z]* or .*
    vint wild_match(const string & s, int &pos, char c)
    {
        assert(pos < s.size());
        vint v;
        if (c == '.')
        {
            while (pos < s.size())
            {
                v.push_back(pos++);
            }
            v.push_back(pos);
        }
        else
        {
            while (pos < s.size() && c == s[pos])
            {
                v.push_back(pos++);
            }
            v.push_back(pos);
        }
        return v;
    }

    //map<pair<int, int>, bool> map;
    vector<vint> map;
    bool isMatch_map(string s, string p, int s_pos, int p_pos) {

        int i = s_pos;
        int j = p_pos;
        
        bool result = false;

        auto pos = mkp(s_pos, p_pos);

        //if (map.find(pos) == map.end())
        if(map[i][j] == -1)
        {
            //cout << "working on " << i << "," << j << endl;
            for (; i < s.size() && j < p.size();)
            {
                if (j < p.size() - 1 && p[j + 1] == '*')
                {
                    vint v = wild_match(s, i, p[j]);
                    j = j + 2;
                    for (auto a : v)
                    {
                        bool b = isMatch_map(s, p, a, j);
                        if (b)
                        {
                            result = true;
                            break;
                        }
                    }
                    if (!result) {
                        result = false;
                        break;
                    }
                    else break;
                }
                else
                {
                    bool b = match(s, i, p[j]);
                    if (!b)
                    {
                        result = false;
                        break;
                    }
                    j++;
                }
            }

            if (i == s.size() && j + 1 < p.size())
            {
                while (j + 1 < p.size() && p[j + 1] == '*')
                {
                    j = j + 2;
                }
            }

            if (i == s.size() && j == p.size()) result = true;
            //map.emplace(pos, result);
            map[s_pos][p_pos] = (int)result;
        }
        else
        {
            //result = map[pos];
            result = map[s_pos][p_pos] == 0 ? false : true;
        }

        return result;
    }

    bool isMatch(string s, string p, int s_pos, int p_pos) {

        int i = s_pos;
        int j = p_pos;
        //cout << "working on " << i << "," << j << endl;
        for (; i < s.size() && j < p.size();)
        {
            if (j < p.size() - 1 && p[j + 1] == '*')
            {
                vint v = wild_match(s, i, p[j]);
                j = j + 2;
                for (auto a : v)
                {
                    bool b = isMatch(s, p, a, j);
                    if (b) return true;
                }
                return false;
            }
            else
            {
                bool b = match(s, i, p[j]);
                if (!b) return b;
                j++;
            }
        }
        if (i == s.size() && j + 1 < p.size())
        {
            while (j + 1 < p.size() && p[j + 1] == '*')
            {
                j = j + 2;
            }
        }

        if (i == s.size() && j == p.size()) return true;
        return false;
    }

    bool isMatch(string s, string p)
    {
        //map.clear();
        return isMatch(s, p, 0, 0);
    }

    bool isMatch_m(string s, string p)
    {
        //map.clear();
        map.clear();
        for (int i = 0; i <= s.size(); i++)
        {
            vint v(p.size() + 1, -1);
            map.push_back(v);
        }
        testUtil::timer t;
        t.start();
        bool result = isMatch_map(s, p, 0, 0);
        cout << "result : " << t.stop() << endl;
        return result;
    }

    virtual void test()
    {
        char s1 [] = "aa";
        char p1 [] = "a";
        char p2 [] = "aa";
        char p3 [] = "aaa";
        assert(!isMatch(s1, p1));
        assert(isMatch(s1, p2));
        assert(!isMatch(s1, p3));
        assert(!isMatch("aa", "a"));// false
        assert(isMatch("aa", "aa"));// -> true
        assert(!isMatch("aaa", "aa"));// false
        assert(isMatch("aa", "a*"));// -> true
        assert(isMatch("aa", ".*"));// -> true
        assert(isMatch("ab", ".*"));// -> true
        assert(isMatch("aab", "c*a*b"));// -> true
        assert(isMatch("aaa", "a*a"));// -> true
        assert(isMatch("a", "ab*"));// -> true
        assert(isMatch("a", "ab*.*"));// -> true
        cout << "=================" << endl;
        testUtil::timer t;
        t.start();
        assert(isMatch("baccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbc", 
            "c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*"));// -> true
        //assert(isMatch("baccbbcbcacacbbc", "c*.*b*c*ba*b*b*.a*"));
        auto elapsed = t.stop();
        cout << "spent " << elapsed << endl;
        //t.reset();
        assert(isMatch_m("baccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbcbaccbbcbcacacbbc",
            "c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*c*.*b*c*ba*b*b*.a*"));// -> true
        //assert(isMatch_m("baccbbcbcacacbbc", "c*.*b*c*ba*b*b*.a*"));
        //cout << "spent " << t.stop() << endl;
    }
};
#include "Solution.h"

using namespace std;

class strStr: public  solution {

public:

    class Interface
    {
    public:
        virtual int strStr(const string& s, const string &t)=0;
    };

    class Solution_Hash: public Interface
    {
    public:

        //vector<szt> M;
        static const ll K = 102199;
        static const ll B = 101;

 

        ll hash(const string & s, const szt start, const szt len)
        {

            ll hash_value = 0;
            szt m = len;
            //if(start == 0)
            for(szt i = 0; i < m; i++)
            {
                hash_value = (hash_value * B) % K + (s[start+i]-'a')*B % K;
            }
            hash_value %= K;
            if(hash_value < 0) hash_value+=K;
            return hash_value;
        }


        bool equal(const string &s, int s1, const string & t, szt t1, szt len)
        {
            for(szt i = 0; i <len; i++)
            {
                if(s[s1+i]!=t[t1+i]) return false;
            }
            return true;
        }

        int strStr(const string& s, const string &t) 
        {

            if(t.size() > s.size()) return -1;


            szt m = t.size();
            szt n = s.size();
            
            unordered_map<ll, list<szt>> M;
            ll h_prev;
            ll hash_value;

            vector<ll> bm(m+1,0);
            for(szt i = 0; i < bm.size(); i++)
            {
                if(i == 0) bm[0] = 1%K;
                else bm[i] = bm[i-1]*B%K;
            }

            for(szt start = 0; start < n - m + 1; start++)
            {
                if(start == 0)
                {
                    hash_value=hash(s, 0, m);
                }
                else
                {
                    //h_prev = M[start - 1];
                    hash_value = (h_prev - ((s[start-1]-'a')*bm[m]))*B%K + ((s[start + m - 1]-'a') * B % K);
                    // if(s[start] == 'a')
                    // {
                    //     //cout << ((s[start + m - 1]-'a')*B);
                    // }
                    hash_value %= K;
                    if(hash_value < 0) hash_value += K;
                }
                h_prev = hash_value;
                //cout << s.substr(start, m) << ":" << hash_value << endl;
                if(M.count(hash_value) == 0)
                {
                    list<szt> l(1, start);
                    M.emplace(hash_value, l);
                }
                else
                {
                    bool match = false;
                    for(auto wordPos : M[hash_value])
                    {
                        if(equal(s, start, s, wordPos, m))
                        {
                            match = true;
                            break;
                        }
                    }
                    if(!match)
                    {
                        //cout << "we found collsion << " << s.substr(start, m) << " : " << hash_value << endl;
                        M[hash_value].push_back(start);  
                    }
                }
            }


            auto keyHash = hash(t, 0, m);
            //cout << t << "->" << keyHash << endl;
            if(M.count(keyHash))
            {
                for(auto wordPos : M[keyHash])
                {
                    if(equal(s, wordPos, t, 0, m))
                    {
                        return wordPos;
                    }
                }
            }

            return -1;        
        }

    };


    class Solution_KMP : public Interface
    {
    private:
        // Pay attention! 
        // the prefix under index i in the table above is 
        // is the string from pattern[0] to pattern[i - 1] 
        // inclusive, so the last character of the string under 
        // index i is pattern[i - 1]   

        // https://www.topcoder.com/community/data-science/data-science-tutorials/introduction-to-string-searching-algorithms/
        void build_fail_function(const string & t, vint & f)
        {
            auto n = t.size();
            for(int i = 2; i <= n; i++)
            {
                int j = f[i - 1];
                for (;;)
                {
                    if (t[j] == t[i - 1])
                    {
                        f[i] = j + 1;
                        break;
                    }
                    if (j == 0)
                    {
                        f[i] = 0;
                        break;
                    }
                    j = f[j];
                }
            }
        }

    public:
        int strStr(const string& s, const string &t)
        {
            szt result = -1;

            if (t.empty())
            {
                result = 0;
            }
            else if (s.size() >= t.size())
            {
               vint f(t.size()+1, 0);
               build_fail_function(t, f);
               szt i = 0, j = 0;
               auto n = s.size();
               auto m = t.size();
               while (true)
               {
                   if (j == n) break;

                   if (t[i] == s[j])
                   {
                       i++; j++;
                       if (i == m)  // found a match
                       {
                           result = j - m;
                           break;
                       }
                   }
                   else if (i > 0)
                   {
                       i = f[i];
                   }
                   else
                   {
                       j++;
                   }
               }
            }
            return (int)result;
        }
    };

    virtual void test()
    {
        //string s = "First line of the input contains no of test cases  T,the T test cases follow.";
        //string t = "cases";
        string s = "ababcaababcaabc";
        string t = "ababcaabc" ;
        //string s("aabba aab");
        //string t("aa");
        //cout << (int)'A' << endl;
        Solution_Hash s1;
        Solution_KMP s2;
        assert(s1.strStr(s, t) == s2.strStr(s, t));

        int tests = 5;
        range(tests)
        {
            auto v = testUtil::randomGen(1000, 25, false);
            string s(v.size(), 'a');
            rangen(j, s.size())
            {
                s[j] += v[j];
            }
            this_thread::sleep_for(1s);
            auto v2 = testUtil::randomGen(2, 25, false);
            string t(v2.size(), 'a');
            rangen(j, t.size())
            {
                t[j] += v2[j];
            }

            assert(s1.strStr(s, t) == s2.strStr(s, t));
        }
    }
};

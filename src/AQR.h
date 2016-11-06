#include "Solution.h"

using namespace std;

class AQR: public  solution {

public:

    long long power(int p, int q)
    {
        // not supporting negative pow since return type is int
        if (q < 0) return 0;

        if (q == 0) return 1;

        if (p == 0) return 0;

        if (q == 1) return p;

        long long pow = power(p, q / 2);
        if (q % 2)
        {
            return pow * pow * p;
        }
        else
        {
            return pow * pow;
        }
    }

    vector < int > sortIntegers(vector < int > n) {
        const int N = 10 + 1;
        vector<int> A(N, 0);

        for (auto i : n)
        {
            A[i]++;
        }

        vector<int> out(n.size(),0);
        int pos = 0;
        int pos_out = 0;
        while (pos < A.size())
        {
            if (A[pos] == 0)
            {
                pos++;
            }
            else
            {
                out[pos_out++] = pos;
                A[pos]--;
            }
        }

        return out;
    }


    bool isNumeric(char c)
    {
        if ('0' <= c && c <= '9')
            return true;
        else return false;
    }

    string sortWord(const string & s)
    {

        if (s.empty()) return "";

        vector<char> v;
        for (char c : s)
        {
            v.push_back(c);
        }

        sort(v.begin(), v.end());


        string ret(v.begin(), v.end());

        return ret;
    }

    string sortSegments(string &s)
    {
        string ret;

        if (s.empty()) return "";

        if (s.size() == 1) return s;

        bool found = false;
        int p = 0;
        if (isNumeric(s[0]))
        {
            for (int i = 1; i < s.size(); i++)
            {
                if (!isNumeric(s[i]))
                {
                    found = true;
                    p = i;
                    break;
                }
            }
        }
        else
        {
            for (int i = 1; i < s.size(); i++)
            {
                if (isNumeric(s[i]))
                {
                    found = true;
                    p = i;
                    break;
                }
            }
        }


        if (found)
        {
            //sort s[0,i-1] + sort(s[i])
            return sortWord(s.substr(0, p)) + sortSegments(s.substr(p));
        }
        else
        {
            return sortWord(s);
        }

    }


    virtual void test()
    {
        /*assert(1 == power(2, 0));
        assert(8 == power(2, 3));
        assert(64 == power(2, 6));

        assert(pow(2,20) == power(2, 20));

        assert(pow(2,62) == power(2, 62));
        assert(pow(2, 61) == power(2, 61));*/
        /*vint n1 = { 3,1,4,1,5,9,2,6,5 };
        auto r1 = sortIntegers(n1);

        vint n2 = { 10 };
        auto r2 = sortIntegers(n2);

        vint n3 = {  };
        auto r3 = sortIntegers(n3);

        int tests = 100;
        range(tests.size())
        {

        }*/

        string s = "AZQF013452BAB";
        auto r = sortSegments(s);

        s = "A1D2B2A2A1D11";
        r = sortSegments(s);

        s = "1028947582092";
        r = sortSegments(s);

        s = "AZDFYTRDAQZD";
        r = sortSegments(s);
    }
};

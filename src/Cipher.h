#include "Solution.h"

using namespace std;

class Cipher: public  solution {

public:

    ll bitToLong(vector<char> & c)
    {
        ll result = 0;
        for (int i = (int)c.size() - 1; i >= 0; i--)
        {
            result += (c[i] - '0')*(ll)pow(2, c.size() - 1 - i);
        }
        return result;
    }
    ll bitToLong(const string &s)
    {
        ll result = 0;
        for (int i = (int)s.size() - 1; i >= 0; i--)
        {
            result += (s[i] - '0')*(ll)pow(2, s.size() - 1 - i);
        }
        return result;
    }

    typedef vector<vector<char>> vcc;

    void fill(vcc& v, char val, int pos)
    {
        for (int i = 0; i < v.size(); i++)
        {
            v[i][pos + i] = val;
        }
    }

    int charToBit(char c)
    {
        return c - '0';
    }

    char calc(vcc & v, int pos, const string &s, int k, int n)
    {
        int bit = charToBit(s[pos]);
        int result = bit;
        for (int i = 1; i < v.size(); i++)
        {
            result ^= charToBit(v[i][pos]);
        }
        return '0' + result;
    }

    void run(int k, int n, const string & str)
    {
        if (str.empty()) return ;
        vector<char> result(n, '\0');
        int pos = 0;

        vector<vector<char>> s;
        for (int i = 0; i < k; i++)
        {
            vector<char> v(str.size(), '\0');
            for (int j = 0; j < i; j++)
                v[j] = '0';
            for (int j = i; j < n; j++){
                //v[j] = str[j - i];
            }
            for (int j = 0; j < str.size() - n - i; j++)
                v[n + j + i] = '0';
            s.push_back(v);
        }

        for (int i = 0; i < n; i++)
        {
            char c = calc(s, i, str, k, n);
            fill(s, c, i);
        }

        s[0].erase(s[0].begin() + n, s[0].end());
        for (auto c : s[0])
        {
            cout << c;
        }
        cout << endl;
        return;
    }

    void run(istream & in)
    {
        vint v = readInts(in, ' ', 2);
        int n = v[0];
        int k = v[1];
        string str;
        getline(in, str);
        //run2(k, n, str);
    }
};

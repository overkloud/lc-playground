#include "Solution.h"

using namespace std;

class FriendCircle: public  solution {

public:


    void dfs(vector<vint> & v, const int n, vint& x, int root)
    {
        x[root] = 1;
        for (int i = 0; i < n; i++)
        {
            if (x[i] == 0 && v[root][i])
            {
                x[i] = 1;
                dfs(v, n, x, i);
            }
        }
    }


    int calc(vector<vint> & v, const int n)
    { 
        int count = 0;
        vint x(n, 0);

        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] == 0)
            {
                dfs(v, n, x, i);
                count++;
            }
        }

        return count;
    }

    /*
    * Complete the function below.
    */
    int friendCircles(vector < string > friends) {
        vector<vint> v;
        for (int i = 0; i < friends.size(); i++)
        {
            vint v1;
            string &line = friends[i];
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == 'Y')
                {
                    v1.push_back(1);
                }
                else
                {
                    v1.push_back(0);
                }
            }
            v.push_back(v1);
        }
        return calc(v, (int)v.size());
    }

    void run(istream & in)
    {
        int n = readInt(in);
        vector<string> v;
        string line;
        for (int i = 0; i < n; i++)
        {
            getline(in, line);
            v.push_back(line);
        }

        cout << friendCircles(v) << endl;
    }
};

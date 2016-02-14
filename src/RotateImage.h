#include "Solution.h"

using namespace std;

class RotateImage : public  solution {


public:
    void Rotate(vector<vector<int>> & v, int s_i, int s_j, int size) 
    {
        if(0 == size || 1 == size) return;
        
        if(size - 2 >= 2)
        {
            Rotate(v, s_i + 1, s_j + 1, size - 2);
        }

        // rotate up, down, left and right edges

        // store four edges.
        vector<int>old_up;
        vector<int>old_down;
        vector<int>old_left;
        vector<int>old_right;
        for (int i = 0; i < size; i++)
        {
            old_up.push_back(v[s_i][s_j + i]);
            old_down.push_back(v[s_i + size - 1][s_j + i]);
            old_left.push_back(v[s_i + i][s_j]);
            old_right.push_back(v[s_i + i][s_j + size - 1]);
        }


        // up
        for(int i = 0; i < size; i++)
        {
            v[s_i + i][s_j + size - 1] = old_up[i];
        }
        // down
        for(int i = 0; i < size; i++)
        {
            v[s_i + i][s_j] = old_down[i];
        }
        for(int i = 0; i < size; i++)
        {
            v[s_i][s_j + i] = old_left[size - 1 - i];
        }
        for(int i = 0; i < size; i++)
        {
            v[s_i + size - 1][s_j + i] = old_right[size - 1 - i];
        }
        
    }

    void Rotate(vector<vector<int>> &v) {
        Rotate(v, 0, 0, v.size());
    }

    void print (vector<vector<int>> &v)
    {
        for(auto row : v)
        {
            for (auto i : row)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    void test()
    {
        //vector<vector<int>> v = {{9, 8, 7}, {4, 5, 6}, {1, 2, 3}};
        vector<vector<int>> v = {{9, 8}, {1, 2}};
        print(v);
        Rotate(v);
        print(v);

        vector<vector<int>> v1= {{9}};
        print(v1);
        Rotate(v1);
        print(v1);

        vector<vector<int>> v2 = {{9, 8, 7, 12}, {4, 5, 6, 10}, {1, 2, 3, 11}, {15, 16, 17, 18}};
        print(v2);
        Rotate(v2);
        print(v2);

    }
};


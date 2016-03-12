#include "Solution.h"

using namespace std;

class FindMedian: public  solution {

public:

    typedef struct MinMaxHeap {
        pq<int> max;
        pq<int, vector<int>, std::greater<int>> min;

        void add(int i)
        {
            if (max.size() == 0)
                max.push(i);
            else
            {
                if (i > max.top())
                {
                    min.push(i);
                    while (min.size() > max.size())
                    {
                        max.push(min.top());
                        min.pop();
                    }
                }
                else {
                    max.push(i);
                    while (max.size() > min.size() + 1)
                    {
                        min.push(max.top());
                        max.pop();
                    }
                }
            }
            
        }

        double median()
        {
            if (max.size() == min.size())
            {
                return (max.top() + min.top()) / 2.0;
            }
            else
                return max.top();
        }
    } MMHeap;


    virtual void run(istream & in)
    {
        int n = readInt(in);
        MMHeap h;
        cout.setf(std::ios::fixed, std::ios::floatfield);
        cout.precision(1);
        while (n > 0)
        {
            n--;
            int i = readInt(in);
            h.add(i);
            cout << h.median() << endl;
        }
    }
};

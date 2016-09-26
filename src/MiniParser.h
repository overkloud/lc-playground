#include "Solution.h"

using namespace std;

class MiniParser : public  solution {



public:

    // This is the interface that allows for creating nested lists.
         // You should not implement it, or speculate about its implementation
    class NestedInteger {
    public:
        // Constructor initializes an empty nested list.
        NestedInteger() :num(INT_MIN) {};

        // Constructor initializes a single integer.
        NestedInteger(int value) :num(value) {};

        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const
        {
            return num != INT_MIN;
        }

        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const
        {
            return num;
        }

        // Set this NestedInteger to hold a single integer.
        void setInteger(int value)
        {
            num = value;
        }

        // Set this NestedInteger to hold a nested list and adds a nested integer to it.
        void add(const NestedInteger &ni)
        {
            list.push_back(ni);
        }

        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        const vector<NestedInteger> &getList() const
        {
            return list;
        }

        vector<NestedInteger> list;
        int num;

    };

    NestedInteger deserialize(const string &s, int start, int end) {
        NestedInteger result;
        std::function <int(const string&, int,int,int)> getClose = [](const string &s, int start, int end,  int open) {
            int nextClose;
            //if (start != open)
            {
                int countOpen = 0;
                for (int i = open + 1; i < end; i++)
                {
                    if (s[i] == ']' && countOpen == 0)
                    {
                        nextClose = i; break;
                    }
                    else if (s[i] == '[')
                    {
                        countOpen++;
                    }
                    else if (s[i] == ']')
                    {
                        countOpen--;
                    }
                }
            }
            return nextClose;
        };
        if (start <= end)
        {
            if (s[start] == '[' && s[end] == ']')
            {
                int numStart = -1;
                for (int pos = start + 1; pos < end; pos++)
                {
                    auto ch = s[pos];
                    if ((isdigit(ch) && numStart == -1) || ch == '-')
                    {
                        numStart = pos;
                    }
                    if (numStart != -1 && (ch == ',' || pos == end - 1))
                    {
                        int len = (pos == end - 1) ? pos - numStart + 1 : pos - numStart;
                        int ele = atoi(s.substr(numStart, len).c_str());
                        numStart = -1;
                        NestedInteger n(ele);
                        result.add(n);
                    }
                    if (ch == '[')
                    {
                        int open = pos;
                        int close = getClose(s, start, end, open);
                        result.add(deserialize(s, open, close));
                        pos = close + 1;
                    }
                }
            }
            else
            {
                auto num = atoi(s.c_str());
                //NestedInteger ni(num);
                result.setInteger(num);
            }
            
        }
        return result;
    }


    NestedInteger deserialize(string s) {
        NestedInteger result = deserialize(s, 0, s.size() - 1);
        return result;
    }

    virtual void test()
    {
        string s1 = "1";
        auto r2 = deserialize(s1);

        string s = "[11,12,[13,[14,[15,110]]],[16],17,18,19]";
        auto r1 = deserialize(s);
    }
};

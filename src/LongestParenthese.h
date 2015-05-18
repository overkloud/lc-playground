#include "Solution.h"



// Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

// For "(()", the longest valid parentheses substring is "()", which has length = 2.

// Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

class LongestParenthese : public solution
{

public:
    static int longestValidParentheses(string s) {

        stack <char> t;
        int maxLength = 0;
        int start = -1;
        int end = -1;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s.at(i);
            if (c == '(')
            {
                t.push(c);
                if (start == -1) start = i;
            }
            else
            {
                if (t.size() > 0)
                {
                    char cc = t.top();
                    t.pop();
                    //end = i;
                    if (i - start > maxLength)
                    {
                        end = i;
                        maxLength = end - start + 1;
                    }
                }
                else
                {
                    stack<char> tt;
                    t.swap(tt);
                    start = -1;
                    end = -1;
                }
            }
        }
        //for (int i = s.length() - 1; i >= 0; i--)
        //{
        //    char c = s.at(i);
        //    if (c == ')')
        //    {
        //        t.push(c);
        //        if (start == -1) start = i;
        //    }
        //    else
        //    {
        //        if (t.size() > 0)
        //        {
        //            char cc = t.top();
        //            t.pop();
        //            //end = i;
        //            if (i - start > maxLength)
        //            {
        //                end = i;
        //                maxLength = end - start;
        //            }
        //        }
        //        else
        //        {
        //            stack<char> tt;
        //            t.swap(tt);
        //            start = -1;
        //            end = -1;
        //        }
        //    }
        //}

        return maxLength;
    }

    void test()
    {
        assert(longestValidParentheses("(()()") == 4);
        assert(longestValidParentheses("()") == 2);
        assert(longestValidParentheses("(()") == 2);
        assert(longestValidParentheses("()(()") == 2);
    }
};


// class Solution {
// public:
//     int longestValidParentheses(string s) {
//         return LongestParenthese::longestValidParentheses(s);
//     }
// };

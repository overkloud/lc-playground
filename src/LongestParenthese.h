#include "Solution.h"



// Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

// For "(()", the longest valid parentheses substring is "()", which has length = 2.

// Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

class LongestParenthese : public solution
{

public:
    static int longestValidParentheses(string s) {

        // stack <char> t;
        // int totalMax = 0;
        // int currenMax = 0;
        // for(int i = 0; i < s.length(); i++)
        // {
        //  char c  = s.at(i);
        //  if(c == '(')
        //  {
        //      t.push(c);
        //      currentMax = 0;
        //  }
        //  else
        //  {
        //      if(!t.empty())
        //      {
        //          t.pop();
        //          currentMax += 2;
        //          if(t.empty())
        //          {
        //              totalMax += currentMax;
        //          }
        //      }
        //  }
        // }
  //       return maxLength;

        return 0;
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

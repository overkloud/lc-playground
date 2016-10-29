#include "Solution.h"



// Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

// For "(()", the longest valid parentheses substring is "()", which has length = 2.

// Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

class LongestParenthese : public solution
{

public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        int n = (int)s.size();
        if (n >= 1)
        {
            vector<int> dp(n, 0);
            dp[0] = 0;

            for (int i = 1; i < n; i++)
            {
                const char c = s[i];
                if (c == ')')
                {
                    if (s[i - 1] == '(')
                    {
                        int j = i - 2;
                        if (j >= 0)  dp[i] = dp[j] + 2;
                        else dp[i] = 2;
                    }
                    else
                    {
                        int j = i - 1 - dp[i - 1];
                        if (j >= 0 && s[j] == '(')
                        {
                            if (j >= 1)
                            {
                                dp[i] = 2 + dp[i - 1] + dp[j - 1];
                            }
                            else
                                dp[i] = 2 + dp[i - 1];
                        }
                        else dp[i] = 0;
                    }
                }
                else
                {
                    dp[i] = 0;
                }

                maxLen = std::max(maxLen, dp[i]);
            }

        }
        return maxLen;
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

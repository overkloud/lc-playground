
#include "Solution.h"
#include <queue>
#include <list>
#include <sstream>




// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.

// The matching should cover the entire input string (not partial).

// The function prototype should be:
// bool isMatch(const char *s, const char *p)

// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "a*") → true
// isMatch("aa", ".*") → true
// isMatch("ab", ".*") → true
// isMatch("aab", "c*a*b") → true

class RegexMatch {
public:

    // c = [a-z] or .
    bool match(const char *s, char c)
    {
        if (!s) return false;

        if(*s == '\0') return false;

        if (c == '.')
        {
            s++;
            return true;
        }

        return (*s == c);
      
    }


    // *c = [a-z]* or .*
    bool match(const char *s, char *c)
    {

    }

    bool isMatch(const char *s, const char *p) {

        
        return true;
    }

    static bool isMatch(const char *s, const char *p) 
    {
        RegexMatch r;
        return r.isMatch(s, p);
    }

    void test()
    {
        char s1 [] = "aa";
        char p1 [] = "a";
        char p2 [] = "aa";
        char p3 [] = "aaa";
        assert(!isMatch(s1, p1));
        assert(isMatch(s1, p2));
        assert(!isMatch(s1, p3));

    }
};
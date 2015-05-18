//Problem Statement
//
//Let's say you have a binary string such as the following:
//011100011
//One way to encrypt this string is to add to each digit the sum of its adjacent digits.For example, the above string would become :
//123210122
//In particular, if P is the original string, and Q is the encrypted string, then Q[i] = P[i - 1] + P[i] + P[i + 1] for all digit positions i.Characters off the left and right edges of the string are treated as zeroes.
//An encrypted string given to you in this format can be decoded as follows(using 123210122 as an example) :
//Assume P[0] = 0.
//Because Q[0] = P[0] + P[1] = 0 + P[1] = 1, we know that P[1] = 1.
//Because Q[1] = P[0] + P[1] + P[2] = 0 + 1 + P[2] = 2, we know that P[2] = 1.
//Because Q[2] = P[1] + P[2] + P[3] = 1 + 1 + P[3] = 3, we know that P[3] = 1.
//Repeating these steps gives us P[4] = 0, P[5] = 0, P[6] = 0, P[7] = 1, and P[8] = 1.
//We check our work by noting that Q[8] = P[7] + P[8] = 1 + 1 = 2. Since this equation works out, we are finished, and we have recovered one possible original string.
//Now we repeat the process, assuming the opposite about P[0]:
//Assume P[0] = 1.
//Because Q[0] = P[0] + P[1] = 1 + P[1] = 1, we know that P[1] = 0.
//Because Q[1] = P[0] + P[1] + P[2] = 1 + 0 + P[2] = 2, we know that P[2] = 1.
//Now note that Q[2] = P[1] + P[2] + P[3] = 0 + 1 + P[3] = 3, which leads us to the conclusion that P[3] = 2. However, this violates the fact that each character in the original string must be '0' or '1'.Therefore, there exists no such original string P where the first digit is '1'.
//Note that this algorithm produces at most two decodings for any given encrypted string.There can never be more than one possible way to decode a string once the first binary digit is set.
//Given a string message, containing the encrypted string, return a vector <string> with exactly two elements.The first element should contain the decrypted string assuming the first character is '0'; the second element should assume the first character is '1'.If one of the tests fails, return the string "NONE" in its place.For the above example, you should return{ "011100011", "NONE" }.
//Definition
//
//Class :
//BinaryCode
//Method :
//decode
//Parameters :
//string
//Returns :
//vector <string>
//Method signature :
//vector <string> decode(string message)
//(be sure your method is public)

#include "Solution.h"
#include <sstream>


using namespace std;
class BinaryCode : public solution
{
public:

    vector<int> decode(vector<int> Q, int first)
    {

        vector<int> P;
        P.push_back(first);
        for (int i = 0; i < Q.size(); i++)
        {
            if (i == 0)
            {
                int a = Q[0] - P[0];
                if (a < 0 || a > 1) return vector<int>();
                P.push_back(a);
            }
            else if (i == Q.size() - 1)
            {
                int a = Q[i] - P[i - 1];
                if (a != P.back()) return vector<int>();
            }
            else 
            {
                int a = Q[i] - P[i - 1] - P[i];
                if (a < 0 || a > 1) return vector<int>();
                P.push_back(a);
            }
        }
        return P;
    }

    vector<string> decode(string s)
    {
        vector<string> ret;
        if (s.empty())
        {
            ret.push_back("NONE");
            ret.push_back("NONE");
            return ret;
        }


        
        vector<int>n;

        int a = atoi(s.c_str());

        if (a == 0)
        {
            ret.push_back("0");
            ret.push_back("NONE");
            return ret;
        }

        while (a > 0)
        {
            n.push_back(a % 10);
            a = a / 10;
        }

        // now n has reverse order of s
        // reverse it to b
        vector<int> b(n.rbegin(), n.rbegin());

        vector<int> P_0(move(decode(b, 0)));
        vector<int> P_1(move(decode(b, 1)));

        stringstream ss1;
        for (int a : P_0) 
        {
            ss1 << a;
        }
        string s1 = ss1.str();

        stringstream ss2;
        for (int a : P_1)
        {
            ss2 << a;
        }
        string s2 = ss2.str();

        if (s1.empty())
            ret.push_back("NONE");
        else ret.push_back(s1);

        if (s2.empty())
            ret.push_back("NONE");
        else ret.push_back(s2);

        return ret;
    }
};
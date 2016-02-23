#include "Solution.h"

using namespace std;

class HuffmanDecode: public  solution {

public:

    /*
    https://www.hackerrank.com/challenges/tree-huffman-decoding
    */


    typedef struct node
    {
        int freq;
        char data;
        node * left;
        node * right;

        node(node * l, node * r, char c)
        {
            left = l;
            right = r;
            data = c;
        }
    }node;

    string dfs(node * root, string & str)
    {
        int pos = 0;
        node * p = root;
        string result;
        while (pos < str.size())
        {
            while (pos < str.size() && p && p->data == '\0')
            {
                if (str[pos] == '1')
                {
                    p = p->right;
                }
                else
                    p = p->left;
                pos++;
            }
            if (p && p->data != '\0') result.append(1, p->data);
            p = root;
        }
        
        return result;
    }

    void decode_huff(node * root, string s)
    {
        int pos = 0;
        cout << dfs(root, s) << endl;
    }


    void run(istream & in)
    {
        #define null nullptr
        //node b(null, null, 'B');
        node a(null, null, 'A');
        //node c(null, null, 'C');
        //node e1(&b, &c, '\0');
        node root(null, &a, '\0');
        decode_huff(&root, "1");
    }

};

#include "Solution.h"

using namespace std;

class Trie: public  solution {

public:

    struct Node
    {
        char c;
        Node * children['z'-'a' + 1];
        int count = 0;

        Node() : children()
        {
        }

        Node(char ch) : children()
        {
            c = ch;
        }
    };

    int find(Node * root, const string & w) 
    {
        Node * p = root;
        for (auto c : w)
        {
            if (p->children[c - 'a'] != nullptr)
            {
                p = p->children[c-'a'];
            }
            else
            {
                return 0;
            }
        }

        if (p) return p->count;
        else return 0;
    }

    void add(Node * root, const string & w)
    {
        Node * p = root;
        for (char c : w)
        {
            Node * n = nullptr;
            if (p->children[c-'a'] != nullptr)
            {
                n = p->children[c-'a'];
            }
            else
            {
                n = new Node(c);
            }
            n->count++; //p->count++;
            p->children[c-'a'] = n;
            p = n;
        }
    }

    void run(istream & in, ostream & out)
    {
        int n = readInt(in);
        Node * root = new Node();
        for (int i = 0; i < n; i++)
        {
            string line;
            getline(in, line);
            const vt<string>& s = split(line, ' ');
            if (s[0] == "add")
            {
                add(root, s[1]);
            }
            else if (s[0] == "find")
            { 
                out << find(root, s[1]) << endl;
            }
        }
    }
};

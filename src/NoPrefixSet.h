#include "Solution.h"

using namespace std;

class NoPrefixSet: public  solution {

public:

    struct Node
    {
        char c;
        Node * children['j' - 'a' + 1];
        //int count = 0;
        bool end = false;

        Node() : children(), end(false)
        {
        }

        Node(char ch) : children(), end(false)
        {
            c = ch;
        }
    };


    bool add(Node * root, const string & w)
    {
        Node * p = root;
        for (int i = 0; i < w.size(); i++)
        {
            auto c = w[i];
            Node * n = nullptr;
            if (p->children[c - 'a'])
            {
                n = p->children[c - 'a'];
                if (n->end || i == w.size() - 1) return true;
            }
            else
            {
                n = new Node(c);
                p->children[c - 'a'] = n;
            }
            p = n;
            if (i == w.size() - 1)
            {
                if (p != root) p->end = true;
            }

        }


        return false;
    }



    void run(istream & in, ostream & out)
    {
        int n = readInt(in);
        Node * root = new Node();
        fori(n){
            string line;
            getline(in, line);
            if (add(root, line))
            {
                out << "BAD SET" << endl;
                out << line << endl;
                return;
            }
        }

        out << "GOOD SET" << endl;

    }
};

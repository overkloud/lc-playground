#include "Solution.h"

using namespace std;

class WordLadder : public  solution {

public:

    double timetook;
    long long called;

    bool OffByOne(const string & a, const string &b)
    {
        //called++;
        //testUtil::timer t;
        //t.start();
        if (a.size() != b.size()) return false;

        bool off = false;
        range(a.size())
        {
            if (a[i] != b[i])
            {
                if (!off) off = true;
                else return false;
            }
        }
        /*timetook += t.stop();*/
        return off;
    }

    list<string> getAllVariations(const string & s)
    {
        //called++;
        /*testUtil::timer t;
        t.start();*/
        list<string> result;
        for (int i = 0; i < s.size(); i++)
        {
            for (int j = 'a'; j <= 'z'; j++)
            {
                if (j != s[i])
                {
                    string news = s;
                    news[i] = j;
                    result.push_back(news);
                }
            }
        }
        //timetook += t.stop();
        return result;
    }

    typedef set<string> Dictionary;

    int ladderLength_bfs(string start, string end, unordered_set<string> &dict) {
        dict.insert(end);
        queue<pair<string, int>> q;
        q.push(make_pair(start, 1));
        while (!q.empty()) {
            string s = q.front().first;
            int len = q.front().second;
            if (s == end) return len;
            q.pop();
            vector<string> neighbors = findNeighbors(s, dict);
            for (int i = 0; i < neighbors.size(); i++)
                q.push(make_pair(neighbors[i], len + 1));
        }
        return 0;
    }

    vector<string> findNeighbors(string s, unordered_set<string> &dict) {
        vector<string> ret;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            for (int j = 0; j < 26; j++) {
                if (c == 'a' + j) continue;
                s[i] = 'a' + j;
                /*testUtil::timer t;
                t.start();*/
                if (dict.count(s)) {
                    //called++;
                    ret.push_back(s);
                    dict.erase(s);
                }
                //timetook += t.stop();
            }
            s[i] = c;
        }
        return ret;
    }

    struct Node {
        string s;
        Node* parent;
        list<Node*>children;
        Node(string s) :s(s), parent(NULL) {};
    };


    pair<Node*, Node*> ladderLength_base(string start, string end, unordered_set<string> &dict) {
        dict.insert(end);
        dict.erase(start);


        queue<Node*> Q;
        Node*root = new Node(start);
        Node*endNode = NULL;
        Q.emplace(root);
        while (!Q.empty())
        {
            auto node = Q.front(); Q.pop();
            if (node->s == end)
            {
                endNode = node;
                break;
            }

            //dict.erase(node->s);
            string cur = node->s;
            for (int i = 0; i < cur.size(); i++)
            {
                for (int j = 'a'; j <= 'z'; j++)
                {
                    if (j != cur[i])
                    {
                        cur[i] = j;
                        if (dict.count(cur))
                        {
                            Node * child = new Node(cur);
                            child->parent = node;
                            node->children.push_back(child);
                            Q.emplace(child);
                            dict.erase(cur);
                        }
                        cur[i] = node->s[i];
                    }
                }
            }
        }


        return mkp(root, endNode);
    }

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        auto nodes = ladderLength_base(start, end, dict);
        auto root = nodes.first;
        auto leave = nodes.second;


        Node* cur = leave;
        int result = 0;
        while (cur != NULL)
        {
            result++;
            cur = cur->parent;
        }

        return result;
    }

    struct Node2 {
        string s;
        int dep;
        list<Node2*>parent;
        list<Node2*>children;
        Node2(string s, int dep) :s(s), dep(dep) {};
    };

    pair<Node2*, Node2*> ladderLength2_base(string start, string end, unordered_set<string> &dict) {
        dict.insert(end);
        dict.erase(start);

        unordered_map<string, Node2*> queued;
        queue<Node2*> Q;
        Node2*root = new Node2(start,0);
        Node2*endNode = NULL;
        Q.emplace(root);
        list<string> toRemove;
        int lastDep = 0;
        while (!Q.empty())
        {
            Node2* node = Q.front(); Q.pop();
            if (node->s == end)
            {
                endNode = node;
                break;
            }

            if (lastDep != node->dep)
            {
                for_each(toRemove.begin(), toRemove.end(), [&dict](string& e) {dict.erase(e); });
            }

            //dict.erase(node->s);
            string cur = node->s;
            for (int i = 0; i < cur.size(); i++)
            {
                for (int j = 'a'; j <= 'z'; j++)
                {
                    if (j != cur[i])
                    {
                        cur[i] = j;
                        if (dict.count(cur))
                        {
                            unordered_map<string, Node2*>::iterator it = queued.find(cur);
                            if (it == queued.end())
                            {
                                Node2 * child = new Node2(cur, node->dep + 1);
                                queued.emplace(cur, child);
                                child->parent.push_back(node);
                                node->children.push_back(child);
                                Q.emplace(child);
                                toRemove.push_back(cur);
                            }
                            else
                            {
                                Node2 * child = it->second;
                                child->parent.push_back(node);
                                node->children.push_back(child);
                            }
                        }
                        cur[i] = node->s[i];
                    }
                }
            }
            lastDep = node->dep;
        }


        return mkp(root, endNode);
    }


    void getAllPaths(Node2*cur, Node2* end, list<string>& curPath, list<list<string>>&result)
    {
        if (!cur) return;

        
        if (cur == end)
        {
            list<string>pp = curPath;
            result.push_back(pp);
        }

        for (Node2* parent: cur->parent)
        {
            curPath.push_front(parent->s);
            getAllPaths(parent, end, curPath, result);
            curPath.pop_front();
        }
    }

    vt<vt<string>> ladderLength2(string start, string end, unordered_set<string> &dict) {
        pair<Node2*, Node2*> nodes = ladderLength2_base(start, end, dict);
        Node2* root = nodes.first;
        Node2* leave = nodes.second;

        vt<vt<string>> result;

        if (leave)
        {
            list<list<string>>res_list;
            list<string> path(1, leave->s);
            getAllPaths(leave, root, path, res_list);

            //vt<vt<string>> result(res_list.begin(), res_list.end());
            //std::copy(res_list.begin(), res_list.end(), std::back_inserter(result));
            for (list<string>& list : res_list)
            {
                vt<string> result_vt(list.begin(), list.end());
                result.push_back(result_vt);
            }
        }
        
        return result;
    }

    virtual void test()
    {
        unordered_set<string> dict1 = { "hot","dot","dog","lot","log" };
        auto r1 = ladderLength2("hit", "cog", dict1);

        unordered_set<string> dict2 = { "hot", "cog", "dot", "dog", "hit", "lot", "log" };
        auto r2 = ladderLength2("hit", "cog", dict2);
        auto r3 = ladderLength2("hit", "xxg", dict1);
        auto r4 = ladderLength2("hit", "hit", dict1);
        auto r5 = ladderLength2("hit", "hot", dict1);

        unordered_set<string> dict3 = { "ted", "tex", "red", "tax", "tad", "den", "rex", "pee" };
        auto r6 = ladderLength2("red", "tax", dict3);

        unordered_set<string> dict4 =
        { "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob" };
        unordered_set<string> dict4_small =
        { "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus" };

        
        auto r8 = ladderLength2("cet", "ism", dict4_small);
        auto r7 = ladderLength2("cet", "ism", dict4);
}

    void test_wordladder()
    {
        unordered_set<string> dict1 = { "hot","dot","dog","lot","log" };
        unordered_set<string> dict2 = { "hot", "cog", "dot", "dog", "hit", "lot", "log" };
        assert(5 == ladderLength("hit", "cog", dict1));
        assert(5 == ladderLength("hit", "cog", dict2));

        assert(0 == ladderLength("hit", "xxg", dict1));

        assert(1 == ladderLength("hit", "hit", dict1));
        assert(2 == ladderLength("hit", "hot", dict1));

        unordered_set<string> dict3 = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
        assert(4 == ladderLength("red", "tax", dict3));
        
        unordered_set<string> dict4 = 
        {"kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob"};
        unordered_set<string> dict42 = dict4;
        unordered_set<string> dict5 =
        { "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus"};
        timetook = 0;
        called = 0;
        testUtil::timer t1;
        t1.start();
        auto r = ladderLength("cet", "ism", dict4);
        cout << r << endl;
        cout << t1.stop() << " ms" << endl;


        t1.reset();
        auto r2 = ladderLength_bfs("cet", "ism", dict42);
        cout << r2 << endl;
        cout << t1.stop() << " ms" << endl;
        
    }
};

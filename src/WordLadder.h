#include "Solution.h"

using namespace std;

class WordLadder: public  solution {

public:

    bool OffByOne(const string & a, const string &b)
    {
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

        return off;
    }

    vector<string> getAllVariations(const string & s)
    {
        vt<string> result;
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
        return result;
    }

    typedef set<string> Dictionary;
    szt minSol = INT_MAX;
    list<string>optSol;
    map<string, int> dist;
    void solve(const string & cur, const string & end, Dictionary &dict, list<string> & curPath)
    {
        if (cur == end)
        {
            if (minSol > curPath.size())
            {
                minSol = curPath.size();
                optSol = curPath;
            }
            return;
        }
        else if (OffByOne(cur, end)) {
            curPath.push_back(end);
            if (minSol > curPath.size())
            {
                minSol = curPath.size(); 
                optSol = curPath;
            }
            curPath.pop_back();
            return;
        }

        if (curPath.size() >= minSol) return;

        auto allVar = getAllVariations(cur);
        for (auto var : allVar)
        {
            auto it = dict.find(var);
            if (it != dict.end())
            {
                auto distIt = dist.find(*it);
                if (distIt == dist.end() || curPath.size() < distIt->second)
                {
                    string next = *it;
                    dist.emplace(*it, (int)curPath.size());
                    curPath.push_back(*it);
                    dict.erase(it);
                    solve(next, end, dict, curPath);
                    dict.insert(next);
                    curPath.pop_back();
                }
            }
        }

        //for (auto it = dict.begin(); it != dict.end(); )
        //{
        //    const string next = *it;
        //    if (OffByOne(cur, *it))
        //    {
        //        auto distIt = dist.find(next);
        //        if (distIt == dist.end() || curPath.size() < distIt->second)
        //        {
        //            dist.emplace(next, (int)curPath.size());
        //            curPath.push_back(next);
        //            string nextIter = "";
        //            it = dict.erase(it);
        //            if (it != dict.end()) nextIter = *it;
        //            solve(next, end, dict, curPath);
        //            curPath.pop_back();
        //            dict.insert(next);
        //            it = dict.find(nextIter);
        //            continue;
        //        }
        //    }
        //    ++it;
        //}

    }

    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        list<string> path(1,beginWord);
        Dictionary dict(wordList.begin(), wordList.end());
        dict.erase(beginWord);
        minSol = INT_MAX;
        optSol.clear();
        dist.clear();
        solve(beginWord, endWord, dict, path);
        return (int)optSol.size();
    }

    virtual void test()
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
        unordered_set<string> dict5 =
        { "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus"};
        testUtil::timer t1;
        t1.start();
        auto r = ladderLength("cet", "ism", dict5);
        cout << r << endl;
        cout << t1.stop() << " ms" << endl;
        
    }
};

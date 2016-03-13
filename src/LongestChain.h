#include "Solution.h"


using namespace std;

class LongestChain: public  solution {

public:

    int helper(string &s, set<string> &dict, map<string, int> & map)
    {
        int result = 0;
        for (int i = 0; i < s.size(); i++)
        {
            string news = s.substr(0, i) + s.substr(i + 1);
            
            
            if (dict.find(news) != dict.end())
            {
                if (map.find(news) != map.end())
                {
                    result = std::max(result, map[news]);
                }
                else
                {
                    result = std::max(result, helper(news, dict, map) + 1);
                }
            }
        }
        return result;
    }

    int longest_chain3(const vector < string >& words) {

        set<string> dict;
        map<string, int> map;

        for (string s : words)
        {
            dict.insert(s);
        }

        int longest = 0;
        for (auto s : words)
        {
            if (s.size() <= longest)
            {
                // no need to go further
                continue;
            }
            int len = helper(s, dict, map) + 1;
            map.emplace(s, len);
            longest = std::max(longest, len);
        }
        return longest;
    }
    
    vector<string> getAllMatch(string & s)
    {
        vector<string>ss(s.size(), "");
        //vector<string>ss;
        for (int i = 0; i < s.size(); i++)
        {
            string news = s.substr(0, i) + s.substr(i + 1);
            ss[i] = std::move(news);
            //ss.push_back(std::move(news));
        }

        return std::move(ss);
    }

    /*
    * Complete the function below.
    */
    int longest_chain1(vector < string >& w) {
        //testUtil::timer timer;
        //timer.start();
        map<szt, set<string>> M;
        for (auto i : w)
        {
            szt len = i.size();
            auto it = M.find(len);
            if (it == M.end())
            {
                set<string> vv;
                vv.insert(i);
                M.emplace(len, vv);
            }
            else
            {
                it->second.insert(i);
            }
        }
        //timer.stop();
        //cout << "first sorting took " << timer.getTime() << " ms" << endl;
        int result = 0;

        //timer.reset();
        map<string, pair<int, szt>> count;
        szt maxlen = M.rbegin()->first;
        szt minlen = M.begin()->first;
#define mkp make_pair
        for (auto letter : M[1])
        {
            count[letter] = make_pair(1, maxlen - minlen + 1);
        }
        for (auto word : w)
        {
            count[word] = mkp(1, maxlen - minlen + 1);
        }

        //cout << "prep took " << timer.stop() << " ms" << endl;

        int c = 0;

        //timer.reset();
        int currentMax = 1;
        for (int i = 2; i <= maxlen; i++)
        {
            auto all = M.find(i);
            if (all != M.end())
            {
                auto pre = M.find(i - 1);

                szt maxPosssible = maxlen - i;
                forward_list<string> toRemove;
                for (auto word : all->second)
                {
                    
                    if (pre == M.end() || pre->second.empty())
                    {
                        count[word] = mkp(1, 1 + maxPosssible);
                    }
                    else
                    {
                        int wordLen = 1;
                        szt maxPos = maxPosssible;
                        for (int i = 0; i < word.size(); i++)
                        {
                            string news = word.substr(0, i) + word.substr(i + 1);
                            auto it = pre->second.find(news);
                            if (it != pre->second.end())
                            {
                                wordLen = std::max(wordLen, count[news].first + 1);
                            }
                        }

                        count[word] = mkp(wordLen, wordLen + maxPosssible);
                        currentMax = std::max(currentMax, wordLen);
                    }

                    if (count[word].second <= currentMax)
                    {
                        //toRemove.push_back(word);
                        toRemove.push_front(word);
                    }
                }

                for (auto ww : toRemove)
                {
                    all->second.erase(ww);
                }
            }
        }
        //timer.stop();
        //cout << "main algo took " << timer.getTime() << " ms" << endl;
        //out.close();
        return currentMax;
    }




    void run(istream & in)
    {
        int n = readInt(in);
        vt<string> v;
        for (int i = 0; i < n; i++)
        {
            string line;
            getline(in, line);
            v.push_back(line);
        }
        //v = testUtil::randomGenWords(1000, 100);
        testUtil::timer timer;
        timer.start();
        cout << "lc3: ";
        cout << longest_chain3(v) << endl;;
        timer.stop();
        cout << "Overall: " << timer.getTime() << " ms" << endl;

        

        cout << "lc1: ";
        timer.reset();
        cout << longest_chain1(v) << endl;;
        timer.stop();
        cout << "Overall: " << timer.getTime()<< " ms" << endl;

    }
};

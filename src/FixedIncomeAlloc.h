#include "Solution.h"

using namespace std;

class FixedIncomeAlloc: public  solution {

public:


    struct portfolio
    {
        string id;
        int order;
        int alloc_amt;
        portfolio(string id, int order)
            :id(id), order(order), alloc_amt(0)
        {
        }

        bool operator < (const portfolio & rhs) const
        {
            if (this->order != rhs.order)
            {
                return this->order < rhs.order;
            }

            return this->id < rhs.id;
        }
        bool operator () (const portfolio & lhs, const portfolio & rhs) const
        {
            if (lhs.order != rhs.order)
            {
                return lhs.order < rhs.order;
            }

            return lhs.id < rhs.id;
        }
    };


    bool is_tradeable(int alloc_amt, int incre, int min_size)
    {
        if (alloc_amt == 0) return true;
        if (alloc_amt < min_size) return false;
        int i = (alloc_amt - min_size) % incre;
        return i == 0;
    }

    int alloc(int min_size, int incre, int alloc_amt)
    {
        if (alloc_amt < min_size) return 0;
        if (is_tradeable(alloc_amt, incre, min_size)) return alloc_amt;
        int i = (alloc_amt - min_size) / incre;
        return (min_size + i*incre);
    }


    int alloc(list<portfolio> &ports, int alloc_amt, int n, int min_size, int incre)
    {

        int total = 0;
        int done = 0;

        if (ports.size() == 0) return 0;

        bool allAllocted = true;
        for (auto p : ports)
        {
            if (p.alloc_amt == 0) allAllocted = false;
        }
        if (allAllocted) return 0;

        for_each(ports.begin(), ports.end(), [&total](portfolio & it)
        {
            total += it.order;
        });

        list<portfolio*> half;
        for(portfolio & p : ports)
        {
            if (p.alloc_amt > 0) continue;

            double prop_alloc = alloc_amt * p.order * 1.0 / total;
            if (prop_alloc > min_size)
            {
                if (prop_alloc >= p.order)
                {
                    //if (is_tradeable(p.order - prop_alloc, incre, min_size))
                    {
                        p.alloc_amt = p.order;
                        done += p.order;
                    }
                }
                else
                {
                    int rounded_amt = alloc(min_size, incre, (int)prop_alloc);
                    if (is_tradeable(p.order - rounded_amt, incre, min_size))
                    {
                        p.alloc_amt = rounded_amt;
                        done += rounded_amt;
                    }
                }
            }
            else
            {
                if (prop_alloc > min_size / 2.0)
                {
                    if (is_tradeable(p.order - min_size, incre, min_size))
                    {
                        p.alloc_amt = min_size;
                        done += min_size;
                    }
                }
            }
            alloc_amt -= p.alloc_amt;
            total -= p.order;
        }
        

        return 0;
    }


    void run(istream & in)
    {
        int n = readInt(in);
        vint x = readInts(in);
        int min_size = x[0];
        int incre = x[1];
        int alloc_int = x[2];
        list<portfolio> ports;
        for (int i = 0; i < n; i++)
        {
            string line;
            getline(in, line);
            vector<string> v = split(line, ' ');
            portfolio p(v[0], atoi(v[1].c_str()));
            ports.push_front(p);
        }
        ports.sort();
        int ret = alloc(ports, alloc_int, n, min_size, incre);



        std::function<bool(const portfolio & lhs, const portfolio & rhs)> comp = [](const portfolio & lhs, const portfolio & rhs)
        {
            return lhs.id < rhs.id;
        };
        ports.sort(comp);
        for (auto p : ports)
        {
            cout << p.id << ":" << p.alloc_amt << endl;
        }
        return;
    }

    virtual void test()
    {
        ifstream in("a.in");
        run(in);
    }
};

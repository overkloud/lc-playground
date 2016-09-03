#include "Solution.h"

using namespace std;

class LRUCache: public  solution {

public:

    struct node
    {
        ll time;
        int val;
        int key;
        node(int key, int val, ll time)
        {
            this->val = val;
            this->time = time;
            this->key = key;
        }
    };

    int cap;
    int size;
    ll count;

    std::function<bool(const node* a, const node* b)>  cmp = [](const node* a, const node* b)
    {
        return a->time > b->time;
    };

    vector<node*> q;
    map<int, node*> t;

    LRUCache()
    {
        this->cap = 0;
        this->size = 0;
        this->count = 0;
    }

    LRUCache(int capacity) {
        this->cap = capacity;
        this->size = 0;
        this->count = 0;
    }

    int get(int key) {
        if (t.find(key) != t.end())
        {
            auto x = t.find(key);
            //x->second.time = count++;
            node* n = x->second;
            n->time= count++;
            std::make_heap(q.begin(), q.end(), cmp);
            return n->val;
        }
        else
        {
            return -1;
        }
    }

    void set(int key, int value) {
        if (t.find(key) != t.end())
        {
            auto x = t.find(key);
            node * n = x->second;
            n->time = count++;
            n->val = value;
            std::make_heap(q.begin(), q.end(), cmp);
        }
        else
        {
            if (size >= cap)
            {
                node* top = q.front();
                t.erase(top->key);
                std::pop_heap(q.begin(), q.end(), cmp);
                q.pop_back();
                delete top;
                size--;
            }

            node *n = new node(key, value, count++);
            q.push_back(n);
            std::push_heap(q.begin(), q.end());
            t.emplace(key, n);
            size++;
        }

    }

    virtual void test()
    {
        LRUCache cache(2);
        //cache.set(0, 2);
        //assert(cache.get(0) == 2);
        //cache.set(0, 1);
        //assert(cache.get(0) == 1);
        //cache.set(1, 3);
        //cache.set(2, 4);
        //assert(cache.get(1) == 3);
        //cache.set(3, 5);
        //assert(cache.get(0)==-1);
        //assert(cache.get(1)==3);
        //assert(cache.get(2)==-1);
        //assert(cache.get(3)==5);

        cache.set(2, 1);
        cache.set(2, 2);
        int i = cache.get(2);
        cache.set(1, 1);
        cache.set(4, 1);
        i = cache.get(2);
    }
};

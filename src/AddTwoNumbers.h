#include "Solution.h"

class AddTwoNumbers : public solution
{
public:

    struct ListNode 
    {
        int val;
        ListNode * next;

        ListNode(int x) : val(x), next(NULL)
        {}
    };

    ll nodeToInt (ListNode *a)
    {
        if(!a) return -1;

        ll power = 0;
        ll intA = 0;
        while(a)
        {
            intA += (ll)pow(10, power) * a->val;
            power++;
            a = a->next;            
        }


        return intA;
    }

    ListNode *intToNode(int64_t a)
    {
        //ListNode * p = new ListNode

        ListNode * head = NULL;
        ListNode * prev = NULL;

        if (a == 0)
        {
            head = new ListNode(0);
        }


        while(a != 0)
        {
            int n = a % 10;
            a = a / 10;

            //ListNode p = 

            if (!head)
            {
                head = new ListNode(n);
                prev = head;
            }
            else
            {
                ListNode * newNode = new ListNode(n);
                prev->next = newNode;
                prev = newNode;// = prev;
            }
        }

        return head;
    }

    ListNode * addTwoNumbers(ListNode * a, ListNode * b)
    {
        if(!a || !b) return 0;

        ll aa = nodeToInt(a);
        ll bb = nodeToInt(b);
        ll sum = aa + bb;

        return intToNode(sum);
    }


    void test()
    {
        cout << "Running test for add two numbers. " << endl;
    	assert(nodeToInt(addTwoNumbers(intToNode(342), intToNode(465)))==807);
    	assert(nodeToInt(addTwoNumbers(intToNode(100), intToNode(30000)))==30100);
    	assert(nodeToInt(addTwoNumbers(intToNode(2001), intToNode(2)))==2003);
        cout << nodeToInt(addTwoNumbers(intToNode(9), intToNode(9999999999991))) << endl;
    }
};


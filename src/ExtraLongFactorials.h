#include "Solution.h"

using namespace std;

class ExtraLongFactorials: public  solution {

public:

    struct bigInt
    {
        vector<int> digits;
        const static int DIGITSPERINT = 4;

        bigInt() {};

        bigInt(const long long i)
        {
            long long in = i;
            //int d = i % pow(10, 8);
            do
            {
                int mod = in % (int)pow(10, DIGITSPERINT);
                digits.push_back(mod);
                in = in / (int)pow(10, DIGITSPERINT);

            } while (in / pow(10, DIGITSPERINT) > 0);
        };

        bigInt operator* (const int rhs)
        {
            bigInt result;
            int mod = 0;

            for (int i = 0; i < this->digits.size(); i++)
            {
                int prod = digits[i] * rhs;
                if (mod > 0)
                {
                    prod += mod;
                }
                result.digits.push_back(prod % (int)pow(10, DIGITSPERINT));
                mod = prod / (int)pow(10, DIGITSPERINT);
            }

            while (mod > 0)
            {
                result.digits.push_back(mod % (int)pow(10, DIGITSPERINT));
                mod = mod / (int)pow(10, DIGITSPERINT);
            }

            return result;
        }

        bigInt& operator = (const bigInt & rhs)
        {
            this->digits.clear();
            this->digits = rhs.digits;
            return *this;
        }

        void print(ostream & out)
        {

            std::function<string(int)> padZeros = [](int k)
            {
                stringstream ss;
                for (int i = DIGITSPERINT - 1; i >= 1; i--)
                {
                    if (k < pow(10, i))
                    {
                        ss << '0';
                    }
                }
                ss << k;
                return ss.str();
            };

            for (szt i = digits.size() - 1; i >= 0; i--)
            {
                if (i == digits.size() - 1) out << (digits[i]);
                else out << padZeros(digits[i]);
            }
            out << endl;
        }
    };

    _int64 fact(int i)
    {
        if (i == 1) return 1;
        if (i == 0) return 1;

        return fact(i - 1) * i;
    }

    bigInt bigIntFact(int i)
    {
        if (i <= 12)
        {
            return bigInt(fact(i));
        }
        else
        {
            bigInt result(fact(12));
            for (int j = 13; j <= i; j++)
            {
                result = result * j;
            }
            return result;
        }
    }

    void calcLongFactorial(int i)
    {
        if (i <= 12)
        {
            cout << fact(i) << endl;
        }
        else
        {
            bigIntFact(i).print(cout);
        }
    }

    virtual void test()
    {
        //cout << fact(18) << endl;
        //for (int i = 1)
        bigIntFact(18).print(cout);
    }
};

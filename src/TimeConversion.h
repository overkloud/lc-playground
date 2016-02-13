#include "Solution.h"

using namespace std;


/***
from HackerRank HR
Given a time in AM/PM format, convert it to military (24-hour) time.

Note: Midnight is 12:00:00AM on a 12-hour clock and 00:00:00 on a 24-hour clock. Noon is 12:00:00PM on a 12-hour clock and 12:00:00 on a 24-hour clock.

Input Format

A time in 12-hour clock format (i.e.: hh:mm:ssAM or hh:mm:ssPM), where 01¡Ühh¡Ü1201¡Ühh¡Ü12.

Output Format

Convert and print the given time in 24-hour format, where 00¡Ühh¡Ü2300¡Ühh¡Ü23.
***/


class TimeConversion : public  solution {

public:

    string convert(const string & s)
    {
        if (s.empty() || s.size() != 10) return "";

        int hr = atoi(s.substr(0, 2).c_str());
        int min = atoi(s.substr(3, 2).c_str());
        int sec = atoi(s.substr(6, 2).c_str());
        bool isAm = s.substr(8, 2) == "AM";

        std::function<string(int)> padZero = [](int i)
        {
            stringstream ss;
            if (i < 10) ss << "0";
            ss << i;
            return ss.str();
        };

        stringstream ss;
        if (hr != 12)
        {
            if (!isAm) hr += 12;
            
            ss << padZero(hr) << ":" << padZero(min) << ":" << padZero(sec);
            return ss.str();
        }
        else
        {
            if (isAm) hr = 0;
            else hr = 12;
            ss << padZero(hr) << ":" << padZero(min) << ":" << padZero(sec);
        }

        return ss.str();
    }

    void run()
    {
        string time;
        cin >> time;

        return ;
    }

    virtual void test()
    {

    }
};

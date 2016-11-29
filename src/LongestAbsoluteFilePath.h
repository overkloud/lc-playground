#include "Solution.h"

using namespace std;

class LongestAbsoluteFilePath: public  solution {

public:

    int lengthLongestPath(string s) {
        szt result = 0;
        szt dirLen = 0;
        stack<int> dirs;
        const char tab = '\t';
        const char eol = '\n';

        szt i = 0;
        std::function<bool(szt p, szt q)> isFile = [&s](szt p, szt q)
        {
            auto dot = s.find('.', p);
            return dot < q;
        };
        while (i < s.size())
        {
            int lv = 1;
            while (s[i] == '\t')
            {
                lv++; i++;
            }

            szt end = s.find(eol, i);
            if (end == string::npos) end = s.size();
            if (!isFile(i, end))
            {
                if (lv > dirs.size())
                {
                    //string dirname = s.substr(i, end - i);
                    dirs.push(end - i);
                    dirLen += (end-i+1);
                }
                else
                {
                    //const string &dirName = dirs.top();
                    while (dirs.size() >= lv)
                    {
                        auto len = dirs.top();
                        dirLen -= (len+1);
                        dirs.pop();
                    }
                    dirLen += (end - i + 1);
                    dirs.push(end - i);
                }
            }
            else
            {
                while (dirs.size() >= lv)
                {
                    auto len = dirs.top();
                    dirLen -= (len + 1);
                    dirs.pop();
                }
                result = std::max(result, dirLen + (end - i));
            }
            i = end + 1;
        }

        return result;
    }

    virtual void test()
    {
        string s = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
        string f = "dir\\subdir1\\file.ext";
        auto r = lengthLongestPath(s);
        assert(r == f.size());


        s = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
        r = lengthLongestPath(s); // should be 32
        assert(r == 32);

        s = "dir\n\tsubdir1\n\tsubdir2";
        r = lengthLongestPath(s);
        assert(r == 0);

        s = "dir\n    file.txt";
        r = lengthLongestPath(s);
        assert(r == 12);

        s = "dir\n        file.txt";
        r = lengthLongestPath(s);
        assert(r == 16);

        s = "   file.txt";
        r = lengthLongestPath(s);
        assert(r == s.size());

        s = "a\n\tb.txt\na2\n\tb2.txt";
        r = lengthLongestPath(s);
        assert(r == 9);

        s = "skd\n\talskjv\n\t\tlskjf\n\t\t\tklsj.slkj\n\t\tsdlfkj.sdlkjf\n\t\tslkdjf.sdfkj\n\tsldkjf\n\t\tlskdjf\n\t\t\tslkdjf.sldkjf\n\t\t\tslkjf\n\t\t\tsfdklj\n\t\t\tlskjdflk.sdkflj\n\t\t\tsdlkjfl\n\t\t\t\tlskdjf\n\t\t\t\t\tlskdjf.sdlkfj\n\t\t\t\t\tlsdkjf\n\t\t\t\t\t\tsldkfjl.sdlfkj\n\t\t\t\tsldfjlkjd\n\t\t\tsdlfjlk\n\t\t\tlsdkjf\n\t\tlsdkjfl\n\tskdjfl\n\t\tsladkfjlj\n\t\tlskjdflkjsdlfjsldjfljslkjlkjslkjslfjlskjgldfjlkfdjbljdbkjdlkjkasljfklasjdfkljaklwejrkljewkljfslkjflksjfvsafjlgjfljgklsdf.a";
        r = lengthLongestPath(s);
        assert(r == 133);
    }
};

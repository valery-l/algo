
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>
#include <tuple>
#include <set>
#include <chrono>

using namespace std;

void speed_up()
{
    static bool boosted = []()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        return true;
    }();
}

////////////////////////////////////////////////////////////

using num_t = int64_t;

struct str_hash
{
    explicit str_hash(string const& s)
        : origin_(s)
        , hash_ (s.size() + 1)
        , power_(s.size() + 1)
    {
        static int p = 1000001;

        const size_t N = s.size();

        hash_ [0] = 0;
        power_[0] = 1;

        for (size_t i = 0; i < N; ++i)
        {
            power_[i + 1] = p * power_[i];
            hash_ [i + 1] = hash_[i] * p + s[i];
        }
    }

    num_t get_hash(size_t l, size_t r) const
    {
        return hash_[r + 1] - hash_[l] * power_[r - l + 1];
    }

    string const& origin() const
    {
        return origin_;
    }

private:
    string        origin_;
    vector<num_t> hash_;
    vector<num_t> power_;
};

size_t substr_count(string const& str)
{
    size_t num = 0;
    auto n = str.size();

    str_hash sh(str);

    unordered_set<num_t> prefix_hash;
    for (size_t i = 1; i <= n; ++i)
    {
        prefix_hash.clear();
        for (size_t j = 0; j <= n - i; ++j)
            prefix_hash.insert(sh.get_hash(j, j + i - 1));

        num += prefix_hash.size();
    }

    return num;
}

struct elapsed
{
   elapsed()
       : start_(chrono::steady_clock::now())
   {
   }

   ~elapsed()
   {
       auto stop = chrono::steady_clock::now();
       cout << "Spent in ms: " << chrono::duration_cast<chrono::milliseconds>(stop - start_).count() << endl;
   }

private:
   chrono::time_point<chrono::steady_clock> start_;
};


void test_bacon(string const& str, size_t expected)
{
   elapsed els;
   auto num = substr_count(str);
   bool res = (num == expected);
   cout /*<< str */ << (res ? " YES " : " NO ") << num << endl;
}

void bacon_cipher()
{
    //test_bacon("aaba", 8);
    //test_bacon("", 0);
    //test_bacon("a", 1);
    //test_bacon("aaa", 3);
    //test_bacon("aaab", 7);
    //test_bacon("abcd", 10);

//     cout << "XXX" << endl;
// 
//     test_bacon("afdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjafdksfjhklasdhfkldashfkljasdhfklhasdklfhasldjkfhklasdhfkjasdhfkljasdhfkljhasdfklhasdkfhjasdklhfkasdhjfkljasdhfkajsdhfkljahsdfkljhasdfklhasdkjfhasdkljfhasdkljfhklasdhjfkljasdhfkljasdhfklasdhfkhjasdfkhjasdfklhasdfkhasdklfhasdklfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjlfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjlfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjlfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhjlfjhasdklfhaskldjfhklasdjfhkasdjhfklasdjhfklasdhjfklasdjfhasdkljfhadklsjfhlkasdjfhklasdjhfaklsdfhj", 1398241);
//     
//     string s(5000, 'a');
//     test_bacon(s, 5000);

    char a[6001];
    gets_s(a, 6000);
    
    elapsed els;
    cout << substr_count(a) << endl;
}

string common_substr_of_len(str_hash const& sha, str_hash const& shb, int m)
{
    unordered_set<num_t> hashs;

    for (size_t i = 0, n = sha.origin().size(); i <= n - m; ++i)
    {
        size_t l = i;
        size_t r = i + m - 1;

        auto x = sha.origin().substr(l, m);

        auto pr = hashs.insert(sha.get_hash(l, r));
        if (!pr.second)
            return sha.origin().substr(l, m);

        x = shb.origin().substr(l, m);

        pr = hashs.insert(shb.get_hash(l, r));
        if (!pr.second)
            return shb.origin().substr(l, m);
    }

    return "";
}

string find_largest_substring(string const& a, string const& b)
{
    str_hash sha(a);
    str_hash shb(b);

    int l = 1;
    int r = int(a.size());

    string result;
    while (l <= r)
    {
        int m = (l + r) / 2;
        
        auto s = common_substr_of_len(sha, shb, m);

        if (s.size() > result.size())
            result = s;

        if (s.empty())
            r = m - 1; 
        else
            l = m + 1;
    }

    return result;
}

void test_freedom(string const& a, string const& b, string const& expected)
{
    string s = find_largest_substring(a, b);
    bool res = (s == expected);
    cout << (res ? " YES " : " NO ") << s << endl;
}

void freedom_of_choice()
{
//     test_freedom("VOTEFORTHEGREATALBANIAFORYOU", "CHOOSETHEGREATALBANIANFUTURE", "THEGREATALBANIA");
//     test_freedom("", "", "");
//     test_freedom("a", "a", "a");
//     test_freedom("a", "b", "");
//     test_freedom("THEGREATALBANIA", "THEGREATALBANIA", "THEGREATALBANIA");
// 
//     return; 

    size_t n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    cout << find_largest_substring(a, b);
}


int main()
{
    speed_up();
    
    //bacon_cipher();
    freedom_of_choice();




    return 0;
}
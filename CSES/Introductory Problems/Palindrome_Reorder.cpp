#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define ld long double
#define endl "\n"
#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, x) cout << fixed << setprecision(n) << x
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define forp(i, a, b) for (ll i = a; i < b; i++)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define spc << " "
#define sp << " " <<
#define trav(i, a) for (auto &i : a)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define si(a) ((int)(a).size())
#define pb push_back

#define int long long

using namespace std;

void solve()
{
    string s;
    cin >> s;

    int n = s.size();

    vector<int> freq(26, 0);

    //  Count the frequency of each character
    for (int i = 0; i < n; i++)
    {
        freq[s[i] - 'A']++;
    }

    int odd = 0;

    //  Count the number of characters with odd frequency
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2)
        {
            odd++;
        }
    }

    //  If there are more than 1 characters with odd frequency, then it is impossible to make a palindrome
    if (odd > 1)
    {
        cout << "NO SOLUTION" << endl;
        return;
    }

    string ans = "";

    //    If there are no characters with odd frequency, then we can make a palindrome by taking half of the characters with even frequency
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2 == 0)
        {
            for (int j = 0; j < freq[i] / 2; j++)
            {
                ans += (char)(i + 'A');
            }
        }
    }

    cout << ans;

    //   If there is a character with odd frequency, then we can make a palindrome by taking half of the characters with even frequency and all the characters with odd frequency
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2)
        {
            for (int j = 0; j < freq[i]; j++)
            {
                cout << (char)(i + 'A');
            }
        }
    }

    //   Print the second half of the palindrome
    reverse(all(ans));

    cout << ans << endl;
}

signed main()
{
    fast;

    int tc = 1;
    // cin >> tc;

    while (tc--)
    {
        solve();
    }

    return 0;
}
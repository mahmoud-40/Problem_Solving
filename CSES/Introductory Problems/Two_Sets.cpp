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
    int n;
    cin >> n;

    // sum of first n natural numbers
    int sum = n * (n + 1) / 2;

    // if sum is odd, then we can't divide it into two equal parts
    if (sum % 2)
    {
        cout << "NO" << endl;
        return;
    }

    // if sum is even, then we can divide it into two equal parts
    cout << "YES" << endl;

    // a and b are two sets
    vector<int> a, b;

    // sum of each set
    sum /= 2;

    // we will start from n and keep on adding numbers to a set until sum - n >= 0
    while (n)
    {
        // if sum - n >= 0, then we can add n to a set
        if (sum - n >= 0)
        {
            a.pb(n);
            sum -= n;
        }
        // if sum - n < 0, then we can add n to b set
        else
        {
            b.pb(n);
        }

        n--;
    }

    cout << a.size() << endl;

    for (auto x : a)
    {
        cout << x << " ";
    }

    cout << endl;

    cout << b.size() << endl;

    for (auto x : b)
    {
        cout << x << " ";
    }

    cout << endl;
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
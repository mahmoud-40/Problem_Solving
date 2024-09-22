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

const int mod = 1e9 + 7;

int fun(int a, int b)
{
    // base case
    if (b == 0)
        return 1;

    if (b == 1)
        return a % mod;

    // recursive call
    int x = fun(a, b / 2);

    x = (x * x) % mod; // a^(b/2) * a^(b/2)

    if (b % 2)
        x = (x * a) % mod; // a^(b/2) * a^(b/2) * a

    return x;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    n = n % mod;

    cout << fun(n, m) << endl;
}

signed main()
{
    fast;

    int tc = 1;
    cin >> tc;

    while (tc--)
    {
        solve();
    }

    return 0;
}

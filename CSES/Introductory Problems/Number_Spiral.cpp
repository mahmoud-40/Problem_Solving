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
#define forp(i, a, b) for (ll i = a; i < b; i++)
#define forn(i, a, b) for (ll i = a; i > b; i--)
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
    int n, m;
    cin >> n >> m;

    if (n > m)
    {
        ll ans = (n - 1) * (n - 1);
        ll add = 0;

        if (n % 2 != 0)
        {
            add = m;
        }
        else
        {
            add = 2 * n - m;
        }
        cout << ans + add << "\n";
    }
    else
    {
        ll ans = (m - 1) * (m - 1);
        ll add = 0;

        if (m % 2 == 0)
        {
            add = n;
        }
        else
        {
            add = 2 * m - n;
        }
        cout << ans + add << "\n";
    }
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
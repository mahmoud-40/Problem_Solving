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

    vector<int> w(n);

    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }

    int ans = LLONG_MAX;

    for (int i = 0; i < (1 << n); i++) // 2^n
    {
        int sum1 = 0, sum2 = 0;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j)) // if jth bit is set in i
            {
                sum1 += w[j];
            }
            else
            {
                sum2 += w[j];
            }
        }

        ans = min(ans, abs(sum1 - sum2));
    }

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
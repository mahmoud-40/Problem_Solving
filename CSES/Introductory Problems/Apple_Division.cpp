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

// There are n apples with known weights. Your task is to divide the apples into two groups so that the difference between the weights of the groups is minimal.

vector<int> a;
int n, tot, ans = INT32_MAX;

int fun(int i, int sum)
{
    // base case
    if (i >= si(a))
    {
        return abs(tot - 2 * sum); // why 2*sum? because we are dividing the array into two groups
    }

    // recursive call
    int add = fun(i + 1, sum + a[i]); // add a[i] to the current group

    int sub = fun(i + 1, sum); // don't add a[i] to the current group

    return min(add, sub);
}

void solve()
{
    cin >> n;

    a.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        tot += a[i];
    }

    cout << fun(0, 0) << endl;
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
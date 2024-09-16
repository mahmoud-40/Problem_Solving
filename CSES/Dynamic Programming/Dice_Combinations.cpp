#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define int long long

using namespace std;

const int MOD = 1000000007;
const int N = 1e6 + 5;

int memo[N];

int dp(int n)
{
    if (n == 0)
        return 1;
    if (memo[n] != -1)
        return memo[n];

    int ways = 0;

    for (int i = 1; i <= 6; ++i)
    {
        if (n - i >= 0)
        {
            ways = (ways + dp(n - i)) % MOD;
        }
    }

    memo[n] = ways;
    return ways;
}

void solve()
{
    int n;
    cin >> n;

    memset(memo, -1, sizeof(memo));

    cout << dp(n) << endl;
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

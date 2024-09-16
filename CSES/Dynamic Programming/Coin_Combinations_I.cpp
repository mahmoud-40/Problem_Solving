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

const int INF = 1e9;
const int MOD = 1000000007;

vector<int> a;
vector<int> memo;

int dp(int x)
{
    if (x == 0)
        return 1;
    if (x < 0)
        return 0;

    if (memo[x] != -1)
        return memo[x];

    int ans = 0;

    for (int coin : a)
    {
        ans = (ans + dp(x - coin)) % MOD;
    }

    return memo[x] = ans;
}

void solve()
{
    int n, x;
    cin >> n >> x;

    a.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    memo.assign(x + 1, -1);

    int ans = dp(x);

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

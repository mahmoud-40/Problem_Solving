#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define int long long
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back

/*
dp[i][j] = number of ways to get sum j using numbers 1,2,3,...,i
dp[i][j] = dp[i-1][j] + dp[i-1][j-i]

dp[i-1][j] means we are not including i
dp[i-1][j-i] means we are including i
*/

const int mod = 1e9 + 7;
int dp[501][125251];

bool vis[501][125251];

int fun(int i, int j)
{
    if (i == 0)
    {
        if (j == 0)
            return 1;
        return 0;
    }

    if (vis[i][j])
        return dp[i][j];

    vis[i][j] = 1;

    int ch1 = fun(i - 1, j);
    int ch2 = (j - i >= 0) ? fun(i - 1, j - i) : 0;

    return dp[i][j] = (ch1 + ch2) % mod;
}

void solve()
{
    int n;
    cin >> n;

    int sum = n * (n + 1) / 2;

    if (sum % 2)
    {
        cout << 0 << endl;
        return;
    }

    sum /= 2; // why? because we need to divide the sum into two equal parts

    cout << fun(n - 1, sum) << endl;
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int tc = 1;
    // cin >> tc;

    while (tc--)
    {
        solve();
    }
}

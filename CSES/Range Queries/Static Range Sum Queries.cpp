#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define input_txt                     \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define PQ priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define S second
#define F first
#define MP make_pair
#define endl "\n"
#define PI 3.14159265
#define tests   \
    ll t;       \
    cin >> t;   \
    ll i_t = 0; \
    while (i_t++ < t)

#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, x) cout << fixed << setprecision(n) << x
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
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
#define ins insert
#define pb push_back
#define mp make_pair
#define si(a) ((int)(a).size())
#define gcd(a, b) __gcd(a, b)
#define mem(b, z) memset(b, z, sizeof(b))
#define rn return

using namespace std;
#define int long long

vector<vector<long long>> sparse_table;
vector<int> LOG;

// update this variable to a value that has no effect on the answer of the operation
long long neutral = 0;

// update this function for the desired operation
long long merge(long long val1, long long val2)
{
    return (val1 + val2);
}

void build(vector<long long> &arr)
{
    int n = arr.size();
    LOG.resize(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        LOG[i] = __lg(i);
    }

    sparse_table.assign(LOG[n] + 1, vector<int>(n));

    sparse_table[0] = arr;

    for (int i = 1; i <= LOG[n]; ++i)
    {
        int len = 1 << (i - 1);
        for (int j = 0; j + 2 * len <= n; ++j)
        {
            sparse_table[i][j] = merge(sparse_table[i - 1][j], sparse_table[i - 1][j + len]);
        }
    }
}

// use this as a general case but a bit slower
long long query(int l, int r) // 0 indexed range, O(log(N))
{
    int len = r - l + 1;
    int cnt = 0;

    int ans = neutral;
    while (len)
    {
        if (len & 1)
        {
            ans = merge(ans, sparse_table[cnt][l]);
            l += 1 << cnt;
        }
        len >>= 1;
        cnt++;
    }

    return ans;
}

// use this for [min, max, or ,and, gcd, lcm] in O(1) time
long long query_overlap(int l, int r) // 0 indexed range, fast O(1) -> but must [(x op x) = x].
{
    int len = r - l + 1;
    int row = LOG[len];

    return merge(sparse_table[row][l], sparse_table[row][r - (1 << row) + 1]);
}

void b3dsh()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    loop(n)
    {
        cin >> a[i];
    }

    build(a);

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(l, r) << endl;
    }
}

signed main()
{
    fast;

    int tc = 1;
    // cin>>tc;

    while (tc--)
    {
        b3dsh();
    }
    return 0;
}
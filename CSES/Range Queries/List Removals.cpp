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

#define dpp(arr, i) memset(arr, i, sizeof(arr))
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
#define mod 1000000007
#define tests   \
    ll t;       \
    cin >> t;   \
    ll i_t = 0; \
    while (i_t++ < t)

#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, q_idx) cout << fixed << setprecision(n) << q_idx
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define forp(i, a, q) for (ll i = a; i < q; i++)
#define forn(i, a, q) for (ll i = a; i > q; i--)
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
#define gcd(a, q) __gcd(a, q)
#define mem(q, z) memset(q, z, sizeof(q))
#define rn return

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define multi_ordered_set tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>

void b3dsh()
{
    int n;
    cin >> n;
    vector<int> a(n), q(n);
    ordered_set s;

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        s.insert(i);
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> q[i];
    }

    vector<int> ans;

    for (int i = 0; i < n; ++i)
    {
        int q_idx = q[i] - 1;
        int idx = *s.find_by_order(q_idx);
        ans.push_back(a[idx]);
        s.erase(idx);
    }

    for (int i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

signed main()
{
    fast;
    ll t = 1;
    // cin >> t;

    while (t--)
    {
        b3dsh();
    }

    return 0;
}
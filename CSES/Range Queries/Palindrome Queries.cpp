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

struct Node
{
    int val;
    int mx;
    Node()
    {
        val = 0;
        mx = 0;
    }
    Node(int x)
    {
        val = x;
        x = x;
    }
};
struct SegTree
{
    int tree_size;
    vector<Node> seg_data;

    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n)
            tree_size *= 2;
        seg_data.resize(2 * tree_size, Node());
    }
    Node merge(Node &lf, Node &ri)
    {
        Node res = Node();
        res.mx = max(lf.mx, ri.mx);
        res.val = lf.val + ri.val;
        return res;
    }
    void init(vector<long long> &nums, int ni, int lx, int rx)
    {

        if (rx - lx == 1)
        {
            if (lx < (int)nums.size())
            {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }

        int mid = lx + (rx - lx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(vector<int> &nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void set(int idx, int val, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            seg_data[node] = val;
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, val, 2 * node + 1, lx, mid);
        else
            set(idx, val, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void set(int idx, int val)
    {
        set(idx, val, 0, 0, tree_size);
    }

    void update(int l, int r, int x, int node, int lx, int rx)
    {
        if (rx <= l || lx >= r || seg_data[node].mx < x)
            return;
        if (rx - lx == 1)
        {
            seg_data[node].val %= x;
            seg_data[node].mx = seg_data[node].val;
            return;
        }

        int mid = lx + (rx - lx) / 2;
        update(l, r, x, 2 * node + 1, lx, mid);
        update(l, r, x, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void update(int l, int r, int val)
    {
        update(l, r, val, 0, 0, tree_size);
    }

    int get_range(int l, int r, int node, int lx, int rx)
    {
        if (lx >= l && rx <= r)
            return seg_data[node].val;
        if (lx >= r || rx <= l)
            return 0;

        int mid = (lx + rx) / 2;
        int ans = get_range(l, r, 2 * node + 1, lx, mid);
        ans += get_range(l, r, 2 * node + 2, mid, rx);

        return ans;
    }
    int get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size);
    }
};

const int p = 31;
const int m = 1e9 + 9;

int compute_hash(const string &s)
{
    int hash = 0;
    int pow = 1;
    for (char c : s)
    {
        hash = (hash + (c - 'a' + 1) * pow) % m;
        pow = (pow * p) % m;
    }
    return hash;
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
    SegTree tree(n);
    tree.init(a);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            l--;
            int sum = tree.get_range(l, r);
            cout << sum << endl;
        }
        else if (type == 2)
        {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            tree.update(l, r, x);
        }
        else if (type == 3)
        {
            int k, x;
            cin >> k >> x;
            k--;
            tree.set(k, x);
        }
    }
}

signed main()
{
    fast;
    b3dsh();
    return 0;
}
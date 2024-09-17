#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define ll long long
#define endl "\n"

using namespace std;
#define int long long

struct Node
{
    int pref = 0;
    int suf = 0;
    int sum = 0;
    int best = 0;
    Node() = default;
    Node(int x)
    {
        sum = x;
        pref = suf = best = max(0LL, x);
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

    Node merge(const Node &lf, const Node &ri)
    {
        Node res;
        res.sum = lf.sum + ri.sum;
        res.suf = max(ri.suf, lf.suf + ri.sum);
        res.pref = max(lf.pref, lf.sum + ri.pref);
        res.best = max({lf.best, ri.best, ri.pref + lf.suf});
        return res;
    }

    void init(const vector<int> &nums, int ni, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)nums.size())
            {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }
        int mid = (lx + rx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);
        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(const vector<int> &nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void set(int idx, int value, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            seg_data[node] = Node(value);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, value, 2 * node + 1, lx, mid);
        else
            set(idx, value, 2 * node + 2, mid, rx);
        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }

    void set(int idx, int value)
    {
        set(idx, value, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx)
    {
        if (lx >= l && rx <= r)
            return seg_data[node];
        if (rx <= l || lx >= r)
            return Node();
        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);
        return merge(lf, ri);
    }

    int get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size).best;
    }
};

void b3dsh()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    SegTree tree(n);
    tree.init(a);
    while (q--)
    {
        int idx, val;
        cin >> idx >> val;
        idx--;
        tree.set(idx, val);
        cout << tree.get_range(0, n) << endl;
    }
}

signed main()
{
    fast;
    b3dsh();
    return 0;
}
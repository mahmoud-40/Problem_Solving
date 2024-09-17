#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

using namespace std;
#define int long long

class Node
{
public:
    int v = 0;
    Node() {}
    Node(int val) { v = val; }

    void merge(const Node &l, const Node &r)
    {
        v = l.v + r.v;
    }
};

class Update
{
public:
    int add_val = 0;     // Add this value
    int set_val = -1;    // Set to this value (-1 means no set operation)
    bool is_set = false; // Set flag

    Update() {};
    Update(int add_val, bool is_set = false, int set_val = -1) : add_val(add_val), is_set(is_set), set_val(set_val) {}

    void combine(const Update &otherUpdate, const int &tl, const int &tr)
    {
        if (otherUpdate.is_set)
        {
            is_set = true;
            set_val = otherUpdate.set_val; // Override the set value
            add_val = otherUpdate.add_val; // Reset add to the new set value
        }
        else
        {
            add_val += otherUpdate.add_val; // Just accumulate add value
        }
    }

    void apply(Node &node, const int &tl, const int &tr) const
    {
        if (is_set)
        {
            node.v = (tr - tl + 1) * set_val; // Set the entire range to set_val
        }
        node.v += (tr - tl + 1) * add_val; // Apply the accumulated add_val
    }
};

template <typename node, typename update>
class SegTree
{
public:
    int tree_size;
    vector<node> seg_data;
    vector<update> unpropUpd;
    vector<bool> isLazy;
    node identityElement;
    update identityTransformation;

    SegTree() {}
    SegTree(int l)
    {
        tree_size = l;
        seg_data.resize(4 * tree_size);
        isLazy.resize(4 * tree_size);
        unpropUpd.resize(4 * tree_size);
        identityElement = node();
        identityTransformation = update();
    }

    void apply(const int &v, const int &tl, const int &tr, const update &upd)
    {
        if (tl != tr)
        {
            isLazy[v] = true;
            unpropUpd[v].combine(upd, tl, tr);
        }
        upd.apply(seg_data[v], tl, tr);
    }

    void pushDown(const int &v, const int &tl, const int &tr)
    {
        if (!isLazy[v])
            return;
        isLazy[v] = false;
        int tm = (tl + tr) / 2;
        apply(2 * v, tl, tm, unpropUpd[v]);
        apply(2 * v + 1, tm + 1, tr, unpropUpd[v]);
        unpropUpd[v] = identityTransformation;
    }

    template <typename T>
    void init(const T &a, const int &v, const int &tl, const int &tr)
    {
        if (tl == tr)
        {
            seg_data[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        init(a, 2 * v, tl, tm);
        init(a, 2 * v + 1, tm + 1, tr);
        seg_data[v].merge(seg_data[2 * v], seg_data[2 * v + 1]);
    }

    node query(const int &v, const int &tl, const int &tr, const int &l, const int &r)
    {
        if (tl > r || tr < l)
            return identityElement;
        if (l <= tl && tr <= r)
            return seg_data[v];

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        node leftAns = query(2 * v, tl, tm, l, r);
        node rightAns = query(2 * v + 1, tm + 1, tr, l, r);
        node ans;
        ans.merge(leftAns, rightAns);
        return ans;
    }

    void update_range(const int &v, const int &tl, const int &tr, const int &l, const int &r, const update &upd)
    {
        if (l <= tl && tr <= r)
        {
            apply(v, tl, tr, upd);
            return;
        }
        if (tl > r || tr < l)
            return;

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        update_range(2 * v, tl, tm, l, r, upd);
        update_range(2 * v + 1, tm + 1, tr, l, r, upd);
        seg_data[v].merge(seg_data[2 * v], seg_data[2 * v + 1]);
    }

    template <typename T>
    void init(const T &a)
    {
        init(a, 1, 0, tree_size - 1);
    }

    node query(const int &l, const int &r)
    {
        return query(1, 0, tree_size - 1, l, r);
    }

    void update_range(const int &l, const int &r, const update &upd)
    {
        update_range(1, 0, tree_size - 1, l, r, upd);
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
    SegTree<Node, Update> tree(n);
    tree.init(a);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, u;
            cin >> l >> r >> u;
            l--, r--;
            tree.update_range(l, r, Update(u, false)); // Range add
        }
        else if (type == 2)
        {
            int l, r, u;
            cin >> l >> r >> u;
            l--, r--;
            tree.update_range(l, r, Update(0, true, u)); // Range set
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << tree.query(l, r).v << endl;
        }
    }
}

signed main()
{
    fast;
    b3dsh();
    return 0;
}

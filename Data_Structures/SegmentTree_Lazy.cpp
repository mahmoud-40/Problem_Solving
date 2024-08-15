#include <vector>
using namespace std;

struct Node
{
    long long sum;
    long long lazy;
    bool is_lazy;

    Node() : sum(0), lazy(0), is_lazy(false) {}

    void add(int x, int len)
    {
        sum += x * len;
        lazy += x;
        is_lazy = true;
    }
};

struct SegTree
{
    int sz;
    vector<Node> data;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n)
            sz *= 2;
        data.resize(2 * sz, Node());
    }

    Node merge(Node &lf, Node &ri)
    {
        Node ans;
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void init(vector<int> &a, int ni, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                data[ni].sum = a[lx];
            }
            return;
        }

        int mid = lx + (rx - lx) / 2;
        init(a, 2 * ni + 1, lx, mid);
        init(a, 2 * ni + 2, mid, rx);

        data[ni] = merge(data[2 * ni + 1], data[2 * ni + 2]);
    }

    void init(vector<int> &a)
    {
        init(a, 0, 0, sz);
    }

    void propagate(int ni, int lx, int rx)
    {
        if (rx - lx == 1 || !data[ni].is_lazy)
            return;

        int len = rx - lx;
        data[2 * ni + 1].add(data[ni].lazy, (len + 1) / 2);
        data[2 * ni + 2].add(data[ni].lazy, len / 2);

        data[ni].is_lazy = false;
        data[ni].lazy = 0;
    }

    void set(int l, int r, int value, int ni, int lx, int rx)
    {
        propagate(ni, lx, rx);

        if (lx >= l && rx <= r)
        {
            data[ni].add(value, rx - lx); // Apply the update
            return;
        }
        if (rx <= l || lx >= r)
            return;

        int mid = lx + (rx - lx) / 2;
        set(l, r, value, 2 * ni + 1, lx, mid);
        set(l, r, value, 2 * ni + 2, mid, rx);

        data[ni] = merge(data[2 * ni + 1], data[2 * ni + 2]);
    }

    void set(int l, int r, int value)
    {
        set(l, r, value, 0, 0, sz);
    }

    Node get_range(int l, int r, int ni, int lx, int rx)
    {
        propagate(ni, lx, rx);

        if (lx >= l && rx <= r)
            return data[ni];
        if (rx <= l || lx >= r)
            return Node();

        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * ni + 1, lx, mid);
        Node ri = get_range(l, r, 2 * ni + 2, mid, rx);

        return merge(lf, ri);
    }

    long long get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, sz).sum;
    }
};

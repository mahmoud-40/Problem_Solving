#include <vector>

using namespace std;

struct Node
{
    int val;

    Node()
    {
        val = 0; // update with a value that has no effect on the answer
    }

    Node(int x)
    {
        val = x;
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

    // update this function for the desired operation
    Node merge(Node &lf, Node &ri)
    {
        Node ans = Node();
        ans.val = lf.val + ri.val;
        return ans;
    }

    void init(vector<int> &a, int ni, int lx, int rx)
    {

        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                data[ni] = Node(a[lx]);
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

    void set(int idx, int value, int ni, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            data[ni] = Node(value);
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, value, 2 * ni + 1, lx, mid);
        else
            set(idx, value, 2 * ni + 2, mid, rx);

        data[ni] = merge(data[2 * ni + 1], data[2 * ni + 2]);
    }
    void set(int idx, int value)
    {
        set(idx, value, 0, 0, sz);
    }

    Node get(int l, int r, int ni, int lx, int rx)
    {
        if (lx >= l && rx <= r)
            return data[ni];
        if (rx <= l || lx >= r)
            return Node();

        int mid = (lx + rx) / 2;

        Node lf = get(l, r, 2 * ni + 1, lx, mid);
        Node ri = get(l, r, 2 * ni + 2, mid, rx);
        return merge(lf, ri);
    }

    int get(int l, int r) // [l,r)
    {
        return get(l, r, 0, 0, sz).val;
    }
};

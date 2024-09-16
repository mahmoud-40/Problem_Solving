#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

class FenwickTree2D
{
private:
    int n, m;
    vector<vector<long long>> tree;

    static int lsb(int i)
    {
        return i & -i;
    }

    long long pref(int x, int y)
    {
        long long sum = 0;
        for (int i = x; i > 0; i -= lsb(i))
        {
            for (int j = y; j > 0; j -= lsb(j))
            {
                sum += tree[i][j];
            }
        }
        return sum;
    }

public:
    FenwickTree2D(int rows, int cols) : n(rows + 1), m(cols + 1)
    {
        tree.resize(n, vector<long long>(m, 0));
    }

    void add(int x, int y, long long value)
    {
        for (int i = x; i < n; i += lsb(i))
        {
            for (int j = y; j < m; j += lsb(j))
            {
                tree[i][j] += value;
            }
        }
    }

    long long sum(int x, int y)
    {
        return pref(x, y);
    }

    long long sum(int x1, int y1, int x2, int y2)
    {
        return pref(x2, y2) - pref(x1 - 1, y2) - pref(x2, y1 - 1) + pref(x1 - 1, y1 - 1);
    }
};

void b3dsh()
{
    int n, q;
    cin >> n >> q;
    FenwickTree2D fenwick(n, n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char ch;
            cin >> ch;
            if (ch == '*')
            {
                fenwick.add(i, j, 1);
            }
        }
    }

    while (q--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ans = fenwick.sum(x1, y1, x2, y2);
        cout << ans << endl;
    }
}

signed main()
{
    fast;
    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        b3dsh();
    }
    return 0;
}

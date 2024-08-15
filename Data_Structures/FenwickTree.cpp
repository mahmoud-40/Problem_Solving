#include <vector>
using namespace std;

class FenwickTree
{
private:
    int n;
    vector<long long> tree;

    static int lsb(int i)
    {
        return i & -i;
    }

    long long pref(int i)
    {
        long long sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            i -= lsb(i);
        }
        return sum;
    }

public:
    FenwickTree(const vector<long long> &values)
    {
        n = values.size();
        tree.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            add(i + 1, values[i]);
        }
    }

    FenwickTree(int sz) : n(sz + 1), tree(n, 0) {}

    void update_range(int left, int right, long long val)
    {
        add(left, val);
        if (right + 1 < n) // Ensure within bounds
            add(right + 1, -val);
    }

    void add(int i, long long v)
    {
        while (i < n)
        {
            tree[i] += v;
            i += lsb(i);
        }
    }

    void set(int i, long long v)
    {
        add(i, v - sum(i, i));
    }

    long long get(int i)
    {
        return pref(i) - pref(i - 1);
    }

    long long sum(int left, int right)
    {
        return pref(right) - pref(left - 1);
    }
};

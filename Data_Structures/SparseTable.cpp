#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class SparseTable
{
private:
    vector<vector<long long>> sparse_table;
    vector<int> log;
    long long neutral = 1e15;

    // Update this function for the desired operation
    long long merge(long long x, long long y)
    {
        return min(x, y);
    }

public:
    SparseTable() {}

    void build(const vector<long long> &a)
    {
        int n = a.size();
        log.resize(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            log[i] = log2(i); // Using log2 directly
        }

        sparse_table.assign(log[n] + 1, vector<long long>(n));
        sparse_table[0] = a;

        for (int i = 1; i <= log[n]; ++i)
        {
            int len = 1 << (i - 1);
            for (int j = 0; j + 2 * len <= n; ++j)
            {
                sparse_table[i][j] = merge(sparse_table[i - 1][j], sparse_table[i - 1][j + len]);
            }
        }
    }

    // General case query, O(log(N))
    long long query(int l, int r)
    {
        int len = r - l + 1;
        long long ans = neutral;

        for (int cnt = 0; len > 0; ++cnt)
        {
            if (len & 1)
            {
                ans = merge(ans, sparse_table[cnt][l]);
                l += 1 << cnt;
            }
            len >>= 1;
        }

        return ans;
    }

    // Fast O(1) query for [min, max, or ,and, gcd, lcm]
    // 0 indexed range, fast O(1) -> but must [(x op x) = x].
    long long query_overlap(int l, int r)
    {
        int len = r - l + 1;
        int row = log[len];

        return merge(sparse_table[row][l], sparse_table[row][r - (1 << row) + 1]);
    }
};

#include <bits/stdc++.h>

using namespace std;
typedef array<int, 3> triple;
const int maxN = 2e5 + 1;

int n, q, a, b, x[maxN], ptr[maxN], fen[maxN], ans[maxN];
triple queries[maxN];
map<int, int> mp;
set<int> S;

void update(int idx, int val)
{
    for (int i = idx; i <= n; i += -i & i)
        fen[i] += val;
}

int query(int idx)
{
    int sum = 0;
    for (int i = idx; i > 0; i -= -i & i)
        sum += fen[i];
    return sum;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x[i]);

    for (int i = n; i > 0; i--)
    {
        if (mp[x[i]])
            ptr[i] = mp[x[i]];
        mp[x[i]] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        if (S.count(x[i]) == 0)
            update(i, 1);
        S.insert(x[i]);
    }

    for (int i = 0; i < q; i++)
    {
        scanf("%d %d", &a, &b);
        queries[i] = {a, b, i};
    }
    sort(queries, queries + q);

    int l = 1;
    for (int q = 0; q < q; q++)
    {
        while (l < queries[q][0])
        {
            if (ptr[l])
                update(ptr[l], 1);
            l++;
        }
        ans[queries[q][2]] = query(queries[q][1]) - query(queries[q][0] - 1);
    }

    for (int q = 0; q < q; q++)
        printf("%d\n", ans[q]);
}
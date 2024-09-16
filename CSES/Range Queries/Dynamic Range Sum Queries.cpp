#include <bits/stdc++.h>
using namespace std;

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

template <class T>

class BIT
{
private:
    int size;
    vector<T> bit;
    vector<T> arr;

public:
    BIT(int size) : size(size), bit(size + 1), arr(size) {}

    /** Sets the value at idx to val. */
    void set(int idx, T val) { add(idx, val - arr[idx]); }

    /** Adds val to the element at idx. */
    void add(int idx, T val)
    {
        arr[idx] += val;
        idx++;
        for (; idx <= size; idx += idx & -idx)
        {
            bit[idx] += val;
        }
    }

    /** @return The sum of all values in [0, idx]. */
    T pref_sum(int idx)
    {
        idx++;
        T total = 0;
        for (; idx > 0; idx -= idx & -idx)
        {
            total += bit[idx];
        }
        return total;
    }
};

int main()
{
    int n;
    int q;
    cin >> n >> q;

    BIT<ll> arr(n);
    for (int i = 0; i < n; i++)
    {
        int n;
        cin >> n;
        arr.set(i, n);
    }

    while (q--)
    {
        int type, arg1, arg2;
        cin >> type >> arg1 >> arg2;
        if (type == 1)
        {
            arr.set(arg1 - 1, arg2);
        }
        else if (type == 2)
        {
            cout << arr.pref_sum(arg2 - 1) - arr.pref_sum(arg1 - 2) << endl;
        }
    }
}
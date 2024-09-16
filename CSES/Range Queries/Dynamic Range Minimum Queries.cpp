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

/**
 * Short for "binary indexed tree",
 * this data structure supports point update and range sum
 * queries like a segment tree.
 */
template <class T>
class BIT
{
private:
    int size;
    vector<T> bit;
    vector<T> arr;

public:
    BIT(int size) : size(size), bit(size + 1), arr(size) {}

    /** Sets the value at index idx to val. */
    void set(int idx, T val) { add(idx, val - arr[idx]); }

    /** Adds val to the element at index idx. */
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
    int arr_len;
    int query_num;
    std::cin >> arr_len >> query_num;

    BIT<long long> bit(arr_len);
    for (int i = 0; i < arr_len; i++)
    {
        int n;
        std::cin >> n;
        bit.set(i, n);
    }

    for (int q = 0; q < query_num; q++)
    {
        int type, arg1, arg2;
        std::cin >> type >> arg1 >> arg2;
        if (type == 1)
        {
            bit.set(arg1 - 1, arg2);
        }
        else if (type == 2)
        {
            cout << bit.pref_sum(arg2 - 1) - bit.pref_sum(arg1 - 2) << '\n';
        }
    }
}
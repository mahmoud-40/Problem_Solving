#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define input_txt                     \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define PQ priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define S second
#define F first
#define MP make_pair
#define endl "\n"
#define PI 3.14159265
#define mod 1000000007
#define tests   \
    ll t;       \
    cin >> t;   \
    ll i_t = 0; \
    while (i_t++ < t)

#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, x) cout << fixed << setprecision(n) << x
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define forp(i, a, b) for (ll i = a; i < b; i++)
#define forn(i, a, b) for (ll i = a; i > b; i--)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define spc << " "
#define sp << " " <<
#define trav(i, a) for (auto &i : a)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define si(a) ((int)(a).size())
#define ins insert
#define pb push_back
#define mp make_pair
#define si(a) ((int)(a).size())
#define gcd(a, b) __gcd(a, b)
#define mem(b, z) memset(b, z, sizeof(b))
#define rn return

using namespace std;
#define int long long

class Node
{
public:
    int v = 0; // We can use more variables depending on what all info we need !
    // 1. this is identitiyElement - default node value which will not impact answer on taken
    Node() {}
    Node(int val)
    {
        v = val; // 2. Node constructor will change depending on, what we need to initialize
    }

    void merge(const Node &l, const Node &r)
    {                  // v is each nodes data, while l & r are children
        v = l.v + r.v; // 3. Merge function (merge logic can change)
    }
};

class Update
{
public:
    int v = 0;
    // 4. this is identity Transformation - default update value assigned before or after the operation
    Update(){};
    Update(int val)
    {
        v = val; // 5. Update constructor initialization
    }

    void combine(const Update &otherUpdate, const int &tl, const int &tr)
    {                       // combing the update, to give to chidren in future
        v += otherUpdate.v; // 6. OtherUpdate is the newest update ['=' or '+=' depends on 'assign/set' vs 'add']
    }

    void apply(Node &node, const int &tl, const int &tr) const
    {
        node.v += (tr - tl + 1) * v; // 7. applying the update received on the node
    }
};

template <typename node, typename update>
class SegTree
{
public:
    int tree_size;
    // t is the segment Tree
    vector<node> seg_data;
    vector<update> unpropUpd; // the actual val of un-propogated updates to be processed
    vector<bool> isLazy;      // tells if a certain node is storing un-propogated updates or not
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

    // asking v, to remember that he has 'val' update for his range
    void apply(const int &v, const int &tl, const int &tr, const update &upd)
    { // [tl, tr] is node range
        if (tl != tr)
        { // leaf nodes can't be lazy, as they have no-one to propogate to
            isLazy[v] = true;
            unpropUpd[v].combine(upd, tl, tr); // stacking up the unpropogaed value, which i'll propogate down
        }
        upd.apply(seg_data[v], tl, tr); // this "= shows assign update", "+= shows range add update"
    }

    // assigning the value whatsoever we had on 'v' to its children ('2*v' & '2*v+1')
    void pushDown(const int &v, const int &tl, const int &tr)
    {
        if (!isLazy[v])
            return;        // if not lazy then no push-down required
        isLazy[v] = false; // no more lazy
        int tm = (tl + tr) / 2;
        apply(2 * v, tl, tm, unpropUpd[v]);         // propogates to left child
        apply(2 * v + 1, tm + 1, tr, unpropUpd[v]); // propogates to right child
        unpropUpd[v] = identityTransformation;      // identity-transformation -- updated the children(job done)
    }

    // Build Segment Tree -- init(a, 1, 0, len-1);
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

    // Query input question is = [l, r] included -- query(1, 0, len-1, l, r)
    node query(const int &v, const int &tl, const int &tr, const int &l, const int &r)
    {
        if (tl > r || tr < l)
            return identityElement; // no overlap
        if (l <= tl && tr <= r)
            return seg_data[v]; // Full overlap

        // Partial Overlap
        pushDown(v, tl, tr); // we remove the lazy tag before going down, so children have correct info
        int tm = (tl + tr) / 2;
        node leftAns = query(2 * v, tl, tm, l, r);
        node rightAns = query(2 * v + 1, tm + 1, tr, l, r);
        node ans;
        ans.merge(leftAns, rightAns);
        return ans;
    }

    // Update at index id of nums to a value val (assign/override/set) -- update(1, 0, len-1, l, r, val)
    void update_range(const int &v, const int &tl, const int &tr, const int &l, const int &r, const update &upd)
    {
        // reached leaf node
        if (l <= tl && tr <= r)
        { // full overlap -- apply update and return back
            apply(v, tl, tr, upd);
            return;
        }
        if (tl > r || tr < l)
            return; // no overlap

        // Partial Overlap
        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        update_range(2 * v, tl, tm, l, r, upd);
        update_range(2 * v + 1, tm + 1, tr, l, r, upd);
        seg_data[v].merge(seg_data[2 * v], seg_data[2 * v + 1]);
    }

    // over-ridden functions
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
            l--;
            r--;
            tree.update_range(l, r, u);
        }
        else
        {
            int k;
            cin >> k;
            k--;
            cout << tree.query(k, k).v << endl;
        }
    }
}

signed main()
{
    fast;
    b3dsh();
    return 0;
}

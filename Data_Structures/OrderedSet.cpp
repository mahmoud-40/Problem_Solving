#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
class OrderedSet
{
private:
    typedef tree<T,
                 null_type,
                 less_equal<T>,
                 rb_tree_tag,
                 tree_order_statistics_node_update>
        ordered_set;

    ordered_set s;

public:
    void insert(T x)
    {
        s.insert(x);
    }

    bool exists(T x)
    {
        return (s.upper_bound(x) != s.end() && (*s.upper_bound(x) == x));
    }

    void erase(T x)
    {
        if (exists(x))
        {
            s.erase(s.upper_bound(x));
        }
    }

    int firstIndex(T x)
    {
        if (!exists(x))
        {
            return -1;
        }
        return s.order_of_key(x);
    }

    T valueAt(int idx)
    {
        if (idx < 0 || idx >= (int)s.size())
        {
            throw out_of_range("Index out of range");
        }
        return *s.find_by_order(idx);
    }

    int lastIndex(T x)
    {
        if (!exists(x))
        {
            return -1;
        }
        if (valueAt(s.size() - 1) == x)
        {
            return s.size() - 1;
        }
        return firstIndex(*s.lower_bound(x)) - 1;
    }

    void clear()
    {
        s.clear();
    }

    int size()
    {
        return (int)s.size();
    }

    int count(T x)
    {
        if (!exists(x))
        {
            return 0;
        }
        return lastIndex(x) - firstIndex(x) + 1;
    }

    int countGreater(T x)
    {
        auto it = s.lower_bound(x);
        if (it == s.end())
        {
            return 0;
        }
        return size() - firstIndex(*it);
    }

    int countSmaller(T x)
    {
        auto it = s.upper_bound(x);
        return firstIndex(*it);
    }
};

int main()
{
    OrderedSet<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(5);
    s.insert(7);

    cout << "Count of 5: " << s.count(5) << endl; // Output: 2

    OrderedSet<char> t;
    t.insert('a');
    t.insert('b');
    t.insert('a');
    t.insert('c');

    cout << "Count of 'a': " << t.count('a') << endl; // Output: 2

    return 0;
}

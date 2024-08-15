#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <cstdlib>
using namespace std;

typedef long long ll;

vector<ll> primeFactorization(ll n)
{
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            n /= i;
            factors.push_back(i);
        }
    }
    if (n > 1)
    {
        factors.push_back(n);
    }
    return factors;
}

bool isPrime(ll x)
{
    if (x <= 1)
        return false;
    if (x == 2)
        return true;
    if (x % 2 == 0)
        return false;

    for (ll i = 3; i * i <= x; i += 2)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

ll numOfPairs(ll n)
{
    return (n * (n - 1)) / 2;
}

ll gcd(ll a, ll b)
{
    while (b != 0)
    {
        ll temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

// Find the smallest positive number divisible by all numbers from 1 to n
void smallestDivisible()
{
    ll n;
    cin >> n;
    ll lcmResult = 1;
    for (int i = 1; i <= n; ++i)
    {
        lcmResult = lcm(i, lcmResult);
    }
    cout << lcmResult << endl;

    ll g = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        g = gcd(g, i);
    }
    cout << g << endl;
}

ll numberOfDivisors(ll n)
{
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    ll num = 1, ans = 1;

    for (int it : primes)
    {
        int count = 0;
        while (n % it == 0)
        {
            n /= it;
            count++;
        }
        ans *= (count + 1);
        num *= it;
    }

    int allDivisorsCount = 0;
    for (int i = 1; i < num; i++)
    {
        bool can = true;
        for (int it : primes)
        {
            if (i % it == 0)
            {
                can = false;
                break;
            }
        }
        if (can)
        {
            ll o = i;
            for (; o * o < n; o += num)
            {
                if (n % o == 0)
                {
                    allDivisorsCount += 2;
                }
            }
            if (o * o == n)
            {
                allDivisorsCount++;
            }
        }
    }
    return ans * allDivisorsCount;
}

void compress(vector<ll> &a, int start)
{
    int n = a.size();
    vector<pair<ll, ll>> pairs(n);
    for (int i = 0; i < n; i++)
    {
        pairs[i] = {a[i], i};
    }
    sort(pairs.begin(), pairs.end());

    int next = start;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && pairs[i - 1].first != pairs[i].first)
        {
            next++;
        }
        a[pairs[i].second] = next;
    }
}

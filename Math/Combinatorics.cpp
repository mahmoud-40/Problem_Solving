#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 100001;

typedef long long ll;

class Combinatorics
{
private:
    ll factorial[MAX];

    ll modex(ll a, ll b)
    {
        if (b == 0)
            return 1;
        ll x = modex(a, b / 2) % MOD;
        x = (x * x) % MOD;
        if (b % 2)
            x = (x * a) % MOD;
        return x;
    }

    ll modinv(ll b)
    {
        return modex(b, MOD - 2);
    }

public:
    Combinatorics()
    {
        gen();
    }

    void gen()
    {
        factorial[0] = factorial[1] = 1LL;
        for (ll i = 2; i < MAX; i++)
        {
            factorial[i] = (i * factorial[i - 1]) % MOD;
        }
    }

    ll nCr(ll n, ll r)
    {
        if (r > n)
            return 0;
        ll numerator = factorial[n];
        ll denominator = (modinv(factorial[r]) * modinv(factorial[n - r])) % MOD;
        return (numerator * denominator) % MOD;
    }

    ll nPr(ll n, ll r)
    {
        if (r > n)
            return 0;
        return (factorial[n] * modinv(factorial[n - r])) % MOD;
    }
};

int main()
{
    Combinatorics comb;

    ll n = 5, r = 2;
    cout << "nCr(" << n << ", " << r << ") = " << comb.nCr(n, r) << endl; // Output: 10
    cout << "nPr(" << n << ", " << r << ") = " << comb.nPr(n, r) << endl; // Output: 20

    return 0;
}

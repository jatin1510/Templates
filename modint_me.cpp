#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

// typedefs
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef long long ll;

// debug section
void debug()
{
    cerr << endl;
}
template <typename T1, typename... T2>
void debug(T1 var1, T2... var2)
{
    cerr << var1 << ' ';
    debug(var2...);
}

// print section
void print()
{
    cout << endl;
}
template <typename T1, typename... T2>
void print(T1 var1, T2... var2)
{
    cout << var1 << ' ';
    print(var2...);
}

// vector operator overload - input
template <typename T>
istream &operator>>(istream &os, vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
        os >> v[i];
    return os;
}

// vector - output
template <typename T_vector>
void printv(const T_vector &v)
{
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

int positive_modulo(int i, int n)
{
    return (n + (i % n)) % n;
}

// defines
#define Code ios_base::sync_with_stdio(NULL);
#define By cin.tie(NULL);
#define Jatin cout.tie(NULL)
#define mod (int)(1e9 + 7)
#define PI (4 * atan(1))
#define int ll
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

template <int MOD = mod>
struct mint
{
    int value;
    static const int MOD_value = MOD;

    mint(long long v = 0)
    {
        value = v % MOD;
        if (value < 0)
            value += MOD;
    }
    mint(long long a, long long b) : value(0)
    {
        *this += a;
        *this /= b;
    }

    mint &operator+=(mint const &b)
    {
        value += b.value;
        if (value >= MOD)
            value -= MOD;
        return *this;
    }
    mint &operator-=(mint const &b)
    {
        value -= b.value;
        if (value < 0)
            value += MOD;
        return *this;
    }
    mint &operator*=(mint const &b)
    {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend mint mexp(mint a, long long e)
    {
        mint res = 1;
        while (e)
        {
            if (e & 1)
                res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend mint inverse(mint a) { return mexp(a, MOD - 2); }

    mint &operator/=(mint const &b) { return *this *= inverse(b); }
    friend mint operator+(mint a, mint const b) { return a += b; }
    friend mint operator+(mint const a) { return 0 + a; }
    friend mint operator-(mint a, mint const b) { return a -= b; }
    friend mint operator-(mint const a) { return 0 - a; }
    friend mint operator*(mint a, mint const b) { return a *= b; }
    friend mint operator/(mint a, mint const b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &os, mint const &a) { return os << a.value; }
    friend bool operator==(mint const &a, mint const &b) { return a.value == b.value; }
    friend bool operator!=(mint const &a, mint const &b) { return a.value != b.value; }
};
int32_t main()
{
    return 0;
}
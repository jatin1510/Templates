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
    {
        os >> v[i];
    }
    return os;
}

// vector operator overload - output
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ' ';
    }
    return os;
}

// defines
#define Code ios_base::sync_with_stdio(NULL);
#define By cin.tie(NULL);
#define Jatin cout.tie(NULL)
#define modulo (int)(1e9 + 7)
#define PI (4 * atan(1))
#define int ll
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// User implemented functions
bool isprime(ll n)
{
    if (n == 1)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}
vector<int> Divisors(int n)
{
    vector<int> ans;
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (n / i == i)
                ans.push_back(i);
            else
                ans.push_back(i), ans.push_back(n / i);
        }
    }
    return ans;
}
bool isSquareFree(int n)
{
    vector<int> d = Divisors(n);
    for (auto i : d)
        if (n % (i * i) == 0 && i != 1)
            return false;
    return true;
}
bool primeDivisor(int n)
{
    vector<int> d = Divisors(n);
    int cnt = 0;
    for (auto i : d)
        if (isprime(i))
            cnt++;

    if (cnt % 2 == 0)
        return 1;
    return 0;
}

int mobius(int n)
{
    bool sf = isSquareFree(n);
    bool prime = primeDivisor(n);
    int ans;
    if (prime && sf)
        ans = 1;
    else if (!prime && sf)
        ans = -1;
    else
        ans = 0;
    return ans;
}
int32_t main()
{
    for (int i = 1; i <= 50; i++)
        cout << mobius(i) << ' ';
    cout << endl;
}
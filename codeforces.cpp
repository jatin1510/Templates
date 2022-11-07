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

// User implemented functions
void solve()
{
    // 1st
    // int n;
    // cin >> n;

    // vector<int> v(n);
    // cin >> v;

    // sort(all(v));

    // vector<int> pref(n), suff(n);
    // pref[0] = v[0];
    // for (int i = 1; i < n; i++)
    // {
    //     pref[i] = pref[i - 1] + v[i];
    // }

    // suff[n - 1] = v[n - 1];
    // for (int i = n - 2; i >= 0; i--)
    // {
    //     suff[i] = suff[i + 1] + v[i];
    // }

    // int ans = pref.back();
    // for (int i = 0; i < n - 1; i++)
    //     ans = max(ans, abs(abs(suff[i + 1]) - abs(pref[i])));
    // print(ans);

    // 2nd
}
int32_t main()
{
    Code By Jatin;

#ifdef FILEIO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

#ifdef MULTIPLE
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
#endif

    vector<int> v = {1, 2, 3, 4, 5};
    print(v);
    return 0;
}
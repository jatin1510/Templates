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
template <typename T>
void print(const vector<T> &v)
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
#define allr(v) (v).rbegin(), (v).rend()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// Start
vector<vector<int>> PraiseN(int n)
{
    --n;

    vector<vector<int>> p = {{0, 1}, {1, 1}};
    vector<vector<int>> ans = p;

    auto multiply = [&](vector<vector<int>> &a, vector<vector<int>> &b)
    {
        vector<vector<int>> ans(2, vector<int>(2));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    ans[i][j] += a[i][k] * b[k][j];
        return ans;
    };

    auto power = [&](int b)
    {
        while (b)
        {
            if (b & 1)
                ans = multiply(ans, p);
            p = multiply(p, p);
            b >>= 1;
        }
    };

    power(n);
    return ans;
}
int32_t main()
{
    int n;
    cin >> n;

    vector<vector<int>> p = {{0, 1}, {1, 1}};
    auto pN = PraiseN(n);
    auto f0 = 0, f1 = 1;

    auto fn = f0 * pN[0][0] + f1 * pN[1][0];
    auto fnp1 = f0 * pN[0][1] + f1 * pN[1][1];

    print("fn =", fn, "fnp1 =", fnp1);
}
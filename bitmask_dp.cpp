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

// Start
// int helpTSM(int i, int mask, vector<vector<int>> &cities)
// {
//     // dp baki lagadvani
//     if (i == cities.size())
//         return 0;

//     int ans = INT_MAX, n = cities.size();
//     for (int j = 0; j < n; j++)
//         if ((mask >> j) & 1)
//             ans = min(ans, cities[i][j] + helpTSM(j, mask ^ (1 << j), cities));
//     return ans;
// }
// int TravellingSalesMan(vector<vector<int>> &cities)
// {
//     int n = cities.size();
//     // start from 0 and visit all the cities and return to 0.

//     return helpTSM(0, (1 << n) - 2, cities);
// }

// codechef - https://www.codechef.com/problems/TSHIRTS

// int n;
// // i -> tshirt id, mask -> who left to wear
// int help(int i, int mask, vector<vector<int>> &adj, vector<vector<int>> &dp)
// {
//     if (mask == 0)
//         return 1;

//     if (i == 100)
//         return 0;

//     if (dp[i][mask] != -1)
//         return dp[i][mask];

//     int nottake = help(i + 1, mask, adj, dp), take = 0;
//     for (int j = 0; j < n; j++)
//         if ((mask >> j) & 1 and adj[j][i])
//             take = (take + help(i + 1, mask ^ (1 << j), adj, dp)) % mod;

//     return dp[i][mask] = (nottake + take) % mod;
// }
// void solve()
// {
//     cin >> n;

//     vector<vector<int>> adj(n, vector<int>(100));
//     cin.ignore();

//     for (int i = 0; i < n; i++)
//     {
//         string s;
//         getline(cin, s);

//         stringstream ss(s);
//         int temp;
//         while (ss >> temp)
//             adj[i][temp - 1] = 1;
//     }

//     vector<vector<int>> dp(101, vector<int>((1 << n) + 1));
//     for (int i = 0; i <= 100; i++)
//         dp[i][0] = 1;

//     for (int i = 99; i >= 0; i--)
//     {
//         for (int mask = 0; mask < (1 << n); mask++)
//         {
//             int nottake = dp[i + 1][mask], take = 0;
//             for (int j = 0; j < n; j++)
//                 if ((mask >> j) & 1 and adj[j][i])
//                     take = (take + dp[i + 1][mask ^ (1 << j)]) % mod;
//             dp[i][mask] = (nottake + take) % mod;
//         }
//     }

//     print(dp[0][(1 << n) - 1] % mod);
// }

// CSES - https://cses.fi/problemset/task/2181
int n, m;
void gen_next_mask(int mask, int i, int next_mask, vector<int> &next_masks)
{
    if (i == n)
    {
        next_masks.push_back(next_mask);
        return;
    }

    if (((mask >> i) & 1) != 0)
        gen_next_mask(mask, i + 1, next_mask, next_masks);

    if (i != n - 1)
        if (((mask >> i) & 1) == 0 and ((mask >> (i + 1)) & 1) == 0)
            gen_next_mask(mask, i + 2, next_mask, next_masks);

    if (((mask >> i) & 1) == 0)
        gen_next_mask(mask, i + 1, next_mask | (1 << i), next_masks);
}
int help(int col, int mask, vector<vector<int>> &dp)
{
    if (col == m)
        return mask == 0;

    if (dp[col][mask] != -1)
        return dp[col][mask];

    int ans = 0;
    vector<int> next_masks;
    gen_next_mask(mask, 0, 0, next_masks);
    for (auto next_mask : next_masks)
        ans = (ans + help(col + 1, next_mask, dp)) % mod;

    return dp[col][mask] = ans % mod;
}
void solve()
{
    cin >> n >> m;
    vector<vector<int>> dp(m, vector<int>((1 << n) + 1, -1));
    print(help(0, 0, dp));
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

    solve();
    return 0;
}
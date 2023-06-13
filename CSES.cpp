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
void debug_out() { cout << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    cout << ' ' << H;
    debug_out(T...);
}
#ifndef DEBUG
#define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

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
    for (int i = 0; i < (int)v.size(); ++i)
        os >> v[i];
    return os;
}

// vector - output
template <typename T_vector>
void outvector(const T_vector &v, int start = -1, int end = -1, bool add_one = false)
{
    if (start < 0)
        start = 0;
    if (end < 0)
        end = int(v.size());

    for (int i = start; i < end; i++)
        cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');
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
int n, inf = 1e9;
vector<vector<int>> adj(200005);
vector<int> childs(200005, 1);
vector<int> dist(200005);
vector<int> ans(200005);

void eval_child(int node, int par)
{
    for (auto i : adj[node])
    {
        if (i != par)
        {
            eval_child(i, node);
            childs[node] += childs[i];
        }
    }
}

void eval_dist(int node, int par)
{
    for (auto i : adj[node])
    {
        if (i != par)
        {
            eval_dist(i, node);
            dist[node] += childs[i] + dist[i];
        }
    }
}

void dfs(int node, int par, int par_ans)
{
    ans[node] = dist[node] + (par_ans + (n - childs[node]));
    for (auto i : adj[node])
        if (i != par)
            dfs(i, node, ans[node] - (dist[i] + childs[i]));
}

void solve()
{
    cin >> n;
    int u, v;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    eval_child(1, 0);
    eval_dist(1, 0);
    dfs(1, 0, 0);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
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
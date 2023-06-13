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
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    const int inf = 1e7;

    string decode(int mask)
    {
        string ans;
        while (mask)
        {
            if (mask & 1)
                ans.push_back('1');
            else
                ans.push_back('0');
            mask >>= 1;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

public:
    int dp[13][1 << 13];
    int solve(int node, int mask, int n, vector<vector<int>> &adj)
    {
        if (__builtin_popcount(mask) == n)
            return 0;

        if (dp[node][mask] != -1)
            return dp[node][mask];

        dp[node][mask] = inf;
        for (auto i : adj[node])
            if (((mask >> i) & 1) == 0)
                dp[node][mask] = min(dp[node][mask], 1 + min(solve(i, mask | (1 << i), n, adj), solve(i, mask, n, adj)));
        return dp[node][mask];
    }
    int shortestPathLength(vector<vector<int>> &graph)
    {
        int n = graph.size(), ans = inf;
        for (int i = 0; i < n; i++)
        {
            memset(dp, -1, sizeof(dp));
            ans = min(ans, solve(i, (1 << i), n, graph));
        }
        return ans;
    }
};

int32_t main()
{
    Solution ans;
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    int u, v;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    print(ans.shortestPathLength(graph));

    return 0;
}
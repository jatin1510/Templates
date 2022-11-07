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
vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};
int n, m;

void dfs(int i, int j, vector<vector<int>> &vis, vector<string> &grid)
{
    vis[i][j] = 1;
    auto isvalid = [&](int i, int j) -> bool
    {
        return i >= 0 and i < n and j >= 0 and j < m;
    };
    for (int k = 0; k < 4; k++)
    {
        int x = i + dx[k];
        int y = j + dy[k];

        if (isvalid(x, y) and grid[x][y] != '#' and !vis[x][y])
        {
            dfs(x, y, vis, grid);
        }
    }
}
void solve()
{
    cin >> n >> m;

    vector<string> grid(n);
    cin >> grid;

    vector<vector<int>> vis(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '#')
                vis[i][j] = 1;

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j])
            {
                ans++;
                dfs(i, j, vis, grid);
            }
        }
    }

    print(ans);
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

    // solve();
    srand(time(NULL));
    int x = rand();
    cout << x << '\n';
    cout << x % 6 << '\n';
    cout << x % 6 + 1 << '\n';
    return 0;
}
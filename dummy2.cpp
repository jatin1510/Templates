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

template <class T>
bool ckmin(T &a, const T &b)
{
    return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b)
{
    return a < b ? a = b, 1 : 0;
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
class Graph
{
private:
    // Node -> {{adjecent node, weight}, {adjecent node, weight}, ... }
    map<int, vector<int>> adj;

    // n - node
    // indexing -> (=0) if 1 based indexing and (=1) if 0 based indexing
    // initially it is 1 based indexing
    int n, indexing;

    // weight of the edges
    map<pair<int, int>, int> weight;

public:
    Graph(){};

    Graph(int nodes, int index = 1)
    {
        // nodes assigning
        n = nodes;

        // setting indexing
        if (index == 0)
            indexing = 1;
        else
            indexing = 0;
    };

    void addEdge(int u, int v, int weigh = 1)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        weight[{u, v}] = weigh;
        weight[{v, u}] = weigh;
    };

    void addDirectionalEdge(int u, int v, int weigh = 1)
    {
        adj[u].push_back(v);
        weight[{u, v}] = weigh;
    };

    void printGraph(bool flag = false)
    {
        for (auto i : adj)
        {
            cout << i.first << ": ";
            for (auto j : i.second)
            {
                if (flag)
                    cout << "(";
                cout << j;

                if (flag)
                    cout << ", " << weight[{i.first, j}] << ") ";
                else
                    cout << ' ';
            }
            cout << endl;
        }
    }
};
void solve()
{
}
int32_t main()
{
    Code By Jatin;

#ifdef FILEIO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

#ifndef MULTIPLE
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
#endif

    solve();
    return 0;
}
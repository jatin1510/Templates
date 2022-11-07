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
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// User implemented functions
class seg_tree
{
    // 0 based indexing of tree - means root node is at index 0;
    vector<int> t;
    vector<int> v;
    int n;

private:
    int sum(int i, int tl, int tr, int ql, int qr)
    {
        if (ql <= tl && tr <= qr)
            return t[i];

        if (tr < ql || qr < tl)
            return 0;

        int mid = (tl + tr) / 2;
        return sum(2 * i + 1, tl, mid, ql, qr) + sum(2 * i + 2, mid + 1, tr, ql, qr);
    }

    int build(int i, int l, int r, vector<int> a)
    {
        if (l == r)
        {
            t[i] = a[l];
            return a[l];
        }

        int mid = (l + r) / 2;
        return t[i] = build(2 * i + 1, l, mid, a) + build(2 * i + 2, mid + 1, r, a);
    }

    void updateHelp(int i, int tl, int tr, int idx, int diff)
    {
        if (idx < tl || tr < idx)
            return;

        t[i] += diff;

        if (tl != tr)
        {
            int mid = (tl + tr) / 2;
            updateHelp(2 * i + 1, tl, mid, idx, diff);
            updateHelp(2 * i + 2, mid + 1, tr, idx, diff);
        }
    }

public:
    seg_tree(vector<int> arr)
    {
        n = arr.size();
        v = arr;
        t = vector<int>(4 * n);
        build(0, 0, n - 1, arr);
    }

    int getSum(int l, int r)
    {
        return sum(0, 0, n - 1, l, r);
    }

    void update(int idx, int value)
    {
        updateHelp(0, 0, n - 1, idx, value - v[idx]);
    }
};

int32_t main()
{
    vector<int> v = {1, 2, 5, 6, 7, 9};
    seg_tree s(v);
    cout << s.getSum(0, 2) << endl;
    s.update(2, 6);
    cout << s.getSum(0, 2) << endl;

    return 0;
}
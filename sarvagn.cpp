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
vector<vector<int>> func(int n)
{
    int l = 0, r = n - 1, u = 0, d = n - 1;
    int put = 1, cnt = 0;
    bool flag = false;
    vector<vector<int>> ans(n, vector<int>(n));
    while (1)
    {
        for (int i = l; i <= r; i++)
        {
            ans[u][i] = put++;
            cnt++;
            if (cnt == n * n)
            {
                flag = true;
                break;
            }
        }
        u++;
        if (flag)
            break;

        for (int i = u; i <= d; i++)
        {
            ans[i][r] = put++;
            cnt++;
            if (cnt == n * n)
            {
                flag = true;
                break;
            }
        }
        r--;
        if (flag)
            break;

        for (int i = r; i >= l; i--)
        {
            ans[d][i] = put++;
            cnt++;
            if (cnt == n * n)
            {
                flag = true;
                break;
            }
        }
        d--;
        if (flag)
            break;

        for (int i = d; i >= u; i--)
        {
            ans[i][l] = put++;
            cnt++;
            if (cnt == n * n)
            {
                flag = true;
                break;
            }
        }
        l++;
        if (flag)
            break;
    }
    return ans;
}
int lower(vector<int> A, int B)
{
    int low = 0, high = A.size() - 1, mid, ans = -1;
    while (low <= high)
    {
        mid = (low + high) >> 1;
        if (A[mid] == B)
        {
            ans = mid;
            high = mid - 1;
        }
        else if (A[mid] > B)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return ans;
}
int upper(vector<int> A, int B)
{
    int low = 0, high = A.size(), mid, ans = -1;
    while (low <= high)
    {
        mid = (low + high) >> 1;
        if (A[mid] > B)
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return (ans == -1 ? A.size() : ans);
}
int findCount(const vector<int> &A, int B)
{
    int l = lower(A, B);
    int u = upper(A, B);
    if (l == -1)
        return 0;
    return u - l;
}
int32_t main()
{
    // vector<int> v = {5, 7, 7, 8, 8, 10};
    vector<int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int b = 10;
    cout << findCount(v, b) << endl;
    return 0;
}
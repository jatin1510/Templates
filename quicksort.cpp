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
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// User implemented functions
int part(int l, int r, vector<int> &nums)
{
    int pivot = nums[l];
    int i = l, j = r;
    while (i < j)
    {
        do
        {
            i++;
        } while (nums[i] <= pivot);
        do
        {
            j--;
        } while (nums[j] > pivot);
        if (i < j)
            swap(nums[i], nums[j]);
    }
    swap(nums[l], nums[j]);
    return j;
}

void quickSort(int l, int r, vector<int> &nums)
{
    if (l < r)
    {
        int pos = part(l, r, nums);
        // cout << "while l = " << l << " and r = " << r << '\n';
        // print(nums);
        quickSort(l, pos, nums);
        quickSort(pos + 1, r, nums);
    }
}
void SORT(vector<int> &nums)
{
    nums.push_back(INT_MAX);
    quickSort(0, nums.size() - 1, nums);
    nums.pop_back();
}
int32_t main()
{
    vector<int> nums = {10, 16, 8, 12, 15, 6, 3, 9, 5};
    SORT(nums);
    print(nums);
    return 0;
}
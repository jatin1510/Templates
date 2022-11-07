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

// defines
#define Code ios_base::sync_with_stdio(NULL);
#define By cin.tie(NULL);
#define Jatin cout.tie(NULL)
#define modulo (int)(1e9 + 7)
#define PI (4 * atan(1))
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

class MinHeap
{
    int maxSize = 1e5;
    int n;
    vector<int> arr;

    /* 0-based indexing */
    // Total leaves = (n/2 + 1) {range: 0 to n/2 - 1}
    // Internal Nodes = (Total nodes - leaves) {range: n/2 to n-1}
    // if parent is at index "i" then left child will be at 2*i+1 and right child will be at 2*i+2
    // if child is at index "i" then parent will be at ceil(i/2)-1

public:
    MinHeap()
    {
        this->arr = vector<int>(maxSize);
        this->n = 0;
    }

    MinHeap(int nodes)
    {
        this->arr = vector<int>(maxSize);
        this->n = nodes;
    }

    MinHeap(vector<int> v)
    {
        // copying data
        this->arr = vector<int>(maxSize);
        this->n = v.size();

        for (int i = 0; i < n; i++)
            this->arr[i] = v[i];

        build_heap();
    }

    ~MinHeap()
    {
        arr.erase(arr.begin(), arr.end());
    }

    void printHeap()
    {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " \n"[i == n - 1];
    }

    int parent(int i)
    {
        return ceil(i / 2.0) - 1;
    }

    int size()
    {
        return n;
    }
    // O(logn)
    void percolate_down(int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        int smallest = i;

        if (l < n && arr[l] < arr[i])
            smallest = l;

        if (r < n && arr[r] < arr[smallest])
            smallest = r;

        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            percolate_down(smallest);
        }
    }

    // O(logn)
    void percolate_up(int i)
    {
        while (i > 0 && arr[parent(i)] > arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // O(n)
    void build_heap()
    {
        for (int i = n / 2 - 1; i >= 0; i--)
            percolate_down(i);
    }

    // give min element of the heap and delete it
    // O(logn)
    int extract_min()
    {
        if (n < 1)
        {
            cout << "heap underflow\n";
            return -1;
        }

        int mn = arr[0];
        swap(arr[0], arr[n - 1]);
        this->n--;
        percolate_down(0);
        return mn;
    }

    // give minimum element of the heap
    // O(1)
    int min()
    {
        return arr[0];
    }

    // give maximum element of the heap
    // O(n)
    int max()
    {
        return *max_element(arr.begin(), arr.end() + n);
    }

    // index of node, key to be changed
    void increase_key(int i, int key)
    {
        if (key < arr[i])
        {
            cout << "Please increase key !!!\n";
            return;
        }

        arr[i] = key;
        percolate_down(i);
    }

    // index of node, key to be changed
    void decrease_key(int i, int key)
    {
        if (key > arr[i])
        {
            cout << "Please decrease key !!!\n";
            return;
        }

        arr[i] = key;
        percolate_up(i);
    }

    // insert element in heap and maintain heap properties
    // O(logn)
    void insert(int key)
    {
        n++;
        arr[n - 1] = key;
        percolate_up(n - 1);
    }

    // gives vector form of current heap
    vector<int> givevector()
    {
        vector<int> ans;
        for (int i = 0; i < n; i++)
            ans.push_back(arr[i]);

        return ans;
    }
};

void heapsort(vector<int> &v, bool flag = 0)
{
    // flag == 0 : sort ascending
    // flag == 1 : sort descending
    MinHeap heap(v);
    if (!flag)
        for (int i = 0; i < v.size(); i++)
            v[i] = heap.extract_min();
    else
        for (int i = v.size() - 1; i >= 0; i--)
            v[i] = heap.extract_min();
}

int32_t main()
{
    vector<int> v = {20, 900, 6, 1, 5, 0, 2, 3};
    return 0;
}
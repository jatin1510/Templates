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

struct Node
{
    Node *links[2];

    // checks if the reference trie is present or not
    bool containsKey(int bit)
    {
        return (links[bit] != NULL);
    }

    // creating reference trie
    void put(int bit, Node *node)
    {
        links[bit] = node;
    }

    // to get the next node for traversal
    Node *get(int bit)
    {
        return links[bit];
    }
};

class Trie
{
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    void insert(int num)
    {
        Node *node = root;
        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit))
                node->put(bit, new Node());

            node = node->get(bit);
        }
    }

    int findMaxXorVia(int num)
    {
        Node *node = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;
            if (node->containsKey(!bit))
            {
                maxNum = maxNum | (1 << i);
                node = node->get(!bit);
            }
            else
            {
                node = node->get(bit);
            }
        }
        return maxNum;
    }
};

int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2)
{
    Trie *t = new Trie();
    for (auto i : arr1)
        t->insert(i);

    int ans = 0;
    for (auto i : arr2)
        ans = max(ans, t->findMaxXorVia(i));

    return ans;
}

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries)
{
    //	Write your coode here.
    int q = queries.size();
    for (int i = 0; i < q; i++)
        queries[i].push_back(i);

    sort(queries.begin(), queries.end(), [&](vector<int> &a, vector<int> &b) -> bool
         { return a[1] < b[1]; });

    sort(arr.begin(), arr.end());
    Trie *t = new Trie();
    vector<int> ans(q);

    int itr = 0;
    for (int i = 0; i < q; i++)
    {
        int x = queries[i][0];
        int less = queries[i][1];
        int index = queries[i][2];
        
        while (itr < arr.size() && arr[itr] <= less)
            t->insert(arr[itr++]);

        if (itr == 0)
            ans[index] = -1;
        else
            ans[index] = t->findMaxXorVia(x);
    }
    return ans;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;

        vector<int> v(n);
        cin >> v;

        vector<vector<int>> qr;
        for (int i = 0; i < q; i++)
        {
            int x, a;
            cin >> x >> a;
            qr.push_back({x, a});
        }
        cout << maxXorQueries(v, qr) << endl;
    }

    return 0;
}
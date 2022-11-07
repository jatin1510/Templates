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
struct Node
{
    Node *links[26];
    bool flag = false;
    int cntEndWith = 0;
    int cntPrefix = 0;

    // checks if the reference trie is present or not
    bool containsKey(char ch)
    {
        return (links[ch - 'a'] != NULL);
    }

    // creating reference trie
    void put(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }

    // to get the next node for traversal
    Node *get(char ch)
    {
        return links[ch - 'a'];
    }

    // setting flag to true at the end of the word
    void setEnd()
    {
        flag = true;
    }

    // checking if the word is completed or not
    bool isEnd()
    {
        return flag;
    }

    // increasing end of the given node
    void increaseEnd()
    {
        cntEndWith++;
    }

    // increasing prefix of the given node
    void increasePrefix()
    {
        cntPrefix++;
    }

    // decreasing end of the given node
    void deleteEnd()
    {
        cntEndWith--;
    }

    // decreasing prefix of the given node
    void reducePrefix()
    {
        cntPrefix--;
    }

    int getEnd()
    {
        return cntEndWith;
    }

    int getPrefix()
    {
        return cntPrefix;
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

    void insert(string word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                node->put(i, new Node());

            node = node->get(i);
            node->increasePrefix();
        }
        node->setEnd();
        node->increaseEnd();
    }
    
    int startsWith(string prefix)
    {
        Node *node = root;
        for (auto i : prefix)
        {
            if (!node->containsKey(i))
                return 0;
            node = node->get(i);
        }
        return node->cntPrefix;
    }
};
vector<long long> findScore(int n, int k, vector<string> s)
{
    Trie *t = new Trie();
    for (auto i : s)
        t->insert(i);

    map<string, int> mp;
    vector<long long> ans(n);
    for (int i = 0; i < n; i++)
    {
        long long subans = 0;
        string cur = s[i];
        string make;
        for (auto j : cur)
        {
            make.push_back(j);
            if (!mp[make])
                subans += mp[make] = t->startsWith(make);
            else
                subans += mp[make];
        }
        ans[i] = subans;
    }
    return ans;
}
int32_t main()
{
    int n, k;
    cin >> n >> k;

    vector<string> v(n);
    for (auto &i : v)
        cin >> i;

    cout << findScore(n, k, v) << endl;
    return 0;
}
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

    bool search(string word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                return false;
            node = node->get(i);
        }
        return node->isEnd();
    }

    bool startsWith(string prefix)
    {
        Node *node = root;
        for (auto i : prefix)
        {
            if (!node->containsKey(i))
                return false;
            node = node->get(i);
        }
        return true;
    }

    int countWordsEqualTo(string &word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                return 0;
            node = node->get(i);
        }
        return node->getEnd();
    }

    int countWordsStartingWith(string &word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                return 0;
            node = node->get(i);
        }
        return node->getPrefix();
    }

    void erase(string &word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                return;
            node = node->get(i);
            node->reducePrefix();
        }
        node->deleteEnd();
    }

    bool checkIfAllPrefixExists(string word)
    {
        Node *node = root;
        for (auto i : word)
        {
            if (!node->containsKey(i))
                return false;

            node = node->get(i);
            if (!node->isEnd())
                return false;
        }
        return true;
    }

    int getDistinct(string s, int index)
    {
        Node *node = root;
        int ans = 0;
        for (int i = index; i < s.size(); i++)
        {
            if (!node->containsKey(s[i]))
                node->put(s[i], new Node()), ans++;
            node = node->get(s[i]);
        }
        return ans;
    }
};

string completeString(int n, vector<string> &a)
{
    // Write your code here.
    Trie *t = new Trie();
    for (auto i : a)
        t->insert(i);

    string longest = "";
    for (auto word : a)
    {
        if (t->checkIfAllPrefixExists(word))
        {
            if (word.size() > longest.size())
                longest = word;
            else if (word.size() == longest.size() && word < longest)
                longest = word;
        }
    }
    if (longest == "")
        return "None";
    return longest;
}

int countDistinctSubstrings(string &s)
{
    Trie *t = new Trie();

    int n = s.size(), ans = 0;
    for (int i = 0; i < n; i++)
        ans += t->getDistinct(s, i);
    return ans + 1;
}

int main()
{
    string s = "ababa";
    cout << countDistinctSubstrings(s) << endl;
    return 0;
}
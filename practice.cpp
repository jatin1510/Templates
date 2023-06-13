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
template <typename T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

int dfs(BinaryTreeNode<int> *root)
{
    if (!root)
        return 0;

    if (!root->left and !root->right)
        return root->data;

    int l = (root->left ? root->left->data : 0);
    int r = (root->right ? root->right->data : 0);

    if (root->data > l + r)
    {
        if (root->left)
            root->left->data = root->data;

        if (root->right)
            root->right->data = root->data;
    }

    int left = dfs(root->left);
    int right = dfs(root->right);

    root->data = left + right;
    return root->data;
}
void changeTree(BinaryTreeNode<int> *root)
{
    if (!root)
        return;
    dfs(root);
}

void inorder(BinaryTreeNode<int> *root)
{
    if (!root)
        return;

    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}
struct Node
{
    int data;
    Node *next;
    Node(int data) : data(data) {}
};

Node *givelist(vector<int> v)
{
    int n = v.size();
    if (!n)
        return NULL;
    int i = 0;
    Node *head = new Node(v[i]);
    Node *ptr = head;
    while (++i < n)
    {
        Node *node = new Node(v[i]);
        ptr->next = node;
        ptr = node;
    }
    return head;
}
vector<int> givevector(Node *head)
{
    vector<int> ans;
    Node *ptr = head;
    while (ptr->next != NULL)
    {
        ans.push_back(ptr->data);
        ptr = ptr->next;
    }
    ans.push_back(ptr->data);
    return ans;
}
void printLL(Node *A)
{
    if (A == NULL)
    {
        cout << "List is empty\n";
        return;
    }
    Node *ptr = A;
    while (ptr->next != NULL)
    {
        cout << ptr->data << ' ';
        ptr = ptr->next;
    }
    cout << ptr->data << endl;
}

Node *addOne(Node *head)
{
    // Your Code here
    // return head of list after adding one
    // reverse LL
    if (!head)
        return NULL;

    Node *temp = NULL;
    Node *curr = NULL;

    while (head)
    {
        curr = head->next;
        head->next = temp;
        temp = head;
        head = curr;
    }
    head = temp;

    int carry = 1;
    temp = head;
    Node *prev = NULL;
    while (temp != NULL)
    {
        int sum = temp->data + carry;
        temp->data = sum % 10;
        carry = sum / 10;
        prev = temp;
        temp = temp->next;
    }
    if (carry == 1)
    {
        Node *n = new Node(1);
        prev->next = n;
    }

    // reverse LL
    temp = NULL;
    curr = NULL;

    while (head != NULL)
    {
        curr = head->next;
        head->next = temp;
        temp = head;
        head = curr;
    }
    return head = prev;
}

int32_t main()
{
    vector<int> v = {9, 9};
    printLL(addOne(givelist(v)));
    return 0;
}

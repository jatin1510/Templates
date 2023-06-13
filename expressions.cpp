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
        os >> v[i];
    return os;
}

// vector - output
template <typename T_vector>
void printv(const T_vector &v)
{
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
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

struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(char x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inorder(TreeNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->val;
    inorder(root->right);
}

void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val;
}

// User implemented functions
class expression
{
private:
    string s;

public:
    expression(string t)
    {
        s = t;
    }

    string infix()
    {
        return s;
    }

    bool isOperator(char ch)
    {
        return ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '^';
    }

    int precedence(char ch)
    {
        if (ch == '^')
            return 3;

        if (ch == '*' or ch == '/')
            return 2;

        if (ch == '+' or ch == '-')
            return 1;

        return 0;
    }
    
    string postfix()
    {
        string ans;
        stack<char> st;
        for (auto i : s)
        {
            if (i == '(')
                st.push(i);
            else if (i == ')')
            {
                while (!st.empty() and st.top() != '(')
                {
                    ans.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else if (isOperator(i))
            {
                if (st.empty())
                    st.push(i);
                else if (precedence(i) > precedence(st.top()))
                    st.push(i);
                else if (precedence(i) <= precedence(st.top()))
                {
                    while (!st.empty() and i != '^' and precedence(i) <= precedence(st.top()))
                    {
                        ans.push_back(st.top());
                        st.pop();
                    }
                    st.push(i);
                }
            }
            else
                ans.push_back(i);
        }
        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }
        return ans;
    }

    string prefixusingReverse()
    {
        // Not efficient
        string t = s;
        reverse(s.begin(), s.end());
        for (auto &i : s)
        {
            if (i == '(')
                i = ')';
            else if (i == ')')
                i = '(';
        }
        string ans = postfix();
        s = t;
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string prefix()
    {
        string t = s;
        reverse(t.begin(), t.end());

        string ans;
        stack<char> st;
        for (auto i : t)
        {
            if (i == ')')
                st.push(i);
            else if (i == '(')
            {
                while (!st.empty() and st.top() != ')')
                {
                    ans.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else if (isOperator(i))
            {
                if (st.empty())
                    st.push(i);
                else if (precedence(i) > precedence(st.top()))
                    st.push(i);
                else if (i != '^' and precedence(i) == precedence(st.top()))
                    st.push(i);
                else if (precedence(i) < precedence(st.top()))
                {
                    while (!st.empty() and precedence(i) < precedence(st.top()))
                    {
                        ans.push_back(st.top());
                        st.pop();
                    }
                    st.push(i);
                }
            }
            else
                ans.push_back(i);
        }
        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    int evaluate()
    {
        // WARNING: We can only use digits {0,1,...,9} as A,B,...,Z in infix expression
        string t = postfix();
        stack<long> st;
        for (auto i : t)
        {
            if (i == '+' or i == '-' or i == '*' or i == '/' or i == '^')
            {
                long b = st.top();
                st.pop();
                long a = st.top();
                st.pop();

                if (i == '+')
                    st.push(a + b);
                else if (i == '-')
                    st.push(a - b);
                else if (i == '*')
                    st.push(a * b);
                else if (i == '/')
                    st.push(a / b);
                else
                    st.push(pow(a, b));
            }
            else
                st.push(stoll(to_string(i - '0')));
        }
        return st.top();
    }

    string postfixtoinfix()
    {
        // works only for characters
        string t = postfix();
        stack<string> st;

        for (auto i : t)
        {
            if (i == '+' or i == '-' or i == '*' or i == '/' or i == '^')
            {
                string b = st.top();
                st.pop();
                string a = st.top();
                st.pop();

                if (i == '+')
                    st.push("(" + a + "+" + b + ")");
                else if (i == '-')
                    st.push("(" + a + "-" + b + ")");
                else if (i == '*')
                    st.push("(" + a + "*" + b + ")");
                else if (i == '/')
                    st.push("(" + a + "/" + b + ")");
                else
                    st.push("(" + a + "^" + b + ")");
            }
            else
            {
                string t;
                t.push_back(i);
                st.push(t);
            }
        }
        return st.top();
    }
    string prefixtoinfix()
    {
        // works only for characters
        string t = prefix();
        stack<string> st;

        // first change is here
        reverse(t.begin(), t.end());
        for (auto i : t)
        {
            if (i == '+' or i == '-' or i == '*' or i == '/' or i == '^')
            {
                // Second change is here
                string a = st.top();
                st.pop();
                string b = st.top();
                st.pop();

                if (i == '+')
                    st.push("(" + a + "+" + b + ")");
                else if (i == '-')
                    st.push("(" + a + "-" + b + ")");
                else if (i == '*')
                    st.push("(" + a + "*" + b + ")");
                else if (i == '/')
                    st.push("(" + a + "/" + b + ")");
                else
                    st.push("(" + a + "^" + b + ")");
            }
            else
            {
                string t;
                t.push_back(i);
                st.push(t);
            }
        }
        return st.top();
    }

    TreeNode *expressionTree()
    {
        string t = postfix();

        stack<TreeNode *> st;

        for (auto i : t)
        {
            if (i == '+' or i == '-' or i == '*' or i == '/' or i == '^')
            {
                TreeNode *b = st.top();
                st.pop();
                TreeNode *a = st.top();
                st.pop();

                TreeNode *node = new TreeNode(i);
                node->left = a;
                node->right = b;

                st.push(node);
            }
            else
            {
                st.push(new TreeNode(i));
            }
        }
        return st.top();
    }
};
int32_t main()
{
    string s = "K+L-M*N+(O^P)*W/U/V*T+Q";
    // string s = "2+3*4-8/2^3";
    // string s = "2+(3*1)-9";
    // string s = "(5+3)*(6/2)+(3*5)";
    // string s = "a+b*e/f+d-e^t";
    // string s = "(a+b)*(e/f)";
    // string s = "a*b/c+e/f*g+k-x*y";

    expression e(s);
    // print(e.prefixtoinfix());
    // print(e.evaluate());
    // print("postfix :", e.postfix());
    // print("prefix1 :", e.prefixusingReverse());
    // print("prefix2 :", e.prefix());
    // print("Innnfix :", e.infix());

    // TreeNode *root = e.expressionTree();
    // print(e.infix());
    // inorder(root);
    // cout << endl;
    // cout << endl;

    // print(e.postfix());
    // postorder(root);
    // cout << endl;
    // cout << endl;

    // print(e.prefix());
    // preorder(root);
    // cout << endl;
    // cout << endl;

    print(e.prefix());
    return 0;
}

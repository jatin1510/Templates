#include <bits/stdc++.h>
using namespace std;

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

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int val)
    {
        data = val;
        left = right = NULL;
    }
};

void inorder(TreeNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << ' ';
}

vector<int> levelorder(TreeNode *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    queue<TreeNode *> q;
    q.push(root);
    vector<vector<int>> v;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> temp;
        for (int i = 0; i < size; i++)
        {
            TreeNode *ptr = q.front();
            q.pop();
            if (ptr->left != NULL)
                q.push(ptr->left);
            if (ptr->right != NULL)
                q.push(ptr->right);
            temp.push_back(ptr->data);
            ans.push_back(ptr->data);
        }
        v.push_back(temp);
    }
    // in case we need all levels then return 2d vector v {also change return type😂}
    return ans;
}

vector<int> inorderIterative(TreeNode *root)
{
    if (root == NULL)
        return {};

    stack<TreeNode *> st;
    vector<int> ans;
    while (1)
    {
        if (root != NULL)
        {
            st.push(root);
            root = root->left;
        }
        else
        {
            if (st.empty())
                break;
            root = st.top();
            st.pop();
            ans.push_back(root->data);
            root = root->right;
        }
    }
    return ans;
}
vector<int> preorderIterative(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> ans;
    stack<TreeNode *> st;
    st.push(root);
    while (!st.empty())
    {
        root = st.top();
        st.pop();
        ans.push_back(root->data);
        if (root->right != NULL)
            st.push(root->right);
        if (root->left != NULL)
            st.push(root->left);
    }
    return ans;
}
vector<int> postorderIterative(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> ans;
    stack<TreeNode *> st1, st2;
    st1.push(root);
    while (!st1.empty())
    {
        root = st1.top();
        st1.pop();
        st2.push(root);
        if (root->left != NULL)
            st1.push(root->left);
        if (root->right != NULL)
            st1.push(root->right);
    }
    while (!st2.empty())
    {
        ans.push_back(st2.top()->data);
        st2.pop();
    }
    return ans;
}
vector<int> postorderIterativeUsingOneStack(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> ans;
    TreeNode *curr = root, *temp;
    stack<TreeNode *> st;
    while (curr != NULL || !st.empty())
    {
        if (curr != NULL)
        {
            st.push(curr);
            curr = curr->left;
        }
        else
        {
            temp = st.top()->right;
            if (temp == NULL)
            {
                temp = st.top();
                st.pop();
                ans.push_back(temp->data);
                while (!st.empty() && temp == st.top()->right)
                {
                    temp = st.top();
                    st.pop();
                    ans.push_back(temp->data);
                }
            }
            else
                curr = temp;
        }
    }
    return ans;
}
vector<vector<int>> alltraversels(TreeNode *root)
{
    if (root == NULL)
        return {};

    vector<int> InOrder, PreOrder, PostOrder;
    stack<pair<TreeNode *, int>> st;
    st.push({root, 1});
    while (!st.empty())
    {
        if (st.top().second == 1)
        {
            PreOrder.push_back(st.top().first->data);
            st.top().second++;
            if (st.top().first->left != NULL)
                st.push({st.top().first->left, 1});
        }
        else if (st.top().second == 2)
        {
            InOrder.push_back(st.top().first->data);
            st.top().second++;
            if (st.top().first->right != NULL)
                st.push({st.top().first->right, 1});
        }
        else
        {
            PostOrder.push_back(st.top().first->data);
            st.pop();
        }
    }
    return {PreOrder, InOrder, PostOrder};
}
int validBST(vector<int> &A)
{
    stack<int> st;
    int root = INT_MIN;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] < root)
            return 0;
        while (st.size() && st.top() < A[i])
        {
            root = st.top();
            st.pop();
        }
        st.push(A[i]);
    }
    return 1;
}
// through recursion
int maxDepth(TreeNode *root) // maxDepth of tree == Height of root node
{
    if (root == NULL)
        return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// through level order traversel
int height(TreeNode *root)
{
    int depth = 0;
    queue<TreeNode *> q;

    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        TreeNode *temp = q.front();
        q.pop();
        if (temp == NULL)
            depth++;

        if (temp != NULL)
        {
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        else if (!q.empty())
            q.push(NULL);
    }
    return depth;
}

// check whether the given tree is balanced binary tree or not
// as like as maxDepth. additional thing = check at every node whether the absolute
// differance is >1 or not, Take decision based on it
int isBalancedBinaryTree(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int lh = isBalancedBinaryTree(root->left);
    if (lh == -1)
        return -1;
    int rh = isBalancedBinaryTree(root->right);
    if (rh == -1)
        return -1;

    if (abs(lh - rh) > 1)
        return -1;

    return 1 + max(isBalancedBinaryTree(root->left), isBalancedBinaryTree(root->right));
}

// diameter of a tree - longest path btwn any two nodes
// needn't pass through the root of the tree
// as like as maxDepth. additional thing = update max at every node
int diameterValue = INT_MIN;
int diameterUtilization(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int lh = isBalancedBinaryTree(root->left);
    int rh = isBalancedBinaryTree(root->right);
    diameterValue = max(diameterValue, lh + rh);
    return 1 + max(lh, rh);
}
int diameter(TreeNode *root)
{
    diameterUtilization(root);
    return diameterValue;
}

// max path sum
// as same as maxDepth
int maxsumofpath = INT_MIN;
int maxpathsumUtilization(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int ls = max(0, maxpathsumUtilization(root->left));
    int rs = max(0, maxpathsumUtilization(root->right));
    maxsumofpath = max(maxsumofpath, ls + rs + root->data);
    return root->data + max(ls, rs);
}
int maxpathsum(TreeNode *root)
{
    maxpathsumUtilization(root);
    return maxsumofpath;
}

// check whether given two tree are identical or not
bool isIdentical(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL || root2 == NULL)
        return root1 == root2;

    return (root1->data == root2->data && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right));
}

vector<int> ZigZagTraversel(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == NULL)
        return {};

    queue<TreeNode *> q;
    q.push(root);
    bool flag = true;

    while (!q.empty())
    {
        int size = q.size();
        vector<int> ans(size);
        for (int i = 0; i < size; i++)
        {
            TreeNode *ptr = q.front();
            q.pop();

            int idx = ((flag) ? i : size - i - 1);

            ans[idx] = ptr->data;
            if (ptr->left != NULL)
                q.push(ptr->left);
            if (ptr->right != NULL)
                q.push(ptr->right);
        }
        flag = !flag;
        result.push_back(ans);
    }
    vector<int> finalans;
    for (auto i : result)
        for (auto j : i)
            finalans.push_back(j);
    return finalans;
}

bool isLeaf(TreeNode *root)
{
    return root->left == NULL && root->right == NULL;
}
void getLeaves(TreeNode *root, vector<int> &res)
{
    if (isLeaf(root))
    {
        res.push_back(root->data);
        return;
    }
    if (root->left)
        getLeaves(root->left, res);
    if (root->right)
        getLeaves(root->right, res);
}
// boundary traversel not done bcz if is more tough to understand

// vertical order traversel

vector<vector<int>> verticalLevelTraversel(TreeNode *root)
{
    if (root == NULL)
        return {{}};
    // verticals lines, level, values
    map<int, map<int, multiset<int>>> nodes;

    // node, vertical, level
    queue<pair<TreeNode *, pair<int, int>>> q;
    q.push({root, {0, 0}});

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        nodes[p.second.first][p.second.second].insert(p.first->data);
        if (p.first->left != NULL)
            q.push({p.first->left, {p.second.first - 1, p.second.second + 1}});
        if (p.first->right != NULL)
            q.push({p.first->right, {p.second.first + 1, p.second.second + 1}});
    }
    vector<vector<int>> ans;
    vector<int> oneDanswer;
    for (auto p : nodes)
    {
        vector<int> col;
        for (auto q : p.second)
        {
            oneDanswer.insert(oneDanswer.end(), q.second.begin(), q.second.end());
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
        ans.push_back(col);
    }
    return ans;
}
vector<int> topView(TreeNode *root)
{
    if (root == NULL)
        return {};
    // line, topmost value at line
    map<int, int> mp;
    // node, line
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        if (mp[p.second] == 0)
            mp[p.second] = p.first->data;
        if (p.first->left)
            q.push({p.first->left, p.second - 1});
        if (p.first->right)
            q.push({p.first->right, p.second + 1});
    }
    vector<int> ans;
    for (auto i : mp)
        ans.push_back(i.second);
    return ans;
}
vector<int> bottomView(TreeNode *root)
{
    if (root == NULL)
        return {};
    // line, downmost value at line
    map<int, int> mp;
    // node, line
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        mp[p.second] = p.first->data;
        if (p.first->left)
            q.push({p.first->left, p.second - 1});
        if (p.first->right)
            q.push({p.first->right, p.second + 1});
    }
    vector<int> ans;
    for (auto i : mp)
        ans.push_back(i.second);
    return ans;
}
// left and right view techniques using level order
vector<int> leftViewUsingLevelOrder(TreeNode *root)
{
    // do levelorder, push first node of the each level in the ans
    if (root == NULL)
        return {};
    queue<TreeNode *> q;
    q.push(root);
    vector<vector<int>> v;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> temp;
        for (int i = 0; i < size; i++)
        {
            TreeNode *ptr = q.front();
            q.pop();
            if (ptr->left != NULL)
                q.push(ptr->left);
            if (ptr->right != NULL)
                q.push(ptr->right);
            temp.push_back(ptr->data);
        }
        v.push_back(temp);
    }
    vector<int> ans;
    for (auto i : v)
        ans.push_back(i.front());
    return ans;
}
vector<int> rightViewUsingLevelOrder(TreeNode *root)
{
    // do levelorder, push last node of the each level in the ans
    if (root == NULL)
        return {};
    queue<TreeNode *> q;
    q.push(root);
    vector<vector<int>> v;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> temp;
        for (int i = 0; i < size; i++)
        {
            TreeNode *ptr = q.front();
            q.pop();
            if (ptr->left != NULL)
                q.push(ptr->left);
            if (ptr->right != NULL)
                q.push(ptr->right);
            temp.push_back(ptr->data);
        }
        v.push_back(temp);
    }
    vector<int> ans;
    for (auto i : v)
        ans.push_back(i.back());
    return ans;
}

// smart technique for left and right view of the tree
// left view
void leftViewUsingPreOrderUtil(TreeNode *root, int level, vector<int> &res)
{
    if (root == NULL)
        return;
    if (level == res.size())
        res.push_back(root->data);
    leftViewUsingPreOrderUtil(root->left, level + 1, res);
    leftViewUsingPreOrderUtil(root->right, level + 1, res);
}
vector<int> leftViewUsingPreOrder(TreeNode *root)
{
    vector<int> ans;
    leftViewUsingPreOrderUtil(root, 0, ans);
    return ans;
}
// right view
void rightViewUsingReversePreOrderUtil(TreeNode *root, int level, vector<int> &res)
{
    if (root == NULL)
        return;
    if (level == res.size())
        res.push_back(root->data);
    rightViewUsingReversePreOrderUtil(root->right, level + 1, res);
    rightViewUsingReversePreOrderUtil(root->left, level + 1, res);
}
vector<int> rightViewUsingReversePreOrder(TreeNode *root)
{
    vector<int> ans;
    rightViewUsingReversePreOrderUtil(root, 0, ans);
    return ans;
}

// if Binary tree have symmetry about x = 0 line (root line)
bool isSymmetricUtil(TreeNode *l, TreeNode *r)
{
    if (l == NULL || r == NULL)
        return l == r;
    if (l->data != r->data)
        return false;
    return isSymmetricUtil(l->left, r->right) && isSymmetricUtil(l->right, r->left);
}
bool isSymmetric(TreeNode *root)
{
    return root == NULL || isSymmetricUtil(root->left, root->right);
}

// print path from root to given node
bool pathFromRootToGivenNodeUtil(TreeNode *root, vector<int> &arr, int x)
{
    if (!root)
        return false;
    arr.push_back(root->data);
    if (root->data == x)
        return true;
    if (pathFromRootToGivenNodeUtil(root->left, arr, x) ||
        pathFromRootToGivenNodeUtil(root->right, arr, x))
        return true;
    arr.pop_back();
    return false;
}
vector<int> pathFromRootToGivenNode(TreeNode *root, int val)
{
    if (root == NULL)
        return {};
    vector<int> arr;
    pathFromRootToGivenNodeUtil(root, arr, val);
    return arr;
}
// my code
int lowestCommonAncestor(TreeNode *root, int data1, int data2)
{
    if (root == NULL)
        return -1;
    if (root->data == data1 || root->data == data2)
        return root->data;

    auto l = lowestCommonAncestor(root->left, data1, data2);
    auto r = lowestCommonAncestor(root->right, data1, data2);
    if (l == r && l == -1)
        return -1;
    if (l != -1 && r == -1)
        return l;
    if (l == -1 && r != -1)
        return r;
    return root->data;
}
// Striver code
TreeNode *LCA(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == NULL || root == p || root == q)
        return root;
    TreeNode *left = LCA(root->left, p, q);
    TreeNode *right = LCA(root->right, p, q);
    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;
    return root;
}

// convert binary tree to such a unique binary tree so that parent = sum of child
// we can only increase the value by 1 any number of times
void childrenSumProperty(TreeNode *root)
{
    if (root == NULL)
        return;
    int child = 0;
    if (root->left)
        child += root->left->data;
    if (root->right)
        child += root->right->data;

    if (child >= root->data)
        root->data = child;
    else
    {
        if (root->left)
            root->left->data = root->data;
        else if (root->right)
            root->right->data = root->data;
    }

    childrenSumProperty(root->left);
    childrenSumProperty(root->right);

    int tot = 0;
    if (root->left)
        tot += root->left->data;
    if (root->right)
        tot += root->right->data;
    if (root->left || root->right)
        root->data = tot;
}
int maxWidth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    // pair contains {Node, index}
    int ans = 0;
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        int size = q.size();
        int mmin = q.front().second;

        int first, last;
        for (int i = 0; i < size; i++)
        {
            int cur_id = q.front().second - mmin;
            TreeNode *node = q.front().first;
            q.pop();
            if (i == 0)
                first = cur_id;
            if (i == size - 1)
                last = cur_id;
            if (node->left)
                q.push({node->left, cur_id * 2 + 1});
            if (node->right)
                q.push({node->right, cur_id * 2 + 2});
        }
        ans = max(ans, last - first + 1);
    }
    return ans;
}
map<TreeNode *, TreeNode *> giveParentMap(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    map<TreeNode *, TreeNode *> mp;
    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        if (node->left)
        {
            mp[node->left] = (node);
            q.push(node->left);
        }
        if (node->right)
        {
            mp[node->right] = (node);
            q.push(node->right);
        }
    }
    return mp;
}

vector<int> nodeAtdistanceK(TreeNode *root, TreeNode *node, int k)
{
    if (root == NULL)
        return {};
    if (k == 0)
        return {node->data};
    map<TreeNode *, TreeNode *> mp = giveParentMap(root);

    unordered_map<TreeNode *, bool> visited;
    queue<TreeNode *> qe;
    qe.push(node);
    visited[node] = true;
    int dis = 0;
    vector<int> ans;
    while (!qe.empty())
    {
        ++dis;
        int sz = qe.size();
        for (int i = 0; i < sz; i++)
        {
            TreeNode *n = qe.front();
            qe.pop();
            TreeNode *l = n->left, *r = n->right, *p = mp[n];
            if (visited[l] == false && l)
                qe.push(l), visited[l] = true;
            if (visited[r] == false && r)
                qe.push(r), visited[r] = true;
            if (visited[p] == false && p)
                qe.push(p), visited[p] = true;
        }
        if (dis == k)
        {
            while (!qe.empty())
                ans.push_back(qe.front()->data), qe.pop();
            return ans;
        }
    }
    return {};
}
int minTimetoBurnTree(TreeNode *root, TreeNode *node)
{
    if (root == NULL)
        return 0;

    map<TreeNode *, TreeNode *> mp = giveParentMap(root);

    unordered_map<TreeNode *, bool> visited;
    queue<TreeNode *> q;
    q.push(node);
    visited[node] = true;
    int time = 0;
    while (!q.empty())
    {
        ++time;
        int sz = q.size();
        for (int i = 0; i < sz; i++)
        {
            TreeNode *n = q.front();
            q.pop();
            TreeNode *l = n->left, *r = n->right, *p = mp[n];
            if (visited[l] == false && l)
                q.push(l), visited[l] = true;
            if (visited[r] == false && r)
                q.push(r), visited[r] = true;
            if (visited[p] == false && p)
                q.push(p), visited[p] = true;
        }
        if (q.empty())
            return --time;
    }
    return --time;
}

// Total nodes in complete binary tree
int countCompleteTreeNodes(TreeNode *root)
{
    if (root == NULL)
        return 0;

    auto leftheight = [&](TreeNode *node)
    {
        int lh = 1;
        while (node)
        {
            lh++;
            node = node->left;
        }
        return lh;
    };
    auto rightheight = [&](TreeNode *node)
    {
        int rh = 1;
        while (node)
        {
            rh++;
            node = node->right;
        }
        return rh;
    };
    int lh = leftheight(root->left);
    int rh = rightheight(root->right);

    if (lh == rh)
        return (1 << lh) - 1;
    return 1 + countCompleteTreeNodes(root->left) + countCompleteTreeNodes(root->right);
}

TreeNode *constructBinaryTreeFromInOrderandPreOrder(vector<int> &PreOrder, vector<int> &InOrder)
{
    if (PreOrder.size() != InOrder.size())
        return NULL;
    unordered_map<int, int> mpp;
    for (int i = 0; i < InOrder.size(); i++)
        mpp[InOrder[i]] = i;

    function<TreeNode *(vector<int>, int, int, vector<int>, int, int, unordered_map<int, int>)> subFunc;
    subFunc = [&](vector<int> preorder, int preStart, int preEnd, vector<int> inorder, int inStart, int inEnd, unordered_map<int, int> mp)
    {
        TreeNode *nullnode = NULL;
        if (preStart > preEnd || inStart > inEnd)
            return nullnode;

        TreeNode *Root = new TreeNode(preorder[preStart]);
        int inRoot = mp[Root->data];
        int numsLeft = inRoot - inStart;

        Root->left = subFunc(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRoot - 1, mp);
        Root->right = subFunc(preorder, preStart + numsLeft + 1, preEnd, inorder, inRoot + 1, inEnd, mp);

        return Root;
    };

    TreeNode *root = subFunc(PreOrder, 0, PreOrder.size() - 1, InOrder, 0, InOrder.size() - 1, mpp);
    return root;
}
TreeNode *constructBinaryTreeFromInOrderandPostOrder(vector<int> &PostOrder, vector<int> &InOrder)
{
    if (PostOrder.size() != InOrder.size())
        return NULL;
    unordered_map<int, int> mpp;
    for (int i = 0; i < InOrder.size(); i++)
        mpp[InOrder[i]] = i;

    function<TreeNode *(vector<int>, int, int, vector<int>, int, int, unordered_map<int, int>)> subFunc;
    subFunc = [&](vector<int> postorder, int postStart, int postEnd, vector<int> inorder, int inStart, int inEnd, unordered_map<int, int> mp)
    {
        TreeNode *nullnode = NULL;
        if (postStart > postEnd || inStart > inEnd)
            return nullnode;

        TreeNode *Root = new TreeNode(postorder[postEnd]);
        int inRoot = mp[Root->data];
        int numsLeft = inRoot - inStart;

        Root->left = subFunc(postorder, postStart, postStart + numsLeft - 1, inorder, inStart, inRoot - 1, mp);
        Root->right = subFunc(postorder, postStart + numsLeft, postEnd - 1, inorder, inRoot + 1, inEnd, mp);

        return Root;
    };

    TreeNode *root = subFunc(PostOrder, 0, PostOrder.size() - 1, InOrder, 0, InOrder.size() - 1, mpp);
    return root;
}
string serialize(TreeNode *root)
{
    if (!root)
        return "";

    string s = "";
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode *currNode = q.front();
        q.pop();
        if (currNode == NULL)
            s.append("#,");
        else
        {
            s.append(to_string(currNode->data) + ",");
            q.push(currNode->left);
            q.push(currNode->right);
        }
    }
    return s;
}

TreeNode *deserialize(string data)
{
    if (data.size() == 0)
        return NULL;
    stringstream s(data);
    string str;
    getline(s, str, ',');
    TreeNode *root = new TreeNode(stoi(str));

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        getline(s, str, ',');
        if (str == "#")
            node->left = NULL;
        else
        {
            TreeNode *leftNode = new TreeNode(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        getline(s, str, ',');
        if (str == "#")
            node->right = NULL;
        else
        {
            TreeNode *rightNode = new TreeNode(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}
// Threaded binary tree - traversels with O(1) space
vector<int> morrisInorderTraversel(TreeNode *root)
{
    vector<int> inorder;
    TreeNode *curr = root;

    while (curr != NULL)
    {
        if (curr->left == NULL)
        {
            inorder.push_back(curr->data);
            curr = curr->right;
        }
        else
        {
            TreeNode *prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;

            if (prev->right == NULL)
            {
                // creating thread
                prev->right = curr;
                curr = curr->left;
            }
            else
            {
                // cutting thread while second time visiting
                prev->right = NULL;
                inorder.push_back(curr->data);
                curr = curr->right;
            }
        }
    }
    return inorder;
}

vector<int> morrisPreorderTraversel(TreeNode *root)
{
    vector<int> preorder;
    TreeNode *curr = root;

    while (curr != NULL)
    {
        if (curr->left == NULL)
        {
            preorder.push_back(curr->data);
            curr = curr->right;
        }
        else
        {
            TreeNode *prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;

            if (prev->right == NULL)
            {
                // creating thread
                prev->right = curr;
                preorder.push_back(curr->data);
                curr = curr->left;
            }
            else
            {
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
    return preorder;
}
// Idea (Free ka tree series) right left root - reverse preorder
// Actual code gfg - https://www.geeksforgeeks.org/flatten-a-binary-tree-into-linked-list/
void flattenBinaryTreetoLinkedListusingRecursion(TreeNode *root)
{
    if (root == NULL || root->left == NULL && root->right == NULL)
        return;

    if (root->left != NULL)
    {
        flattenBinaryTreetoLinkedListusingRecursion(root->left);

        TreeNode *tmpRight = root->right;
        root->right = root->left;
        root->left = NULL;

        TreeNode *t = root->right;
        while (t->right != NULL)
            t = t->right;

        t->right = tmpRight;
    }

    flattenBinaryTreetoLinkedListusingRecursion(root->right);
}
// Actual code striver - stack implementation
void flattenBinaryTreetoLinkedListusingStack(TreeNode *root)
{
    if (root == NULL)
        return;

    stack<TreeNode *> st;
    st.push(root);
    TreeNode *curr;
    while (!st.empty())
    {
        curr = st.top(), st.pop();
        if (curr->right)
            st.push(curr->right);
        if (curr->left)
            st.push(curr->left);

        if (!st.empty())
            curr->right = st.top();
        curr->left = NULL;
    }
}
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);



    return 0;
}
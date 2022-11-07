#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define lld long double
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define cel(x, a) (((x) + (a)-1) / (a))
#define all(v) v.begin(), v.end()

const int N = 1e5 + 4;
const int M = 1e9 + 7;

struct Data
{
    // Use required attributes
    ll mn;

    // Default Values
    Data() : mn(0){};
};

struct SegTree
{
    int N;
    vector<Data> st;

    void init(int n)
    {
        N = n;
        st.resize(4 * N + 5);
    }

    // Write reqd merge functions
    void merge(Data &cur, Data &l, Data &r)
    {
        cur.mn = max(l.mn, r.mn);
    }

    Data Query(int node, int L, int R, int i, int j)
    {

        if (j < L || i > R)
            return Data();
        if (i <= L && R <= j)
            return st[node];

        int mid = (L + R) / 2;
        Data left = Query(node * 2, L, mid, i, j);
        Data right = Query(node * 2 + 1, mid + 1, R, i, j);
        Data cur;
        merge(cur, left, right);
        return cur;
    }

    void pUpdate(int node, int L, int R, int pos, int val)
    {
        if (L == R)
        {
            st[node].mn = val;
            return;
        }

        int mid = (L + R) / 2;
        if (pos <= mid)
            pUpdate(node * 2, L, mid, pos, val);
        else
            pUpdate(node * 2 + 1, mid + 1, R, pos, val);

        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    Data query(int l, int r)
    {

        if (l > r)
            return Data();
        return Query(1, 1, N, l, r);
    }

    void update(int pos, int val)
    {

        if (pos > N || pos < 1)
            return;

        pUpdate(1, 1, N, pos, val);
    }
};
void solve()
{

    int n;
    cin >> n;

    int a[n + 1];
    map<int, int> ma;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        ma[a[i]] = i;
    }

    int ct = 1;

    for (auto &it : ma)
        it.S = ct, ct++;

    for (int i = 1; i <= n; i++)
        a[i] = ma[a[i]];

    SegTree seg[2];
    seg[0].init(n);
    seg[1].init(n);

    vector<int> suf(n + 3);

    for (int i = n; i >= 1; i--)
    {
        int maxi = seg[1].query(a[i] + 1, n).mn;

        seg[1].update(a[i], maxi + 1);

        suf[i] = seg[1].query(1, n).mn;
    }

    int ans = suf[1];

    for (int i = 1; i <= n; i++)
    {
        int maxi = seg[0].query(1, a[i] - 1).mn;

        seg[0].update(a[i], maxi + 1);

        int lef = seg[0].query(1, n).mn;

        ans = max(ans, lef + suf[i + 1]);
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}
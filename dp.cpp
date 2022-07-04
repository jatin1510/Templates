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

class Solution
{
public:
    // 1st
    int fib(int n, vector<int> &dp)
    {
        if (n <= 1)
            return dp[n] = n;

        if (dp[n] != -1)
            return dp[n];

        return dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
    }
    int fibonacci(int n)
    {
        // O(n) + stack space
        vector<int> dp(n + 1, -1);
        fib(n, dp);
        return dp[n];

        // O(n) space
        // if (n <= 1)
        //     return n;
        // vector<int> dp(n + 1);
        // dp[0] = 0;
        // dp[1] = 1;
        // for (int i = 1; i <= n; i++)
        //     dp[i] = dp[i - 1] + dp[i - 2];
        // return dp[n];

        // O(1) space
        // if (n <= 1)
        //     return n;
        // int first = 0, second = 1;
        // int loop = n - 1;
        // while (loop--)
        // {
        //     int curr = first + second;
        //     first = second;
        //     second = curr;
        // }
        // return second;
    }

    // 2nd - https://www.codingninjas.com/codestudio/problems/count-ways-to-reach-nth-stairs_798650
    vector<vector<long long int>> multi(vector<vector<long long int>> &a, vector<vector<long long int>> &b)
    {
        int M = 1e9 + 7;
        vector<vector<long long int>> c = {{0, 0}, {0, 0}};
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    c[i][j] += ((a[i][k] % M) * (b[k][j] % M)) % M;
        return c;
    }
    int FindNthTerm(long long int n)
    {
        int M = 1e9 + 7;

        vector<vector<long long int>> mat = {{1, 1}, {1, 0}};
        vector<vector<long long int>> res = {{1, 1}, {1, 0}};

        while (n)
        {
            if (n & 1)
                res = multi(mat, res);

            mat = multi(mat, mat);
            n = n >> 1;
        }
        return res[0][1] % M;
    }
    bool countDistinctWayToClimbStairSolve(int curr, long long n, int &ans, vector<int> &dp)
    {
        if (curr > n)
            return false;

        if (curr == n)
        {
            ans++;
            return true;
        }
        if (dp[curr] != -1)
        {
            ans++;
            return true;
        }

        if (countDistinctWayToClimbStairSolve(curr + 1, n, ans, dp))
            dp[curr + 1] = 1;
        if (countDistinctWayToClimbStairSolve(curr + 2, n, ans, dp))
            dp[curr + 2] = 1;
        return false;
    }
    int countDistinctWayToClimbStair(long long nStairs)
    {
        // Constraints - 1e18

        // TLE - O(N)
        // int ans = 0;
        // vector<int> dp(nStairs, -1);
        // countDistinctWayToClimbStairSolve(0, nStairs, ans, dp);
        // return ans;

        // Accepted
        return FindNthTerm(nStairs);
    }

    // 3rd - https://www.codingninjas.com/codestudio/problems/frog-jump_3621012
    int frogJump(int n, vector<int> &heights)
    {
        vector<int> dp(1e5 + 1);
        dp[0] = 0;
        dp[1] = abs(heights[1] - heights[0]);

        for (int i = 2; i < n; i++)
            dp[i] = min(dp[i - 1] + abs(heights[i] - heights[i - 1]), dp[i - 2] + abs(heights[i] - heights[i - 2]));
        return dp[n - 1];
    }

    // 4th - https://atcoder.jp/contests/dp/tasks/dp_b
    int frogJump2(int k, vector<int> &heights)
    {
        int n = heights.size();
        vector<int> dp(1e5 + 1);
        dp[0] = 0;

        for (int i = 1; i < n; i++)
        {
            int mn = INT_MAX;
            for (int j = 1; j <= k; j++)
                if (i - j >= 0)
                    mn = min(mn, dp[i - j] + abs(heights[i] - heights[i - j]));
            dp[i] = mn;
        }
        return dp[n - 1];
    }

    // 5th - https://www.codingninjas.com/codestudio/problems/maximum-sum-of-non-adjacent-elements_843261
    int maximumNonAdjacentSum(vector<int> &nums)
    {
        int n = nums.size();
        vector<long long> dp(1005);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++)
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        return dp[n - 1];
    }

    // 6th - https://www.codingninjas.com/codestudio/problems/house-robber_839733
    long long int houseRobber(vector<int> &valueInHouse)
    {
        if (valueInHouse.size() == 1)
            return valueInHouse[0];
        if (valueInHouse.size() == 2)
            return 0;
        // Write your code here.
        vector<int> v = valueInHouse;
        v.erase(v.begin());
        valueInHouse.erase(valueInHouse.end() - 1);
        return max(maximumNonAdjacentSum(v), maximumNonAdjacentSum(valueInHouse));
    }

    // 7th - https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003
    int func(int index, vector<vector<int>> &points)
    {
    }
    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        // Running, Fighting Practice or Learning New Moves
        return n;
    }
};
int32_t main()
{
    Solution ans;
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> v(n, vector<int>(3));
        for (auto &i : v)
            cin >> i[0] >> i[1] >> i[2];
        cout << ans.ninjaTraining(v.size(), v) << endl;
    }
    return 0;
}
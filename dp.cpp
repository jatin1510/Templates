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
#define PI (4 * atan(1))
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

class Solution
{
public:
    // dp on indices
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
    int func(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
    {
        if (day == 0)
        {
            int mx = 0;
            for (int i = 0; i < 3; i++)
                if (i != last)
                    mx = max(mx, points[0][i]);
            return mx;
        }

        if (dp[day][last] != -1)
            return dp[day][last];

        int mx = 0;
        for (int i = 0; i < 3; i++)
            if (i != last)
                mx = max(mx, points[day][i] + func(day - 1, i, points, dp));
        return dp[day][last] = mx;
    }
    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        // top-down with memoization
        // vector<vector<int>> dp(n, vector<int>(4, -1));
        // return func(n - 1, 3, points, dp);

        vector<vector<int>> dp(n, vector<int>(3, -1));
        dp[0] = points[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = points[i][0] + max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][1] = points[i][1] + max(dp[i - 1][0], dp[i - 1][2]);
            dp[i][2] = points[i][2] + max(dp[i - 1][0], dp[i - 1][1]);
        }
        return max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
    }

    // DP on grids
    // 8th - https://www.codingninjas.com/codestudio/problems/total-unique-paths_1081470
    bool isvalid(int i, int j, int m, int n)
    {
        return i >= 1 && i <= m && j >= 1 && j <= n;
    }
    int solve(int i, int j, int m, int n, vector<vector<int>> &dp)
    {
        if (!isvalid(i, j, m, n))
            return 0;
        if (i == m && j == n)
            return 1;
        if (dp[i][j] != -1)
            return dp[i][j];
        return dp[i][j] = solve(i + 1, j, m, n, dp) + solve(i, j + 1, m, n, dp);
    }
    int uniquePaths(int m, int n)
    {
        // bottom-up with memoization
        // vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        // return solve(1, 1, m, n, dp);

        // Tabulation
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[m - 1][n - 1];
    }

    // 9th - https://www.codingninjas.com/codestudio/problems/maze-obstacles_977241
    int mod = 1e9 + 7;
    bool isvalid2(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }
    int solve2(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (!isvalid2(i, j, n, m))
            return 0;
        if (i == n - 1 && j == m - 1)
            return 1;
        if (dp[i][j] != -1)
            return dp[i][j];
        long long d = 0, r = 0;
        if (isvalid2(i + 1, j, n, m))
            if (grid[i + 1][j] != -1)
                d = solve2(i + 1, j, n, m, grid, dp);
        if (isvalid2(i, j + 1, n, m))
            if (grid[i][j + 1] != -1)
                r = solve2(i, j + 1, n, m, grid, dp);
        return dp[i][j] = (d + r) % mod;
    }
    int mazeObstacles(int n, int m, vector<vector<int>> &mat)
    {
        // bottom-up with memoization
        // vector<vector<int>> dp(n, vector<int>(m, -1));
        // return solve2(0, 0, n, m, mat, dp);

        // Tabulation
        vector<vector<long long>> dp(n, vector<long long>(m, 0));
        dp[0][0] = (mat[0][0] != -1);
        for (int i = 1; i < m; i++)
        {
            if (mat[0][i] == -1)
                break;
            dp[0][i] = dp[0][i - 1];
        }
        for (int i = 1; i < n; i++)
        {
            if (mat[i][0] == -1)
                break;
            dp[i][0] = dp[i - 1][0];
        }
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (mat[i][j] != -1)
                    dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
        return dp[n - 1][m - 1];
    }

    // 10th - https://www.codingninjas.com/codestudio/problems/minimum-path-sum_985349
    int minSumPathsolve(int i, int j, int m, int n, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (i >= m || j >= n)
            return INT_MAX;

        if (i == m - 1 && j == n - 1)
            return grid[i][j];

        if (dp[i][j] != -1)
            return dp[i][j];

        return dp[i][j] = grid[i][j] + min(minSumPathsolve(i + 1, j, m, n, grid, dp), minSumPathsolve(i, j + 1, m, n, grid, dp));
    }
    int minSumPath(vector<vector<int>> &grid)
    {
        // bottom-up with memoization
        // int m = grid.size(), n = grid[0].size();
        // vector<vector<int>> dp(m, vector<int>(n, -1));
        // return minSumPathsolve(0, 0, m, n, grid, dp);

        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int i = 1; i < n; i++)
            dp[0][i] = dp[0][i - 1] + grid[0][i];

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        return dp[m - 1][n - 1];
    }

    // 11th - https://www.codingninjas.com/codestudio/problems/triangle_1229398
    int minimumPathSum(vector<vector<int>> &triangle, int n)
    {
        for (int i = n - 2; i >= 0; i--)
            for (int j = 0; j <= i; j++)
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        return triangle[0][0];
    }

    // 12th - https://www.codingninjas.com/codestudio/problems/maximum-path-sum-in-the-matrix_797998
    int getMaxPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                int down = matrix[i + 1][j];
                int left = INT_MIN, right = INT_MIN;
                if (j >= 0 && j < m - 1)
                    right = matrix[i + 1][j + 1];
                if (j > 0 && j <= m - 1)
                    left = matrix[i + 1][j - 1];

                matrix[i][j] += max({left, down, right});
            }
        }
        return *max_element(matrix[0].begin(), matrix[0].end());
    }

    // 3D dp
    // 13th - https://www.codingninjas.com/codestudio/problems/ninja-and-his-friends_3125885
    int maxchoco(int i, int j1, int j2, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
    {
        int n = grid.size(), m = grid[0].size();

        if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m)
            return -1e8;

        if (i == n - 1)
        {
            if (j1 == j2)
                return grid[i][j1];
            return grid[i][j1] + grid[i][j2];
        }

        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];

        int mx = 0;
        for (int dj1 = -1; dj1 <= 1; dj1++)
        {
            for (int dj2 = -1; dj2 <= 1; dj2++)
            {
                if (j1 == j2)
                    mx = max(mx, grid[i][j1] + maxchoco(i + 1, j1 + dj1, j2 + dj2, grid, dp));
                else
                    mx = max(mx, grid[i][j1] + grid[i][j2] + maxchoco(i + 1, j1 + dj1, j2 + dj2, grid, dp));
            }
        }
        return dp[i][j1][j2] = mx;
    }
    int maximumChocolates(int r, int c, vector<vector<int>> &grid)
    {
        vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
        return maxchoco(0, 0, c - 1, grid, dp);
    }

    // DP on subsequences
    // 14th - https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954
    bool subsetSumToKsolve(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
    {
        if (target == 0)
            return true;
        if (index == 0)
            return arr[0] == target;

        if (dp[index][target] != -1)
            return dp[index][target];

        bool notpick = subsetSumToKsolve(index - 1, target, arr, dp);
        bool pick = false;
        if (target >= arr[index])
            pick = subsetSumToKsolve(index - 1, target - arr[index], arr, dp);
        return dp[index][target] = pick or notpick;
    }
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        // vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
        // return subsetSumToKsolve(n - 1, k, arr, dp);

        // Tabulation
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));
        for (int i = 0; i < n; i++)
            dp[i][0] = 1;
        if (arr[0] <= k)
            dp[0][arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                int notpick = dp[i - 1][j];
                int pick = 0;
                if (j >= arr[i])
                    pick = dp[i - 1][j - arr[i]];
                dp[i][j] = pick | notpick;
            }
        }
        return dp[n - 1][k];
    }

    // 15th - https://www.codingninjas.com/codestudio/problems/partition-equal-subset-sum_892980utm_campaign=striver_dp_videos
    bool canPartition(vector<int> &arr, int n)
    {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        if (sum & 1)
            return false;

        return subsetSumToK(n, sum / 2, arr);
    }

    // 16th - https://www.codingninjas.com/codestudio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494
    int minSubsetSumDifference(vector<int> &arr, int n)
    {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int i = 0;
        while (1)
        {
            int find = sum / 2 - i;
            if (subsetSumToK(n, find, arr))
                break;
            i++;
        }
        int find = sum / 2 - i;
        int another = sum - find;
        return abs(find - another);
    }

    // 17th - https://www.codingninjas.com/codestudio/problems/number-of-subsets_3952532
    int findWaysSolve(int idx, int target, vector<int> &num, vector<vector<int>> &dp)
    {
        // if num array not contains zero then uncomment below 4 lines
        // if (target == 0)
        //     return 1;
        // if (idx == 0)
        //     return num[0] == target;

        // if num contains zero
        if (idx == 0)
        {
            if (target == 0 && num[0] == 0)
                return 2;
            if (target == 0 || num[0] == target)
                return 1;
            return 0;
        }

        if (dp[idx][target] != -1)
            return dp[idx][target];

        int notpick = findWaysSolve(idx - 1, target, num, dp);
        int pick = 0;
        if (target >= num[idx])
            pick = findWaysSolve(idx - 1, target - num[idx], num, dp);

        return dp[idx][target] = pick + notpick;
    }
    int findWays(vector<int> &num, int tar)
    {
        // top-down memoization
        // int n = num.size();
        // vector<vector<int>> dp(n, vector<int>(tar + 1, -1));
        // return findWaysSolve(n - 1, tar, num, dp);

        // tabulation
        int n = num.size();

        vector<vector<int>> dp(n, vector<int>(tar + 1, 0));

        if (num[0] == 0)
            dp[0][0] = 2; // 2 cases - pick and not pick
        else
            dp[0][0] = 1; // 1 case - not pick

        if (num[0] != 0 && num[0] <= tar)
            dp[0][num[0]] = 1; // 1 case -pick

        for (int ind = 1; ind < n; ind++)
        {
            for (int target = 0; target <= tar; target++)
            {

                int notTaken = dp[ind - 1][target];

                int taken = 0;
                if (num[ind] <= target)
                    taken = dp[ind - 1][target - num[ind]];

                dp[ind][target] = (notTaken + taken) % mod;
            }
        }
        return dp[n - 1][tar];
    }

    // 18th - https://www.codingninjas.com/codestudio/problems/partitions-with-given-difference_3751628
    int countPartitions(int n, int d, vector<int> &arr)
    {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        if (sum - d < 0 || (sum - d) & 1)
            return 0;
        int s2 = (sum - d) / 2;
        return findWays(arr, s2);
    }

    // 0 - 1 Knapsack
    // 19th - https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542
    int knapsacksolve(int idx, int w, vector<int> &value, vector<int> &weight, vector<vector<int>> &dp)
    {
        if (idx == 0)
            return (w >= weight[idx] ? value[idx] : 0);
        if (dp[idx][w] != -1)
            return dp[idx][w];

        int nottake = knapsacksolve(idx - 1, w, value, weight, dp);
        int take = -1e9;
        if (w >= weight[idx])
            take = value[idx] + knapsacksolve(idx - 1, w - weight[idx], value, weight, dp);

        return dp[idx][w] = max(take, nottake);
    }
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
    {
        // top-down memoization
        // vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
        // return knapsacksolve(n - 1, maxWeight, value, weight, dp);

        // tabulation
        // vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

        // for (int w = weight[0]; w <= maxWeight; w++)
        //     dp[0][w] = value[0];

        // for (int idx = 1; idx < n; idx++)
        // {
        //     for (int w = 0; w <= maxWeight; w++)
        //     {
        //         int nottake = dp[idx - 1][w];
        //         int take = INT_MIN;
        //         if (w >= weight[idx])
        //             take = value[idx] + dp[idx - 1][w - weight[idx]];
        //         dp[idx][w] = max(take, nottake);
        //     }
        // }
        // return dp[n - 1][maxWeight];

        // space optimization to 2 1d vector
        // vector<int> prev(maxWeight + 1, 0), cur(maxWeight + 1, 0);
        // for (int w = weight[0]; w <= maxWeight; w++)
        //     prev[w] = value[0];

        // for (int idx = 1; idx < n; idx++)
        // {
        //     for (int w = 0; w <= maxWeight; w++)
        //     {
        //         int nottake = prev[w];
        //         int take = INT_MIN;
        //         if (w >= weight[idx])
        //             take = value[idx] + prev[w - weight[idx]];
        //         cur[w] = max(take, nottake);
        //     }
        //     prev = cur;
        // }
        // return prev[maxWeight];

        // space optimization to only one 1d vector
        vector<int> prev(maxWeight + 1, 0);
        for (int w = weight[0]; w <= maxWeight; w++)
            prev[w] = value[0];

        for (int idx = 1; idx < n; idx++)
        {
            for (int w = maxWeight; w >= 0; w--)
            {
                int nottake = prev[w];
                int take = INT_MIN;
                if (w >= weight[idx])
                    take = value[idx] + prev[w - weight[idx]];
                prev[w] = max(take, nottake);
            }
        }
        return prev[maxWeight];
    }

    // 20th - https://www.codingninjas.com/codestudio/problems/minimum-elements_3843091
    int minimumElementssolve(int ind, int T, vector<int> &arr, vector<vector<int>> &dp)
    {
        if (ind == 0)
        {
            if (T % arr[0] == 0)
                return T / arr[0];
            else
                return 1e9;
        }

        if (dp[ind][T] != -1)
            return dp[ind][T];

        int nottake = 0 + minimumElementssolve(ind - 1, T, arr, dp);
        int take = 1e9;
        if (arr[ind] <= T)
            take = 1 + minimumElementssolve(ind, T - arr[ind], arr, dp);

        return dp[ind][T] = min(nottake, take);
    }
    int minimumElements(vector<int> &arr, int x)
    {
        // top-down memoization
        // int n = arr.size();
        // vector<vector<int>> dp(n, vector<int>(x + 1, -1));
        // int ans = minimumElementssolve(n - 1, x, arr, dp);
        // return ans == 1e9 ? -1 : ans;

        // tabulation
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(x + 1, 0));

        for (int i = 0; i <= x; i++)
        {
            if (i % arr[0] == 0)
                dp[0][i] = i / arr[0];
            else
                dp[0][i] = 1e9;
        }
        for (int ind = 1; ind < n; ind++)
        {
            for (int target = 0; target <= x; target++)
            {

                int notTake = 0 + dp[ind - 1][target];
                int take = 1e9;
                if (arr[ind] <= target)
                    take = 1 + dp[ind][target - arr[ind]];

                dp[ind][target] = min(notTake, take);
            }
        }

        int ans = dp[n - 1][x];
        if (ans >= 1e9)
            return -1;
        return ans;
    }

    // 21st - https://www.codingninjas.com/codestudio/problems/target-sum_4127362
    int targetSum(int n, int target, vector<int> &arr)
    {
        return countPartitions(n, target, arr);
    }

    // 22nd - https://www.codingninjas.com/codestudio/problems/ways-to-make-coin-change_630471
    long long countWaysToMakeChangeSolve(int idx, int target, int *coins, vector<vector<long>> &dp)
    {
        if (idx == 0)
            return target % coins[0] == 0;

        if (dp[idx][target] != -1)
            return dp[idx][target];

        long long nottake = countWaysToMakeChangeSolve(idx - 1, target, coins, dp);
        long long take = 0;
        if (target >= coins[idx])
            take = countWaysToMakeChangeSolve(idx, target - coins[idx], coins, dp);

        return dp[idx][target] = take + nottake;
    }
    long long countWaysToMakeChange(int *denominations, int n, int value)
    {
        // vector<vector<long>> dp(n, vector<long>(value + 1, -1));
        // return countWaysToMakeChangeSolve(n - 1, value, denominations, dp);

        // tabulation
        vector<vector<long>> dp(n, vector<long>(value + 1, -1));
        for (int i = 0; i <= value; i++)
            dp[0][i] = (i % denominations[0] == 0);

        for (int idx = 1; idx < n; idx++)
        {
            for (int target = 0; target <= value; target++)
            {
                long long nottake = dp[idx - 1][target];
                long long take = 0;
                if (target >= denominations[idx])
                    take = dp[idx][target - denominations[idx]];
                dp[idx][target] = take + nottake;
            }
        }
        return dp[n - 1][value];
    }

    // 23rd - https://www.codingninjas.com/codestudio/problems/unbounded-knapsack_1215029
    int unboundedKnapsackSolve(int idx, int w, vector<int> &profit, vector<int> &weight, vector<vector<int>> &dp)
    {
        if (idx == 0)
            return ((int)(w / weight[0])) * profit[0];

        if (dp[idx][w] != -1)
            return dp[idx][w];

        int nottake = unboundedKnapsackSolve(idx - 1, w, profit, weight, dp);
        int take = 0;
        if (w >= weight[idx])
            take = profit[idx] + unboundedKnapsackSolve(idx, w - weight[idx], profit, weight, dp);

        return dp[idx][w] = max(take, nottake);
    }
    int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
    {
        // vector<vector<int>> dp(n, vector<int>(w + 1, -1));
        // return unboundedKnapsackSolve(n - 1, w, profit, weight, dp);

        // tabulation
        vector<vector<int>> dp(n, vector<int>(w + 1, 0));
        for (int i = 0; i <= w; i++)
            dp[0][i] = (i / weight[0]) * profit[0];

        for (int idx = 1; idx < n; idx++)
        {
            for (int weigh = 0; weigh <= w; weigh++)
            {
                int nottake = dp[idx - 1][weigh];
                int take = 0;
                if (weigh >= weight[idx])
                    take = profit[idx] + dp[idx][weigh - weight[idx]];
                dp[idx][weigh] = max(take, nottake);
            }
        }
        return dp[n - 1][w];
    }

    // 24th - https://www.codingninjas.com/codestudio/problems/rod-cutting-problem_800284
    int cutRodSolve(int idx, int n, vector<int> &price, vector<vector<int>> &dp)
    {
        if (idx == 0)
            return n * price[0];
        if (dp[idx][n] != -1)
            return dp[idx][n];
        int nottake = cutRodSolve(idx - 1, n, price, dp);
        int take = INT_MIN;
        if (idx + 1 <= n)
            take = price[idx] + cutRodSolve(idx, n - (idx + 1), price, dp);

        return dp[idx][n] = max(nottake, take);
    }
    int cutRod(vector<int> &price, int n)
    {
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return cutRodSolve(n - 1, n, price, dp);
    }

    // dp on strings
    // 25th - https://www.codingninjas.com/codestudio/problems/longest-common-subsequence_624879
    int lcssolve(int i, int j, string s, string t, vector<vector<int>> &dp)
    {
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j])
            return 1 + lcssolve(i - 1, j - 1, s, t, dp);

        return dp[i][j] = max(lcssolve(i, j - 1, s, t, dp), lcssolve(i - 1, j, s, t, dp));
    }
    int lcs(string s, string t)
    {
        // int n = s.size(), m = t.size();
        // vector<vector<int>> dp(n, vector<int>(m, -1));
        // return lcssolve(n - 1, m - 1, s, t, dp);

        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 26th - https://www.codingninjas.com/codestudio/problems/longest-common-subsequence_624879
    string lcsprint(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        string ans;
        int i = n, j = m;
        while (i > 0 && j > 0)
        {
            if (s[i - 1] == t[j - 1])
            {
                ans.push_back(s[i - 1]);
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    // 27th - https://www.codingninjas.com/codestudio/problems/longest-common-substring_1235207
    int lcsubstring(string &str1, string &str2)
    {
        int n = str1.size(), m = str2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }

    // 28th - https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence-1612327878/1/
    int Longest_Palindromic_Subsequence(string s)
    {
        string t = s;
        reverse(t.begin(), t.end());
        return lcs(s, t);
    }

    // 29th - https://www.codingninjas.com/codestudio/problems/minimum-insertions-to-make-palindrome_985293
    int minInsertion(string &str)
    {
        return str.size() - Longest_Palindromic_Subsequence(str);
    }

    // 30th - https://www.codingninjas.com/codestudio/problems/can-you-make_4244510
    int canYouMake(string &str, string &ptr)
    {
        return str.size() + ptr.size() - 2 * lcs(str, ptr);
    }

    // 31st - https://www.codingninjas.com/codestudio/problems/shortest-supersequence_4244493
    string shortestSupersequence(string a, string b)
    {
        int n = a.size(), m = b.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        string ans;
        int i = n, j = m;
        while (i > 0 && j > 0)
        {
            if (a[i - 1] == b[j - 1])
            {
                ans.push_back(a[i - 1]);
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                ans.push_back(a[--i]);
            }
            else
            {
                ans.push_back(b[--j]);
            }
        }
        while (i > 0)
            ans.push_back(a[--i]);
        while (j > 0)
            ans.push_back(b[--j]);

        reverse(ans.begin(), ans.end());
        return ans;
    }

    // 32nd - https://www.codingninjas.com/codestudio/problems/subsequence-counting_3755256
    int prime = 1e9 + 7;
    int countUtil(string s1, string s2, int ind1, int ind2, vector<vector<int>> &dp)
    {
        if (ind2 < 0)
            return 1;
        if (ind1 < 0)
            return 0;

        if (dp[ind1][ind2] != -1)
            return dp[ind1][ind2];

        if (s1[ind1] == s2[ind2])
        {
            int leaveOne = countUtil(s1, s2, ind1 - 1, ind2 - 1, dp);
            int stay = countUtil(s1, s2, ind1 - 1, ind2, dp);
            return dp[ind1][ind2] = (leaveOne + stay) % prime;
        }
        return dp[ind1][ind2] = countUtil(s1, s2, ind1 - 1, ind2, dp);
    }
    int subsequenceCounting(string &t, string &s, int lt, int ls)
    {
        // vector<vector<int>> dp(lt, vector<int>(ls, -1));
        // return countUtil(t, s, lt - 1, ls - 1, dp);

        // tabulation - leetcode
        vector<vector<double>> dp(lt + 1, vector<double>(ls + 1, 0));
        for (int i = 0; i <= lt; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= lt; i++)
        {
            for (int j = 1; j <= ls; j++)
            {
                if (t[i - 1] == s[j - 1])
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return int(dp[lt][ls]);
    }

    // 33rd - https://www.codingninjas.com/codestudio/problems/edit-distance_630420
    int editDistanceSolve(int i, int j, string s, string t, vector<vector<int>> &dp)
    {
        if (i < 0)
            return j + 1;
        if (j < 0)
            return i + 1;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j])
            return dp[i][j] = editDistanceSolve(i - 1, j - 1, s, t, dp);

        int del = editDistanceSolve(i - 1, j, s, t, dp);
        int insert = editDistanceSolve(i, j - 1, s, t, dp);
        int replace = editDistanceSolve(i - 1, j - 1, s, t, dp);
        return dp[i][j] = 1 + min({del, insert, replace});
    }
    int editDistance(string str1, string str2)
    {
        // int n = str1.size(), m = str2.size();
        // vector<vector<int>> dp(n, vector<int>(m, -1));
        // return editDistanceSolve(str1.size() - 1, str2.size() - 1, str1, str2, dp);

        int n = str1.size(), m = str2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            dp[i][0] = i;
        for (int j = 1; j <= m; j++)
            dp[0][j] = j;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                {
                    int del = dp[i - 1][j];
                    int insert = dp[i][j - 1];
                    int replace = dp[i - 1][j - 1];
                    dp[i][j] = 1 + min({del, insert, replace});
                }
            }
        }
        return dp[n][m];
    }

    // 34th - https://www.codingninjas.com/codestudio/problems/wildcard-pattern-matching_701650
    bool isAllStars(string &S1, int i)
    {
        for (int j = 0; j <= i; j++)
            if (S1[j] != '*')
                return false;
        return true;
    }

    bool wildcardMatchingUtil(string &S1, string &S2, int i, int j, vector<vector<int>> &dp)
    {

        // Base Conditions
        if (i < 0 && j < 0)
            return true;
        if (i < 0 && j >= 0)
            return false;
        if (j < 0 && i >= 0)
            return isAllStars(S1, i);

        if (dp[i][j] != -1)
            return dp[i][j];

        if (S1[i] == S2[j] || S1[i] == '?')
            return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

        else
        {
            if (S1[i] == '*')
                return wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
            else
                return false;
        }
    }
    bool wildcardMatching(string &S1, string &S2)
    {
        // int n = S1.size();
        // int m = S2.size();
        // vector<vector<int>> dp(n, vector<int>(m, -1));
        // return wildcardMatchingUtil(S1, S2, n - 1, m - 1, dp);

        int n = S1.size();
        int m = S2.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m, false));

        dp[0][0] = true;

        for (int j = 1; j <= m; j++)
            dp[0][j] = false;
        for (int i = 1; i <= n; i++)
            dp[i][0] = isAllStars(S1, i);

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (S1[i - 1] == S2[j - 1] || S1[i - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else
                {
                    if (S1[i - 1] == '*')
                        dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                    else
                        dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }

    // dp on stocks
    // 35th - https://www.codingninjas.com/codestudio/problems/stocks-are-profitable_893405
    int maximumProfit(vector<int> &prices)
    {
        int n = prices.size();
        int mini = prices[0];
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            ans = max(ans, prices[i] - mini);
            mini = min(mini, prices[i]);
        }
        return ans;
    }

    // 36th - https://www.codingninjas.com/codestudio/problems/selling-stock_630282
    long getMaximumProfitSolve(long *values, int ind, int buy, int n, vector<vector<long>> &dp)
    {

        if (ind == n)
            return 0;

        if (dp[ind][buy] != -1)
            return dp[ind][buy];

        long profit;

        if (buy)
        {
            profit = max(0 + getMaximumProfitSolve(values, ind + 1, 1, n, dp), values[ind] + getMaximumProfitSolve(values, ind + 1, 0, n, dp));
        }
        else
        {
            profit = max(0 + getMaximumProfitSolve(values, ind + 1, 0, n, dp), -values[ind] + getMaximumProfitSolve(values, ind + 1, 1, n, dp));
        }

        return dp[ind][buy] = profit;
    }
    long getMaximumProfit(long *values, int n)
    {
        // vector<vector<long>> dp(n, vector<long>(2, -1));
        // return getMaximumProfitSolve(values, 0, 0, n, dp);

        vector<vector<long>> dp(n + 1, vector<long>(2));
        dp[n][0] = dp[n][1] = 0;
        long profit;
        for (int ind = n - 1; ind >= 0; ind--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                if (buy)
                    profit = max(0 + dp[ind + 1][1], values[ind] + dp[ind + 1][0]);
                else
                    profit = max(0 + dp[ind + 1][0], -values[ind] + dp[ind + 1][1]);

                dp[ind][buy] = profit;
            }
        }
        return dp[0][0];
    }

    // 37th - https://www.codingninjas.com/codestudio/problems/buy-and-sell-stock_1071012
    int maxProfitSolve(int idx, int buy, int cap, vector<int> &prices, vector<vector<vector<int>>> &dp)
    {
        if (idx == prices.size() || cap == 0)
            return 0;

        if (dp[idx][buy][cap] != -1)
            return dp[idx][buy][cap];

        int profit = 0;
        if (buy)
        {
            profit = max(-prices[idx] + maxProfitSolve(idx + 1, 0, cap, prices, dp), 0 + maxProfitSolve(idx + 1, 1, cap, prices, dp));
        }
        else
        {
            profit = max(prices[idx] + maxProfitSolve(idx + 1, 1, cap - 1, prices, dp), 0 + maxProfitSolve(idx + 1, 0, cap, prices, dp));
        }
        return dp[idx][buy][cap] = profit;
    }
    int maxProfit(vector<int> &prices, int n)
    {
        // vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
        // return maxProfitSolve(0, 1, 2, prices, dp);

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        // as vector initializes to 0, base case is already taken care of

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                for (int cap = 1; cap <= 2; cap++)
                {
                    int profit = 0;
                    if (buy)
                        profit = max(-prices[idx] + dp[idx + 1][0][cap], 0 + dp[idx + 1][1][cap]);
                    else
                        profit = max(prices[idx] + dp[idx + 1][1][cap - 1], 0 + dp[idx + 1][0][cap]);
                    dp[idx][buy][cap] = profit;
                }
            }
        }
        return dp[0][1][2];
    }

    // 38th - https://www.codingninjas.com/codestudio/problems/best-time-to-buy-and-sell-stock_1080698
    int maximumProfit4(vector<int> &prices, int n, int k)
    {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
        // as vector initializes to 0, base case is already taken care of

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int buy = 0; buy <= 1; buy++)
            {
                for (int cap = 1; cap <= k; cap++)
                {
                    int profit = 0;
                    if (buy)
                        profit = max(-prices[idx] + dp[idx + 1][0][cap], 0 + dp[idx + 1][1][cap]);
                    else
                        profit = max(prices[idx] + dp[idx + 1][1][cap - 1], 0 + dp[idx + 1][0][cap]);
                    dp[idx][buy][cap] = profit;
                }
            }
        }
        return dp[0][1][k];
    }

    // 39th - https://www.codingninjas.com/codestudio/problems/highway-billboards_3125969
    int stockProfitSolve(int idx, int buy, vector<int> &prices, vector<vector<int>> &dp)
    {
        if (idx >= prices.size())
            return 0;

        if (dp[idx][buy] != -1)
            return dp[idx][buy];

        if (buy)
        {
            return dp[idx][buy] = max(-prices[idx] + stockProfitSolve(idx + 1, 0, prices, dp), 0 + stockProfitSolve(idx + 1, 1, prices, dp));
        }
        return dp[idx][buy] = max(prices[idx] + stockProfitSolve(idx + 2, 1, prices, dp), 0 + stockProfitSolve(idx + 1, 0, prices, dp));
    }
    int stockProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return stockProfitSolve(0, 1, prices, dp);
    }

    // 40th - https://www.codingninjas.com/codestudio/problems/rahul-and-his-chocolates_3118974
    int maximumProfit5Solve(int idx, int buy, int fee, vector<int> &prices, vector<vector<int>> &dp)
    {
        if (idx >= prices.size())
            return 0;

        if (dp[idx][buy] != -1)
            return dp[idx][buy];

        if (buy)
        {
            return dp[idx][buy] = max(-prices[idx] + maximumProfit5Solve(idx + 1, 0, fee, prices, dp), 0 + maximumProfit5Solve(idx + 1, 1, fee, prices, dp));
        }
        return dp[idx][buy] = max(prices[idx] - fee + maximumProfit5Solve(idx + 1, 1, fee, prices, dp), 0 + maximumProfit5Solve(idx + 1, 0, fee, prices, dp));
    }
    int maximumProfit5(int n, int fee, vector<int> &prices)
    {
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return maximumProfit5Solve(0, 1, fee, prices, dp);
    }

    // dp on LIS
    // 41st - https://www.codingninjas.com/codestudio/problems/longest-increasing-subsequence_630459
    int lisSolve(int idx, int prev_idx, int n, int arr[], vector<vector<int>> &dp)
    {
        if (idx == n)
            return 0;

        if (dp[idx][prev_idx + 1] != -1)
            return dp[idx][prev_idx + 1];

        int len = lisSolve(idx + 1, prev_idx, n, arr, dp);
        if (prev_idx == -1 || arr[idx] > arr[prev_idx])
            len = max(len, 1 + lisSolve(idx + 1, idx, n, arr, dp));

        return dp[idx][prev_idx + 1] = len;
    }
    int longestIncreasingSubsequence(int arr[], int n)
    {
        // 1. Rec + Memo
        // vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        // return lisSolve(0, -1, n, arr, dp);

        // 2. Tabulation
        // vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        // for (int idx = n - 1; idx >= 0; idx--)
        // {
        //     for (int prev_idx = idx - 1; prev_idx >= -1; prev_idx--)
        //     {
        //         int len = dp[idx + 1][prev_idx + 1];
        //         if (prev_idx == -1 || arr[idx] > arr[prev_idx])
        //             len = max(len, 1 + dp[idx + 1][idx + 1]);

        //         dp[idx][prev_idx + 1] = len;
        //     }
        // }
        // return dp[0][0];

        // 3. TLE
        vector<int> dp(n, 1);
        int maxi = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[j] < arr[i])
                {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            maxi = max(maxi, dp[i]);
        }
        return maxi;

        // 4. n * logn
        // vector<int> v;
        // for (int i = 0; i < n; i++)
        // {
        //     auto l = lower_bound(v.begin(), v.end(), arr[i]);
        //     if (l == v.end())
        //         v.push_back(arr[i]);
        //     else
        //         v[l - v.begin()] = arr[i];
        // }
        // return v.size();
    }

    // 42nd - https://www.codingninjas.com/codestudio/problems/longest-increasing-subsequence_630459
    // 43rd - https://www.codingninjas.com/codestudio/problems/longest-increasing-subsequence_630459
    // 42 and 43 covered in 41 code

    // 44th - https://www.codingninjas.com/codestudio/problems/divisible-set_3754960
    vector<int> divisibleSet(vector<int> &arr)
    {
        sort(arr.begin(), arr.end());

        int n = arr.size(), maxi = 1, idx;
        vector<int> dp(n, 1);
        vector<int> mp(n, -1);
        mp[0] = -1;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i] % arr[j] == 0 && dp[i] < 1 + dp[j])
                {
                    dp[i] = 1 + dp[j];
                    mp[i] = j;
                }
            }
            maxi = max(maxi, dp[i]);
            if (maxi == dp[i])
                idx = i;
        }

        vector<int> ans(maxi);
        int ptr = maxi - 1;
        while (idx != -1)
        {
            ans[ptr--] = arr[idx];
            idx = mp[idx];
        }
        return ans;
    }

    // 45th - https://www.codingninjas.com/codestudio/problems/longest-string-chain_3752111
    bool check(string &a, string &b)
    {
        if (a.size() != b.size() + 1)
            return 0;

        int first = 0, second = 0;
        while (first < a.size())
        {
            if (second < b.size() && a[first] == b[second])
            {
                first++;
                second++;
            }
            else
            {
                first++;
            }
        }
        return first == a.size() && second == b.size();
    }
    int longestStrChain(vector<string> &arr)
    {
        sort(arr.begin(), arr.end(), [&](string &a, string &b) -> bool
             { return a.size() < b.size(); });

        int n = arr.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (check(arr[i], arr[j]))
                {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    // 46th - https://www.codingninjas.com/codestudio/problems/longest-bitonic-sequence_1062688
    int longestBitonicSequence(vector<int> &arr, int n)
    {
        vector<int> pref(n, 1), suff(n, 1);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                if (arr[j] < arr[i])
                    pref[i] = max(pref[i], 1 + pref[j]);
        for (int i = n - 1; i >= 0; i--)
            for (int j = n - 1; j > i; j--)
                if (arr[j] < arr[i])
                    suff[i] = max(suff[i], 1 + suff[j]);

        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = max(ans, pref[i] + suff[i] - 1);
        return ans;
    }

    // 47th - https://www.codingninjas.com/codestudio/problems/number-of-longest-increasing-subsequence_3751627
    int findNumberOfLIS(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> dp(n, 1), cnt(n, 1);
        int maxi = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[j] < arr[i] && 1 + dp[j] > dp[i])
                {
                    dp[i] = 1 + dp[j];
                    cnt[i] = cnt[j];
                }
                else if (arr[j] < arr[i] && 1 + dp[j] == dp[i])
                {
                    cnt[i] += cnt[j];
                }
            }
            maxi = max(maxi, dp[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (maxi == dp[i])
                ans += cnt[i];
        }
        return ans;
    }

    // dp on MCM - Partition DP
    // 48th - https://www.codingninjas.com/codestudio/problems/matrix-chain-multiplication_975344
    int MCMSolve(int i, int j, vector<int> &arr, vector<vector<int>> &dp)
    {
        if (i == j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int ans = 1e9;
        for (int k = i; k < j; k++)
            ans = min(ans, arr[i - 1] * arr[k] * arr[j] + MCMSolve(i, k, arr, dp) + MCMSolve(k + 1, j, arr, dp));

        return dp[i][j] = ans;
    }
    int matrixMultiplication(vector<int> &arr, int N)
    {
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return MCMSolve(1, N - 1, arr, dp);
    }

    // 49th - https://www.codingninjas.com/codestudio/problems/matrix-chain-multiplication_975344
    int matrixMultiplicationTab(vector<int> &arr, int N)
    {
        vector<vector<int>> dp(N, vector<int>(N));
        // base case done
        for (int i = N - 1; i >= 1; i--)
        {
            for (int j = i + 1; j < N; j++)
            {
                int ans = 1e9;
                for (int k = i; k < j; k++)
                    ans = min(ans, arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j]);

                dp[i][j] = ans;
            }
        }
        return dp[1][N - 1];
    }

    // 50th - https://www.codingninjas.com/codestudio/problems/cost-to-cut-a-chocolate_3208460
    int costSolve(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
    {
        if (i > j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];
        int ans = INT_MAX;
        for (int idx = i; idx <= j; idx++)
        {
            ans = min(ans, cuts[j + 1] - cuts[i - 1] + costSolve(i, idx - 1, cuts, dp) + costSolve(idx + 1, j, cuts, dp));
        }
        return dp[i][j] = ans;
    }
    int cost(int n, int c, vector<int> &cuts)
    {
        // vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));
        // cuts.insert(cuts.begin(), 0);
        // cuts.push_back(n);
        // sort(cuts.begin(), cuts.end());
        // return costSolve(1, c, cuts, dp);
        vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        for (int i = c; i >= 1; i--)
        {
            for (int j = 1; j <= c; j++)
            {
                if (i > j)
                    continue;

                int ans = INT_MAX;
                for (int idx = i; idx <= j; idx++)
                    ans = min(ans, cuts[j + 1] - cuts[i - 1] + dp[i][idx - 1] + dp[idx + 1][j]);
                dp[i][j] = ans;
            }
        }
        return dp[1][c];
    }

    // 51st - https://www.codingninjas.com/codestudio/problems/mining-diamonds_4244494
    int maxCoinsSolve(int i, int j, vector<int> &a, vector<vector<int>> &dp)
    {
        if (i > j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int ans = INT_MIN;
        for (int idx = i; idx <= j; idx++)
        {
            ans = max(ans, a[i - 1] * a[idx] * a[j + 1] + maxCoinsSolve(i, idx - 1, a, dp) + maxCoinsSolve(idx + 1, j, a, dp));
        }
        return dp[i][j] = ans;
    }
    int maxCoins(vector<int> &a)
    {
        // int n = a.size();
        // vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        // a.insert(a.begin(), 1);
        // a.push_back(1);
        // return maxCoinsSolve(1, n, a, dp);

        int n = a.size();
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        a.insert(a.begin(), 1);
        a.push_back(1);

        for (int i = n; i >= 1; i--)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i > j)
                    continue;
                int ans = INT_MIN;
                for (int idx = i; idx <= j; idx++)
                    ans = max(ans, a[i - 1] * a[idx] * a[j + 1] + dp[i][idx - 1] + dp[idx + 1][j]);
                dp[i][j] = ans;
            }
        }
        return dp[1][n];
    }

    // 52nd - https://www.codingninjas.com/codestudio/problems/problem-name-boolean-evaluation_1214650
    long long evaluateExpSolve(int i, int j, bool isTrue, string &expr, vector<vector<vector<long long>>> &dp)
    {
        if (i > j)
            return 0;
        if (i == j)
        {
            if (isTrue)
                return expr[i] == 'T';
            return expr[i] == 'F';
        }

        if (dp[i][j][isTrue] != -1)
            return dp[i][j][isTrue];

        long long ans = 0;
        for (int idx = i + 1; idx <= j - 1; idx += 2)
        {
            long long leftTrue = evaluateExpSolve(i, idx - 1, 1, expr, dp);
            long long leftFalse = evaluateExpSolve(i, idx - 1, 0, expr, dp);
            long long rightTrue = evaluateExpSolve(idx + 1, j, 1, expr, dp);
            long long rightFalse = evaluateExpSolve(idx + 1, j, 0, expr, dp);

            if (expr[idx] == '&')
            {
                if (isTrue)
                    ans = (ans + leftTrue * rightTrue) % (int)(1e9 + 7);
                else
                    ans = (ans + leftFalse * rightTrue + leftTrue * rightFalse + leftFalse * rightFalse) % (int)(1e9 + 7);
            }
            else if (expr[idx] == '|')
            {
                if (isTrue)
                    ans = (ans + leftTrue * rightTrue + leftFalse * rightTrue + leftTrue * rightFalse) % (int)(1e9 + 7);
                else
                    ans = (ans + leftFalse * rightFalse) % (int)(1e9 + 7);
            }
            else
            {
                if (isTrue)
                    ans = (ans + leftTrue * rightFalse + leftFalse * rightTrue) % (int)(1e9 + 7);
                else
                    ans = (ans + leftFalse * rightFalse + leftTrue * rightTrue) % (int)(1e9 + 7);
            }
        }
        return dp[i][j][isTrue] = ans % (int)(1e9 + 7);
    }
    int evaluateExp(string &exp)
    {
        vector<vector<vector<long long>>> dp(exp.size(), vector<vector<long long>>(exp.size(), vector<long long>(2, -1)));
        return evaluateExpSolve(0, exp.size() - 1, 1, exp, dp);
    }

    // 53rd - https://www.codingninjas.com/codestudio/problems/palindrome-partitioning_873266
    bool isPalindrome(int i, int j, string s)
    {
        while (i < j)
        {
            if (s[i] != s[j])
                return false;
            i++, j--;
        }
        return true;
    }
    int palindromePartitioningSolve(int idx, string &str, vector<int> &dp)
    {
        if (idx == str.size())
            return 0;

        if (dp[idx] != -1)
            return dp[idx];
        int ans = INT_MAX;
        for (int i = idx; i < str.size(); i++)
        {
            if (isPalindrome(idx, i, str))
                ans = min(ans, 1 + palindromePartitioningSolve(i + 1, str, dp));
        }
        return dp[idx] = ans;
    }
    int palindromePartitioning(string str)
    {
        // vector<int> dp(str.size(), -1);
        // return palindromePartitioningSolve(0, str, dp) - 1;

        vector<int> dp(str.size() + 1, 0);
        for (int idx = str.size() - 1; idx >= 0; idx--)
        {
            int ans = INT_MAX;
            for (int i = idx; i < str.size(); i++)
            {
                if (isPalindrome(idx, i, str))
                    ans = min(ans, 1 + dp[i + 1]);
            }
            dp[idx] = ans;
        }
        return dp[0] - 1;
    }

    // 54th - https://www.codingninjas.com/codestudio/problems/maximum-subarray_3755255
    int maximumSubarraySolve(int idx, int k, vector<int> &nums, vector<int> &dp)
    {
        int n = nums.size();
        if (idx == nums.size())
            return 0;
        if (dp[idx] != -1)
            return dp[idx];
        int ans = INT_MIN, maxi = INT_MIN;
        for (int i = idx; i < min(idx + k, n); i++)
        {
            maxi = max(maxi, nums[i]);
            ans = max(ans, maxi * (i - idx + 1) + maximumSubarraySolve(i + 1, k, nums, dp));
        }
        return dp[idx] = ans;
    }
    int maximumSubarray(vector<int> &num, int k)
    {
        // int n = num.size();
        // vector<int> dp(n, -1);
        // return maximumSubarraySolve(0, k, num, dp);

        int n = num.size();
        vector<int> dp(n + 1, 0);

        for (int idx = n - 1; idx >= 0; idx--)
        {
            int ans = INT_MIN, maxi = INT_MIN;
            for (int i = idx; i < min(idx + k, n); i++)
            {
                maxi = max(maxi, num[i]);
                ans = max(ans, maxi * (i - idx + 1) + maximumSubarraySolve(i + 1, k, num, dp));
            }
            dp[idx] = ans;
        }
        return dp[0];
    }

    // dp on squares
    // 55th - https://www.codingninjas.com/codestudio/problems/maximum-size-rectangle-sub-matrix-with-all-1-s_893017
    // below question is of Stack
    int largestRectangleArea(vector<int> &histo)
    {
        stack<int> st;
        int maxA = 0;
        int n = histo.size();
        for (int i = 0; i <= n; i++)
        {
            while (!st.empty() && (i == n || histo[st.top()] >= histo[i]))
            {
                int height = histo[st.top()];
                st.pop();
                int width;
                if (st.empty())
                    width = i;
                else
                    width = i - st.top() - 1;
                maxA = max(maxA, width * height);
            }
            st.push(i);
        }
        return maxA;
    }
    int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &mat, int n, int m)
    {
        vector<int> heights(m);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j])
                    heights[j] += mat[i][j];
                else
                    heights[j] = 0;
            }
            ans = max(ans, largestRectangleArea(heights));
        }
        return ans;
    }

    // 56th - https://www.codingninjas.com/codestudio/problems/count-square-submatrices-with-all-ones_3751502
    int countSquares(int n, int m, vector<vector<int>> &arr)
    {
        vector<vector<int>> dp = arr;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (arr[i][j])
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});

        int ans = 0;
        for (auto i : dp)
            ans += accumulate(i.begin(), i.end(), 0);
        return ans;
    }
};
int32_t main()
{
    Solution ans;
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> v(n, vector<int>(m));
        for (auto &i : v)
            for (auto &j : i)
                cin >> j;

        cout << ans.countSquares(n, m, v) << endl;
    }
    return 0;
}
// #include <bits/stdc++.h>
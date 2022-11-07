//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    vector<vector<int>> dp;
    int mod = 1e9 + 7, N;
    long long solve(int idx, int sum)
    {
        if (sum == 0)
            return 1;

        if (idx == N)
            return sum == 0;

        if (dp[idx][sum] != -1)
            return dp[idx][sum];

        long long cnt = 0;
        for (int i = 0; i <= 9; i++)
        {
            if (idx == 0 && i == 0)
                continue;
            if (sum >= i)
                cnt = (cnt + solve(idx + 1, sum - i)) % mod;
        }
        return dp[idx][sum] = cnt;
    }
    long int countWays(int n, int Sum)
    {
        // code here
        if (!Sum)
            return -1;

        N = n;
        dp = vector<vector<int>>(101, vector<int>(1001, -1));
        
        long long ans = solve(0, Sum);
        if (!ans)
            return -1;
        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int idx, Sum;
        cin >> idx >> Sum;

        Solution ob;
        cout << ob.countWays(idx, Sum) << endl;
    }
    return 0;
}
// } Driver Code Ends
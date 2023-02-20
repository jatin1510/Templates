//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    int dp[101][100001];
    bool help(int idx, int sum, int N, int arr[])
    {
        if (sum < 0)
            return 0;

        if (sum == 0)
            return 1;

        if (idx == N)
            return sum == 0;

        if (dp[idx][sum] != -1)
            return dp[idx][sum];
        bool take = help(idx + 1, sum - arr[idx], N, arr);
        bool nottake = help(idx + 1, sum, N, arr);
        return dp[idx][sum] = take or nottake;
    }
    int equalPartition(int N, int arr[])
    {
        // code here
        memset(dp, -1, sizeof dp);
        int sum = accumulate(arr, arr + N, 0ll);
        if (sum % 2 != 0)
            return 0;
        return help(0, sum / 2, N, arr);
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin >> N;
        int arr[N];
        for (int i = 0; i < N; i++)
            cin >> arr[i];

        Solution ob;
        if (ob.equalPartition(N, arr))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
// } Driver Code Ends
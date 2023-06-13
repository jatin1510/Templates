//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

int countRev(string s)
{
    int n = s.size();
    if (n % 2)
        return -1;
    int ans = 0, cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
            cnt++;
        else
            cnt--;

        if (cnt < 0)
            cnt = 1, ans++;
    }
    ans += (abs(cnt) / 2);
    return ans;
}

int minAddToMakeValid(string s)
{
    int opened = 0, ans = 0;
    for (auto i : s)
    {
        if (i == '(')
            opened++;
        else
            opened--;

        if (opened < 0)
            opened = 0, ans++;
    }
    return ans + opened;
}

int minSwaps(string s)
{
    int cnt = 0, ans = 0;
    for (auto i : s)
    {
        if (i == '(')
            cnt++;
        else
            cnt--;

        if (cnt < 0)
            cnt = 1, ans++;
    }
    return ans;
}

string minRemoveToMakeValid(string s)
{
    int n = s.size(), cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
            cnt++;
        else
            cnt--;

        if (cnt < 0)
        {
            s[i] = '#';
            cnt = 0;
        }
    }

    int j = n - 1;
    while (j >= 0 and cnt)
    {
        if (s[j] == '(')
        {
            s[j] = '#';
            cnt--;
        }
        j--;
    }
    string ans;
    for (int i = 0; i < n; i++)
        if (s[i] != '#')
            ans.push_back(s[i]);
    return ans;
}

int minInsertions(string s)
{
    string t;
    int n = s.size(), ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ')')
        {
            if (i + 1 < n and s[i + 1] == ')')
                t.append(")"), i++;
            else
            {
                ans++;
                t.append(")");
            }
        }
        else
        {
            t.append("(");
        }
    }

    int cnt = 0;
    for (auto i : t)
    {
        if (i == '(')
            cnt++;
        else
            cnt--;

        if (cnt < 0)
        {
            cnt = 0;
            ans++;
        }
    }
    return ans + cnt;
}

class Solution
{
public:
    bool isValid(string &s)
    {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                cnt++;
            else if (s[i] == ')')
                cnt--;

            if (cnt < 0)
                return false;
        }
        return true;
    }
    void help(int idx, int LR, int RR, string &cur, set<string> &ans, string &s)
    {
        if (idx == s.size())
        {
            if (LR == 0 and RR == 0 and isValid(cur))
                ans.insert(cur);
            return;
        }

        if (s[idx] == '(' and LR)
        {
            // remove left bracket
            help(idx + 1, LR - 1, RR, cur, ans, s);
        }
        else if (s[idx] == ')' and RR)
        {
            // remove right bracket
            help(idx + 1, LR, RR - 1, cur, ans, s);
        }

        // do not remove
        cur.push_back(s[idx]);
        help(idx + 1, LR, RR, cur, ans, s);
        cur.pop_back();
    }
    
    vector<string> removeInvalidParentheses(string s)
    {
        int n = s.size(), cnt = 0, RightRemoved = 0, LeftRemoved = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
                cnt++;
            else if (s[i] == ')')
                cnt--;

            if (cnt < 0)
            {
                RightRemoved++;
                cnt = 0;
            }
        }

        int j = n - 1;
        while (j >= 0 and cnt)
        {
            if (s[j] == '(')
            {
                LeftRemoved++;
                cnt--;
            }
            j--;
        }

        set<string> ans;
        string cur;
        help(0, LeftRemoved, RightRemoved, cur, ans, s);
        return vector<string>(ans.begin(), ans.end());
    }
};

int main()
{
    int t = 1;
    while (t--)
    {
        string s;
        cin >> s;
        Solution ans;

        for (auto i : ans.removeInvalidParentheses(s))
            cout << i << ' ';
        cout << endl;
    }
}
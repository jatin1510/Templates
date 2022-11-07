#include <bits/stdc++.h>
using namespace std;

// (1+2*3/(1+2))
bool isoperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '/' || ch == '*';
}

int precedence(char ch1)
{
    if (ch1 == '/' || ch == '*')
        return 2;

    if (ch == '-' || ch == '+')
        return 1;

    return 0;
}

int func(string s)
{
    // convert into postfix
    


    //
    int n = s.size();
    stack<char> ops, nums;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            ops.push(s[i]);
        }
        else if (s[i] == ')')
        {
        }
        else if (isoperator(s[i]))
        {
            if (!ops.empty())
            {
                while (precedence(s[i]) > precedence(ops.top()))
                {
                    int a = nums.top();
                    nums.pop();
                    int b = nums.top();
                    nums.pop();

                    if (ops.top() == '/')
                        ans += a / b;
                    else if (ops.top() == '+')
                        ans += a + b;
                    else if (ops.top() == '-')
                        ans += (a - b);
                    else
                        ans += (a * b);

                    ops.pop();
                }
            }
            else
            {
                ops.push(s[i]);
            }
        }
        else
        {
            nums.push(s[i]);
        }
    }
}

int32_t main()
{

    return 0;
}
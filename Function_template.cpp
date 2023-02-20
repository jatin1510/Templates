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

// functions
// Check whether given number is power of 2 or not
bool isPowerOfTwo(int n)
{
    return __builtin_popcountll(n) == 1;
}
// Check whether given number is prime or not
bool isprime(int n)
{
    if (n == 1)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

// Check whether given string is palindrome or not
bool isPalindrome(string s)
{
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
        if (s[i] != s[n - 1 - i])
            return false;
    return true;
}

// Optimal function for powering a number with/without modulo
// more on https://cp-algorithms.com/algebra/binary-exp.html
int binpow(int a, int b, int m = (1e18))
{
    a %= m;
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Linear combination of gcd(a, b) = a * x + b * y
// more on https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
int GCD_Recursive(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = GCD_Recursive(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int GCD_Iterative(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

// nth and (n+1)th fibonacci numbers in Theta(log(n)) - Fast Doubling Method
// more on https://cp-algorithms.com/algebra/fibonacci-numbers.html
pair<int, int> fib(int n)
{
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    int c = p.first * (2 * p.second - p.first);
    int d = p.first * p.first + p.second * p.second;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}

// all about prime numbers {Sieve of Eratosthenes}
// more on https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
int count_primes(int n)
{
    const int S = 10000;

    // generate all prime numbers till S in vector primes
    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    // return count of prime numbers till n
    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++)
    {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes)
        {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++)
        {
            if (block[i])
                result++;
        }
    }
    return result;
}

// generate all prime number between L to R
vector<bool> segmentedSieve(int L, int R)
{
    // generate all primes up to sqrt(R)
    int lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<int> primes;
    for (int i = 2; i <= lim; ++i)
    {
        if (!mark[i])
        {
            primes.emplace_back(i);
            for (int j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (int i : primes)
        for (int j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}

template <class T>
inline bool chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}

// KMP algorithm
// Better that i have understood from other source
// https://youtu.be/nJbNe0Yzjhw
vector<int> lpsArray(string s)
{
    int n = s.size();
    vector<int> lps(n);
    lps[0] = 0;
    int l;
    for (int i = 1; i < n; i++)
    {
        l = lps[i - 1];

        while (l > 0 && s[i] != s[l])
            l = lps[l - 1];

        if (s[i] == s[l])
            ++l;

        lps[i] = l;
    }
    return lps;
}

// https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
void computeLPSArray(string pat, int M, vector<int> &lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    vector<int> lps(M);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

int xgcd(int a, int b, int &x, int &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = xgcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int modular_inverse(int a, int m)
{
    int x, y;
    int g = xgcd(a, m, x, y);
    if (g != 1)
        return -1;
    else
    {
        x = (x % m + m) % m;
        return x;
    }
}

// const int N = 5;
// int fact[N];
// void factorials()
// {
//     fact[0] = 1;
//     for (int i = 1; i <= N; i++)
//         fact[i] = (fact[i - 1] * i) % mod;
// }

// int nCr(int n, int r)
// {
//     return fact[n] * modular_inverse(fact[r], mod) % mod * modular_inverse(fact[n - r], mod) % mod;
// }

int isDivisibleBy7(int num)
{
    // If number is negative, make it positive
    if (num < 0)
        return isDivisibleBy7(-num);

    // Base cases
    if (num == 0 || num == 7)
        return 1;
    if (num < 10)
        return 0;

    // Recur for ( num / 10 - 2 * num % 10 )
    return isDivisibleBy7(num / 10 - 2 * (num - num / 10 * 10));
}

// give vector as output whose sum is "sum" from natural numbers
vector<int> giveSumArray(int sum)
{
    vector<int> ans;
    int element = 1;
    int s = 0;
    while (s < sum)
    {
        ans.push_back(element);
        s += (element++);
    }

    if (s > sum)
    {
        int remove = s - sum;
        ans.erase(find(all(ans), remove));
    }
    return ans;
}

// give bit length of given 32 bit number, e.g, for 5 = 101 = 3 bits-0
int bit_length_of_decimalNumber(int num)
{
    return sizeof(num) * 8 - __builtin_clz(num);
}

// Currently MAX queue
class MinMaxQueue
{
public:
    queue<int> Q;
    deque<int> D;
    void push(int element)
    {
        if (Q.size() == 0)
        {
            Q.push(element);
            D.push_back(element);
        }
        else
        {
            Q.push(element);
            // change less than to greater than if we want min queue
            while (!D.empty() && D.back() < element)
                D.pop_back();
            D.push_back(element);
        }
    }
    void pop()
    {
        if (Q.front() == D.front())
        {
            Q.pop();
            D.pop_front();
        }
        else
        {
            Q.pop();
        }
    }
    int getMax()
    {
        return D.front();
    }

    bool empty()
    {
        return Q.empty();
    }

    int front()
    {
        return Q.front();
    }
};

// grid minimum from (0,0) to (m-1,n-1)
int minimumObstacles(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    auto isvalid = [&](int i, int j) -> bool
    {
        return 0 <= i and i < m and 0 <= j and j < n;
    };

    // RLDU
    // 1234
    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};

    vector<vector<int>> cost(m, vector<int>(n, 1e6));

    cost[0][0] = 0;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    pq.push({0, {0, 0}});

    while (!pq.empty())
    {
        int c = pq.top().first;
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k];
            int y = j + dy[k];

            int nexthop = grid[i][j];

            if (isvalid(x, y) and cost[i][j] + nexthop < cost[x][y])
                pq.push({cost[x][y] = cost[i][j] + nexthop, {x, y}});
        }
    }

    return cost[m - 1][n - 1];
}

int flip(int n, int i)
{
    return (n ^ (1ll << i));
}

// Given a list of values, finds the minimum total amount of movement needed to make them all equal.
template <typename T_out, typename T_in>
T_out min_equal_distance(vector<T_in> values)
{
    if (values.empty())
        return 0;

    int n = int(values.size());
    nth_element(values.begin(), values.begin() + n / 2, values.end());
    T_in median = values[n / 2];
    T_out total = 0;

    for (T_in x : values)
        total += abs(x - median);

    return total;
}

// Given a list of values, finds the minimum total amount of movement to make them contiguous (x, x + 1, x + 2, ...).
template <typename T_out, typename T_in>
T_out min_contiguous_distance(vector<T_in> values)
{
    if (!is_sorted(values.begin(), values.end()))
        sort(values.begin(), values.end());

    for (int i = 0; i < int(values.size()); i++)
        values[i] -= i;

    return min_equal_distance<T_out>(values);
}

int32_t main()
{

    return 0;
}
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
template <typename T>
void print(const vector<T> &v)
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
#define PI (4 * atan(1))
#define int ll
#define all(v) (v).begin(), (v).end()
#define allr(v) (v).rbegin(), (v).rend()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define modulo (int)1e9 + 7

template <int MOD = modulo>
struct mint
{
    int value;
    static const int MOD_value = MOD;

    mint(long long v = 0)
    {
        value = v % MOD;
        if (value < 0)
            value += MOD;
    }
    mint(long long a, long long b) : value(0)
    {
        *this += a;
        *this /= b;
    }

    mint &operator+=(mint const &b)
    {
        value += b.value;
        if (value >= MOD)
            value -= MOD;
        return *this;
    }
    mint &operator-=(mint const &b)
    {
        value -= b.value;
        if (value < 0)
            value += MOD;
        return *this;
    }
    mint &operator*=(mint const &b)
    {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend mint mexp(mint a, long long e)
    {
        mint res = 1;
        while (e)
        {
            if (e & 1)
                res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend mint inverse(mint a) { return mexp(a, MOD - 2); }

    mint &operator/=(mint const &b) { return *this *= inverse(b); }
    friend mint operator+(mint a, mint const b) { return a += b; }
    friend mint operator+(mint const a) { return 0 + a; }
    friend mint operator-(mint a, mint const b) { return a -= b; }
    friend mint operator-(mint const a) { return 0 - a; }
    friend mint operator*(mint a, mint const b) { return a *= b; }
    friend mint operator/(mint a, mint const b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &os, mint const &a) { return os << a.value; }
    friend bool operator==(mint const &a, mint const &b) { return a.value == b.value; }
    friend bool operator==(mint const &a, int const &b) { return a.value == b; }
    friend bool operator!=(mint const &a, mint const &b) { return a.value != b.value; }
};

vector<double> piper = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

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

// 1
string encode_shift_cipher(string s, int key)
{
    char ch = 'a';
    if (s[0] >= 'A' and s[0] <= 'Z')
        ch = 'A';

    int n = s.size(), mod = 26;
    string ans;
    for (auto i : s)
        ans.push_back(char(ch + ((i - ch + key) % mod + mod) % mod));
    return ans;
}

string decode_shift_cipher(string s, int key)
{
    char ch = 'a';
    if (s[0] >= 'A' and s[0] <= 'Z')
        ch = 'A';

    int n = s.size(), mod = 26;
    string ans;
    for (auto i : s)
        ans.push_back(char(ch + ((i - ch - key) % mod + mod) % mod));
    return ans;
}

string autokey_cipher(string s, int key)
{
    int n = s.size(), mod = 26;
    string ans;
    for (int i = 0; i < n; i++)
    {
        ans.push_back(char('A' + ((((s[i] - 'A') - key) % mod) + mod) % mod));
        key = ((((s[i] - 'A') - key) % mod) + mod) % mod;
    }
    return ans;
}

string hill_cipher(string s, vector<vector<int>> key)
{
    // key = {{a, b}, {c, d}}
    int n = s.size(), mod = 26;
    string ans;
    for (int i = 0; i < n; i += 2)
    {
        int a = s[i] - 'A', b = s[i + 1] - 'A';
        int c = (key[0][0] * a + key[0][1] * b) % mod;
        int d = (key[1][0] * a + key[1][1] * b) % mod;
        ans.push_back(char('A' + c));
        ans.push_back(char('A' + d));
    }
    return ans;
}

void periodic_stream_cipher(vector<int> v, int till)
{
    int m = v.size();
    int mx = (1 << m) - 1;

    int x = 0;
    for (int i = 0; i < till; i++)
        x ^= v[i];

    for (int i = m + 1; i <= mx; i++)
    {
        v.push_back(x);
        x ^= v[i - m - 1];
        x ^= v[i - m + 1];
    }

    print(v);
}
string XOR(string s, string t)
{
    string ans;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == t[i])
            ans.push_back('0');
        else
            ans.push_back('1');
    }
    return ans;
}

void SPN(string K, string x, vector<int> s, vector<int> p, int l, int m, int round)
{
    vector<string> keys;
    for (int i = 0; i < K.size(); i += l)
        keys.push_back(K.substr(i, l * m));

    auto convToBitStream = [&](int i)
    {
        string str = bitset<32>(i).to_string();
        str = str.substr(32 - l);
        return str;
    };

    unordered_map<string, int> mp;
    for (int i = 0; i < s.size(); i++)
    {
        string str = convToBitStream(i);
        mp[str] = i;
    }

    auto sbox = [&](string v)
    {
        int idx = s[mp[v]];
        return convToBitStream(idx);
    };

    string w = x;
    string v;
    for (int r = 0; r < round; r++)
    {
        string k = keys[r];
        string u = XOR(w, k);

        if (r == round - 1)
        {
            string y = XOR(v, k);

            print("y", y);
            break;
        }

        print("w", w);
        print("k", k);
        print("u", u);

        v.clear();
        for (int i = 0; i < u.size(); i += l)
        {
            string num = u.substr(i, l);
            v.append(sbox(num));
        }

        print("v", v);

        for (int i = 0; i < p.size(); i++)
            w[i] = v[p[i] - 1];

        print('\n');
    }

    // auto convToBitStream = [&](int i)
    // {
    //     string str = bitset<32>(i).to_string();
    //     str = str.substr(28);
    //     return str;
    // };

    // unordered_map<string, int> mp;
    // for (int i = 0; i < 15; i++)
    // {
    //     string str = convToBitStream(i);
    //     mp[str] = i;
    // }

    // auto sbox = [&](string v)
    // {
    //     int idx = s[mp[v]];
    //     return convToBitStream(idx);
    // };

    // string w = x;
    // string v;
    // for (int r = 0; r < 5; r++)
    // {
    //     string k = keys[r];
    //     string u = XOR(w, k);

    //     if (r == 4)
    //     {
    //         string y = XOR(v, k);

    //         print("y", y);
    //         break;
    //     }

    //     print("w", w);
    //     print("k", k);
    //     print("u", u);

    //     v.clear();
    //     for (int i = 0; i < u.size(); i += 4)
    //     {
    //         string num = u.substr(i, 4);
    //         v.append(sbox(num));
    //     }

    //     print("v", v);

    //     for (int i = 0; i < p.size(); i++)
    //         w[i] = v[p[i] - 1];

    //     print('\n');
    // }
}

void linear_approximation_table()
{
    // Linear approaximation
    vector<string> v = {"00001110",
                        "00010100",
                        "00101101",
                        "00110001",
                        "01000010",
                        "01011111",
                        "01101011",
                        "01111000",
                        "10000011",
                        "10011010",
                        "10100110",
                        "10111100",
                        "11000101",
                        "11011001",
                        "11100000",
                        "11110111"};

    auto convert = [&](int i)
    {
        string str = bitset<32>(i).to_string();
        str = str.substr(28);
        return str;
    };

    vector<vector<int>> ans;
    for (int a = 0; a < 16; a++)
    {
        vector<int> local;
        for (int b = 0; b < 16; b++)
        {
            string s = convert(a); // x
            string t = convert(b); // y

            int cnt = 0;
            for (int i = 0; i < v.size(); i++)
            {
                int x = 0;
                for (int j = 0; j < 4; j++)
                {
                    if (s[j] == '1')
                    {
                        x ^= (v[i][j] - '0');
                    }
                }
                for (int j = 0; j < 4; j++)
                {
                    if (t[j] == '1')
                    {
                        x ^= (v[i][4 + j] - '0');
                    }
                }

                if (x == 0)
                    cnt++;
            }
            local.push_back(cnt);
        }
        ans.push_back(local);
    }

    for (auto i : ans)
    {
        for (auto j : i)
            cout << j << ' ';
        cout << endl;
    }
}
double entropy(vector<double> p)
{
    double h = 0;
    for (auto prob : p)
        if (prob != 0)
            h += -prob * log2(prob);
    return h;
}

string encode_vigenere_cipher(string p, string key)
{
    char ch = 'a';
    if (key[0] >= 'A' and key[0] <= 'Z')
        ch = 'A';

    vector<int> k;
    for (auto i : key)
        k.push_back(i - ch);

    int idx = 0;
    string ans;
    for (int i = 0; i < p.size(); i++)
    {
        mint<26> num = (p[i] - ch) + k[idx++];
        idx %= k.size();
        ans.push_back(ch + num.value);
    }
    return ans;
}

void cryptanalysis_vigenere_cipher(string cipher, int m)
{
    int n = cipher.size();
    vector<string> v;
    for (int i = 0; i < m; i++)
    {
        string s;
        for (int j = i; j < n; j += m)
            s.push_back(cipher[j]);
        v.push_back(s);
    }

    int ndesh = n / m;

    cout << fixed << setprecision(3);
    for (auto s : v)
    {
        unordered_map<char, int> mp;
        for (auto i : s)
            mp[i]++;

        double ans = 0;
        for (char ch = 'A'; ch <= 'Z'; ch++)
        {
            int f = mp[ch];
            ans += f * (f - 1);
        }

        int n = s.size();
        ans /= (1.0 * n * (n - 1.0));

        print(ans);

        // for (int g = 0; g < 26; g++)
        // {
        //     double mg = 0;
        //     for (int i = 0; i < 26; i++)
        //     {
        //         mg += (piper[i] * mp[((i + g) % 26) + 'A'] / ndesh);
        //     }
        //     cout << mg << ' ';
        // }
        // cout << endl;
    }
}

int32_t main()
{
    // SPN
    // string K = "00111010100101001101011000111111";
    // string x = "0010011010110111";
    // vector<int> p = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    // vector<int> s = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
    // int l = 4, m = 4, round = 5;
    // SPN(K, x, s, p, l, m, round);

    // Linear approximation
    // linear_approximation_table();

    // string cipher = "BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD";
    // for (int k = 0; k < 26; k++)
    //     print(k, decode_shift_cipher(cipher, k));

    // int m;
    // cin >> m;

    // for (int i = 0; i < m; i++)
    //     if(gcd(i, m) == 1)
    //         cout << i << ' ';
    // cout << endl;

    // string cipher = "TGEEMNELNNTDROEOAAHDOETCSHAEIRLM";
    // vector<int> p = {4, 1, 6, 2, 7, 3, 8, 5};
    // vector<int> p = {2, 4, 6, 1, 8, 3, 5, 7};

    // string ans;
    // for (int i = 0; i < cipher.size(); i += p.size())
    // {
    //     string s = cipher.substr(i, p.size());
    //     string t = s;
    //     for (int j = 0; j < p.size(); j++)
    //         t[j] = s[p[j] - 1];
    //     cout << t << ' ';
    // }
    // cout << endl;

    // string cipher = "ZVRQHDUJIM";
    // for (int k = 0; k < 26; k++)
    //     print(k, autokey_cipher(cipher, k));

    // string cipher = "thiscryptosystemisnotsecure";
    // string key = "cipher";
    // print(encode_vigenere_cipher(cipher, key));

    // string cipher = "CHREEVOAHMAERATBIAXXWTNXBEEOPHBSBQMQEQERBWRVXUOAKXAOSXXWEAHBWGJMMQMNKGRFVGXWTRZXWIAKLXFPSKAUTEMNDCMGTSXMXBTUIADNGMGPSRELXNJELXVRVPRTULHDNQWTWDTYGBPHXTFALJHASVBFXNGLLCHRZBWELEKMSJIKNBHWRJGNMGJSGLXFEYPHAGNRBIEQJTAMRVLCRREMNDGLXRRIMGNSNRWCHRQHAEYEVTAQEBBIPEEWEVKAKOEWADREMXMTBHHCHRTKDNVRZCHRCLQOHPWQAIIWXNRMGWOIIFKEE";
    // int m = 5;
    // cryptanalysis_vigenere_cipher(cipher, m);

    // vector<double> p = {1 / 2.0, 1 / 4.0, 1 / 4.0};
    // print(entropy(p));

    string cipher = "XYGROBO";
    for (int k = 0; k < 26; k++)
        print(k, decode_shift_cipher(cipher, k));

    return 0;
}
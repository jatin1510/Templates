#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
#define int ll

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
#define all(v) (v).begin(), (v).end()
#define endl '\n'
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// User implemented functions
int32_t main()
{
    vector<int> games = {2703111, 7033660, 3995359, 8268922, 4041448, 5259212, 5985813, 9477953, 3371429, 9004427, 7654128, 5721231, 5597123, 3450042, 6157385, 2597100, 6071376, 5246630, 4320888, 4506073, 8988447, 8382609, 3891321, 8776164, 9497148, 5939307, 3875076, 4866289, 1441196, 4452771, 2086027, 2282682, 4167000, 6443957, 2508160, 4259204, 9029459, 3648847, 4426120, 3641660, 7453335, 5043846, 6582019, 7889575, 3077061, 2579290, 5668080, 7881760, 6462829, 2247901, 7511958, 4772474, 4751323, 9460800, 2962301, 4050927, 1298072, 5185229, 5894396, 8886656, 5311927, 9751310, 3373576, 6400425, 8238328, 1878655, 6534405, 9361122, 1397557, 1062915, 9062725, 7553617, 9151145, 9914142, 8476158, 7861589, 9860147, 7637254, 1592710, 6389310, 7478631, 1313183, 9863739, 3309688, 5230423, 8883629, 7749104, 2942030, 7670481, 2951627, 8037209, 6463010, 8306584, 8518097, 5960071, 6619482, 8367901, 4972310, 1228990, 5905692};

    vector<int> tags = {444851, 185291, 911414, 550564, 780507, 406467, 119123, 262260, 865020, 280511, 793374, 965014, 539378, 185703, 931586, 439672, 976585, 551113, 495929, 427546, 984448, 608112, 654575, 985900, 387803, 543429, 209856, 783081, 961269, 779001, 753360, 911319, 450590, 522298, 419715, 510794, 132499, 435045, 848469, 329299, 975665, 365210, 167098, 275637, 738046, 951543, 392513, 863469, 761271, 946285, 953301, 886140, 160173, 162564, 758398, 106949, 455975, 457168, 873684, 640615, 699514, 169735, 763573, 910677, 367475, 962204, 718898, 681084, 914775, 643080, 642010, 822051, 119736, 273649, 865684, 146477, 125594, 589745, 652505, 157680, 988738, 212085, 790180, 610441, 425946, 165359, 669215, 418783, 199667, 931813, 693716, 624560, 271153, 807238, 333968, 546570, 741329, 879342, 492100, 407684};

    vector<int> achievement = {79325073, 81690514, 11503762, 65691764, 57774793, 77900232, 19064329, 74909588, 56104067, 90986544, 90634234, 59684928, 73052340, 44322209, 92880419, 19341416, 84692895, 89483320, 45007206, 79968953, 51806809, 70704774, 52377928, 24151449, 52837428, 55268900, 24171342, 24763213, 91782951, 18924498, 37835022, 61475466, 23452650, 68247961, 46612242, 87561990, 66530710, 71748961, 63782004, 51887879, 13255799, 25135141, 42114765, 31340089, 10779317, 79764646, 89964761, 91176720, 63945477, 90086231, 23937084, 13895614, 17433638, 50635401, 37254273, 14465104, 79543367, 94954592, 46464044, 16459353, 51564167, 29982434, 54869535, 29815985, 30884602, 33229655, 54437505, 74164744, 98062231, 34443706, 51206714, 89307327, 80411046, 31783265, 90256328, 81083948, 82697064, 90993521, 72856106, 32022685, 39243697, 78354189, 67581559, 55585097, 64430813, 56127272, 12865719, 92417757, 70813384, 59376935, 12510488, 75138972, 35617036, 28385950, 82214432, 68748588, 88253795, 30205116, 63988176, 31358703};

    vector<int> upcoming_games = {9166969, 4539274, 8754211, 1293068, 1517163, 8544499, 2898836, 7073893, 4753686, 6746101};

    vector<string> player = {"YmNCM", "QhxmA", "r8ayt", "ZLxdU", "SEZQ3", "USi2r", "DQUvy", "PepUd", "pnZH4", "y0Krw", "chL2T", "dbW91", "yS9op", "PUbgm", "IwwWr", "TRuLC", "VAKto", "oFTCq", "gDsZ6", "f5PtQ", "httOy", "2loX3", "hmRg1", "b3750", "kIN8C", "5zSIi", "afXGa", "trtCL", "TwpZ5", "WzHEY", "wCxdN", "XQZeR", "Yc7b3", "W7U0e", "DUPk6", "gxoTb", "HtbyN", "ofba1", "W0fOX", "TkZe3", "cTTjD", "klsFH", "LQVPM", "P1poP", "9j8Om", "IKsQV", "8ciNW", "LPdNF", "VqYjE", "JpEoH", "8TOCZ", "zHJfa", "kQbfC", "g52yS", "S8NEH", "sBGvn", "alJzi", "rud0W", "9HcSW", "zhomz", "1SM01", "wJeJg", "EiWwu", "lYqU3", "Vub8p", "jV3DK", "jpfm0", "pCFqe", "P9zFE", "jK1Ve", "KsCZV", "EO3s0", "gRew3", "U0rFl", "KQAuE", "yfvgQ", "Ge4Kz", "trHRu", "s6wR8", "MplRI", "ioVkv", "dQSAQ", "hPbuB", "AkgCj", "uk3MS", "pmrVs", "OnFkm", "8eQzb", "WLbhC", "cE90g", "k9V5M", "8kqdR", "JUeSu", "VlRsS", "mbK3l", "p9QNG", "MWE5m", "bPImg", "jX3Sb", "wV8aB"};

    vector<int> employee = {8483, 4766, 3991, 9586, 6755, 4664, 3357, 3568, 9078, 1766, 9837, 2416, 7442, 6336, 2169, 4466, 9517, 5310, 6257, 9551};

    vector<int> card_number = {5439642262971517, 5348567391324744, 5455232277744131, 5010120251860931, 5475580901905261, 5048375995341855, 5100138844497053, 5100170614095122, 5109140481625682, 5551375704588142, 5002359542119836, 5048374461367932, 5173548206776559, 5451717352378162, 5100171142963021, 5100132165629196, 5558633654542235, 5100146063928948, 5108757636704723, 5007660206602371, 5136869588782502, 5517069058917428, 5010124945434301, 5108751510582438, 5407575918356683, 5338416773273669, 5002351435962851, 5010128472698212, 5108752970628075, 5114161868771801, 5108759763116242, 5108756330360287, 5002350349025318, 5402362538636678, 5108759641168746, 5048379955365581, 5586378918001752, 5590179221487017, 5398051062163045, 5100174747652239, 5114650592272714, 5100179413820424, 5002355836257324, 5116599032783111, 5100149836032378, 5300978757238749, 5108756130776328, 5108755881594591, 5345669316236145, 5048376135729496, 5100175161735855, 5160334169408571, 5007667751711647, 5100133205820225, 5100142362627273, 5048370816896682, 5108758255359179, 5007660310236982, 5543515768352593, 5205796044291222, 5100134133768585, 5379911340389611, 5150168012766012, 5048379945318195, 5007669909732335, 5299523777073248, 5002355216362892, 5258945505192926, 5100144160834143, 5536681652848663, 5414357447656698, 5002352497751208, 5100149579736061, 5552568560629047, 5100148805904311, 5007668941082352, 5100142907328197, 5576903143985743, 5100148256293494, 5007669063383628, 5425405340437026, 5007661975567539, 5295676453990525, 5100133154909896, 5002355631458531, 5007666068727114, 5007664901701586, 5108657657854136, 5153355951386186, 5048370705258721, 5100144530820806, 5100135452842877, 5188474211505672, 5048371727109496, 5048375883069923, 5010121814847498, 5169581679556279, 5301417757138558, 5100130459663228, 5100136791314149};

    vector<int> developer = {31256, 54317, 94808, 32167, 99820, 29015, 82252, 42327, 91834, 31782, 83990, 27659, 75278, 44949, 42180, 92202, 45046, 56839, 64474, 90259, 16508, 88274, 60697, 56165, 46100, 65383, 81412, 22017, 25273, 13459};

    // for (int i = 0; i < 25; i++)
    // {
    //     cout << employee[getRand(1, 20) - 1] << '\n';
    // }

    // vector<vector<int>> v;
    // for (auto game_id : games)
    // {
    //     int sz = getRand(1, 3);
    //     unordered_map<int, int> mp;
    //     while (mp.size() != sz)
    //     {
    //         int id = tags[getRand(1, 100) - 1];
    //         mp[id]++;
    //     }

    //     for (auto i : mp)
    //         v.push_back({game_id, i.first});
    // }

    // print(v.size());
    // for (auto i : v)
    //     cout << i[0] << '\n';
    // cout << endl;
    // cout << endl;
    // for (auto i : v)
    //     cout << i[1] << '\n';
    // cout << endl;

    // int sz = 25;
    // unordered_map<int, int> mp;
    // while (mp.size() != sz)
    // {
    //     int id = games[getRand(1, 100) - 1];
    //     mp[id]++;
    // }

    // for (auto i : mp)
    //     cout << i.first << '\n';
    // cout << endl;

    // print("size", mp.size());

    // map<pair<string, string>, int> mp;
    // map<pair<string, string>, int> mp1;
    // while (mp.size() != 100)
    // {
    //     string id1 = player[getRand(1, 100) - 1];
    //     string id2 = player[getRand(1, 100) - 1];

    //     if (id1 != id2)
    //     {
    //         if (mp.find({id1, id2}) == mp.end() and mp1.find({id2, id1}) == mp1.end())
    //         {
    //             mp[{id1, id2}] = 1;
    //             // adding

    //             mp1[{id2, id1}] = 1;

    //         }
    //     }
    // }

    // for (auto i : mp)
    // {
    //     cout << i.first.first << '\n';
    // }

    // cout << endl;
    // cout << endl;
    // for (auto i : mp)
    // {
    //     cout << i.first.second << '\n';
    // }

    // cout << endl;

    // upcoming game id = 7 excluded
    // vector<pair<int, string>> v;
    // for (int i = 0; i < 10; i++)
    // {
    //     int game_id = upcoming_games[i];
    //     if (i != 6)
    //     {
    //         int sz = getRand(1, 20);
    //         unordered_map<string, int> mp;
    //         while (mp.size() != sz)
    //         {
    //             string player_id = player[getRand(1, 100) - 1];
    //             mp[player_id]++;
    //         }

    //         for (auto el : mp)
    //         {
    //             v.push_back({game_id, el.first});
    //         }
    //     }
    // }

    // print(v.size());
    // for (auto i : v)
    // {
    //     print(i.second);
    // }
    // cout << endl;

    // for (auto i : v)
    // {
    //     print(i.first);
    // }
    // cout << endl;

    // achieves
    // int sz = 100;
    // map<pair<int, string>, int> mp;
    // while (mp.size() != sz)
    // {
    //     int achv_id = achievement[getRand(1, 100) - 1];
    //     string player_id = player[getRand(1, 100) - 1];

    //     if (mp.find({achv_id, player_id}) == mp.end())
    //     {
    //         mp[{achv_id, player_id}] = 1;
    //     }
    // }

    // for (auto i : mp)
    // {
    //     cout << i.first.first << '\n';
    // }
    // cout << endl;
    // cout << endl;
    // for (auto i : mp)
    // {
    //     cout << i.first.second << '\n';
    // }
    // cout << endl;

    // for (int i = 0; i < 100; i++)
    // {
    //     cout << player[getRand(1, 100) - 1] << '\n';
    // }

    // -- phone no
    // vector<pair<string, int>> v;
    // int cnt = 0;
    // for (int i = 0; i < 100; i++)
    // {
    //     int sz = getRand(1, 3);
    //     while (sz--)
    //         cout << player[i] << '\n';
    // }
    // cout << endl;

    // ph_no
    // unordered_map<int, int> mp;
    // while (mp.size() != 203)
    // {
    //     mp[getRand(1000000000, 9999999999)]++;
    // }

    // for(auto i : mp)
    //     cout << i.first << '\n';

    // system support
    // vector<pair<int, string>> v;
    // vector<string> systems = {"Mac OS", "Windows 8", "Ubuntu", "Windows 10", "Linux"};
    // for (int i = 0; i < 100; i++)
    // {
    //     int sz = getRand(1, 5);
    //     unordered_map<string, int> mp;
    //     while (mp.size() != sz)
    //     {
    //         string sys = systems[getRand(1, 5) - 1];
    //         mp[sys]++;
    //     }

    //     for (auto el : mp)
    //         v.push_back({games[i], el.first});
    // }

    // print(v.size());
    // for (auto i : v)
    //     cout << i.first << '\n';
    // cout << endl;
    // cout << endl;
    // for (auto i : v)
    //     cout << i.second << '\n';
    // cout << endl;

    // reviwes
    // map<pair<string, int>, int> mp;
    // while (mp.size() != 100)
    // {
    //     string id1 = player[getRand(1, 100) - 1];
    //     int id2 = games[getRand(1, 100) - 1];

    //     if (mp.find({id1, id2}) == mp.end())
    //         mp[{id1, id2}] = 1;
    // }

    // for (auto i : mp)
    //     cout << i.first.first << '\n';
    // cout << endl;
    // cout << endl;
    // for (auto i : mp)
    //     cout << i.first.second << '\n';
    // cout << endl;

    // tournament
    // unordered_map<int, int> mp;
    // while (mp.size() != 40)
    // {
    //     mp[games[getRand(1, 100) - 1]]++;
    // }
    // for (auto i : mp)
    //     cout << i.first << '\n';
    // cout << endl;

    // purchase
    // map<pair<int, string>, int> mp;
    // while (mp.size() != 100)
    // {
    //     int game_id = games[getRand(1, 100) - 1];
    //     string player_id = player[getRand(1, 100) - 1];

    //     if (mp.find({game_id, player_id}) == mp.end())
    //         mp[{game_id, player_id}] = 1;
    // }

    // for (auto i : mp)
    //     cout << i.first.first << '\n';
    // cout << endl;
    // cout << endl;
    // for (auto i : mp)
    //     cout << i.first.second << '\n';
    // cout << endl;
    // cout << endl;

    // Purchase -- main
    // vector<string> players_idd = {"pmrVs", "SEZQ3", "IwwWr", "W7U0e", "b3750", "8ciNW", "yS9op", "TRuLC", "8TOCZ", "VAKto", "lYqU3", "zHJfa", "g52yS", "dbW91", "wCxdN", "Ge4Kz", "ioVkv", "dQSAQ", "gxoTb", "LQVPM", "jX3Sb", "jpfm0", "oFTCq", "hPbuB", "Yc7b3", "PUbgm", "8TOCZ", "VAKto", "IwwWr", "zHJfa", "wCxdN", "P9zFE", "8TOCZ", "VlRsS", "YmNCM", "LPdNF", "gDsZ6", "r8ayt", "rud0W", "jX3Sb", "rud0W", "r8ayt", "W0fOX", "bPImg", "TRuLC", "1SM01", "W0fOX", "8TOCZ", "kIN8C", "JUeSu", "b3750", "gDsZ6", "hmRg1", "TwpZ5", "TRuLC", "PUbgm", "b3750", "ZLxdU", "8eQzb", "8TOCZ", "alJzi", "VqYjE", "pCFqe", "kQbfC", "P9zFE", "s6wR8", "yS9op", "1SM01", "Yc7b3", "oFTCq", "rud0W", "yS9op", "y0Krw", "W7U0e", "U0rFl", "TkZe3", "k9V5M", "P9zFE", "rud0W", "mbK3l", "8ciNW", "QhxmA", "wJeJg", "cE90g", "MWE5m", "WLbhC", "IKsQV", "TkZe3", "MplRI", "MWE5m", "DQUvy", "LQVPM", "cE90g", "S8NEH", "AkgCj", "PUbgm", "8ciNW", "lYqU3", "pCFqe", "KQAuE"};

    // vector<int> dummy = {5439642262971517, 5348567391324744, 5455232277744131, 5010120251860931, 5475580901905261, 5048375995341855, 5100138844497053, 5100170614095122, 5109140481625682, 5551375704588142, 5002359542119836, 5048374461367932, 5173548206776559, 5451717352378162, 5100171142963021, 5100132165629196, 5558633654542235, 5100146063928948, 5108757636704723, 5007660206602371, 5136869588782502, 5517069058917428, 5010124945434301, 5108751510582438, 5407575918356683, 5338416773273669, 5002351435962851, 5010128472698212, 5108752970628075, 5114161868771801, 5108759763116242, 5108756330360287, 5002350349025318, 5402362538636678, 5108759641168746, 5048379955365581, 5586378918001752, 5590179221487017, 5398051062163045, 5100174747652239, 5114650592272714, 5100179413820424, 5002355836257324, 5116599032783111, 5100149836032378, 5300978757238749, 5108756130776328, 5108755881594591, 5345669316236145, 5048376135729496, 5100175161735855, 5160334169408571, 5007667751711647, 5100133205820225, 5100142362627273, 5048370816896682, 5108758255359179, 5007660310236982, 5543515768352593, 5205796044291222, 5100134133768585, 5379911340389611, 5150168012766012, 5048379945318195, 5007669909732335, 5299523777073248, 5002355216362892, 5258945505192926, 5100144160834143, 5536681652848663, 5414357447656698, 5002352497751208, 5100149579736061, 5552568560629047, 5100148805904311, 5007668941082352, 5100142907328197, 5576903143985743, 5100148256293494, 5007669063383628, 5425405340437026, 5007661975567539, 5295676453990525, 5100133154909896, 5002355631458531, 5007666068727114, 5007664901701586, 5108657657854136, 5153355951386186, 5048370705258721, 5100144530820806, 5100135452842877, 5188474211505672, 5048371727109496, 5048375883069923, 5010121814847498, 5169581679556279, 5301417757138558, 5100130459663228, 5100136791314149};
    // unordered_map<string, vector<int>> mp;
    // for (int i = 0; i < 100; i++)
    // {
    //     mp[players_idd[i]].push_back(dummy[i]);
    // }

    // vector<string> pl = {"EiWwu", "EiWwu", "jX3Sb", "klsFH", "JpEoH", "oFTCq", "XQZeR", "MplRI", "jpfm0", "KsCZV", "TRuLC", "Vub8p", "chL2T", "wJeJg", "2loX3", "IKsQV", "YmNCM", "Yc7b3", "IwwWr", "bPImg", "jV3DK", "kQbfC", "IKsQV", "VqYjE", "IKsQV", "LQVPM", "WzHEY", "afXGa", "JUeSu", "KQAuE", "f5PtQ", "8ciNW", "cTTjD", "gxoTb", "jV3DK", "zhomz", "PUbgm", "sBGvn", "hPbuB", "yfvgQ", "S8NEH", "bPImg", "sBGvn", "cE90g", "kQbfC", "hmRg1", "lYqU3", "KsCZV", "ZLxdU", "cTTjD", "wV8aB", "jV3DK", "kQbfC", "sBGvn", "lYqU3", "ZLxdU", "Ge4Kz", "TkZe3", "JUeSu", "XQZeR", "DUPk6", "afXGa", "W7U0e", "XQZeR", "8eQzb", "trHRu", "PepUd", "dQSAQ", "zhomz", "HtbyN", "QhxmA", "alJzi", "mbK3l", "DUPk6", "HtbyN", "WzHEY", "ZLxdU", "wJeJg", "r8ayt", "Yc7b3", "JpEoH", "KQAuE", "bPImg", "VqYjE", "dQSAQ", "lYqU3", "sBGvn", "USi2r", "WzHEY", "9HcSW", "DQUvy", "cE90g", "yfvgQ", "KsCZV", "MplRI", "PUbgm", "s6wR8", "LPdNF", "ioVkv", "9j8Om"};

    // vector<string> uu = {"UPI", "Wallet"};
    // for (auto i : pl)
    // {
    //     vector<int> v = mp[i];
    //     if (v.size())
    //         cout << v[0] << '\n';
    //     else
    //     {
    //         cout << uu[getRand(0, 1)] << '\n';
    //     }
    // }

    // int sz = 30;
    // map<pair<int, int>, int> mp;

    // while (mp.size() != sz)
    // {
    //     int season = getRand(1, 5);
    //     int game_id = games[getRand(1, 100) - 1];

    //     if (mp.find({season, game_id}) == mp.end())
    //     {
    //         mp[{season, game_id}] = 1;
    //     }
    // }

    // for (auto i : mp)
    //     cout << i.first.first << '\n';
    // cout << endl;
    // cout << endl;
    // for (auto i : mp)
    //     cout << i.first.second << '\n';
    // cout << endl;
    // cout << endl;

    // for (int i = 0; i < sz; i++)
    // {
    //     print(employee[getRand(1, 20) - 1]);
    // }

    // for (int i = 0; i < 100; i++)
    // {
    //     cout << developer[getRand(1, 30) - 1] << '\n';
    // }

    vector<string> tables = {"Employee", "Player", "Manager", "Developer", "Tags", "Upcoming_Games", "Game", "Achievements", "Achieves", "Belongs_To", "Discount", "Friendship", "Payment_Card", "Phone_No", "Pre_Registers", "Purchase", "Reviews", "Season_Rewards", "Systems_Supported", "Tournament"};

    for (auto i : tables)
    {
        cout << "COPY \"video_game_db\".\"" << i << "\" FROM '/private/tmp/CSVs/" << i << ".csv' DELIMITER ',' NULL AS 'null' csv header;" << '\n';
        cout << "SELECT * FROM \"video_game_db\".\"" << i << "\";" << '\n';
        cout << endl;
    }
    return 0;
}
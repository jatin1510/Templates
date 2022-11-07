#include <bits/stdc++.h>

using namespace std;

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

const double alpha = 0.125;
const double beeta = 0.25;

double estimatedRTT;
double oldestimatedRTT;
double devRTT = 34.00;
double sampleRTT;

double copydevRTT;

double calcEstimateRTT()
{
    oldestimatedRTT = estimatedRTT;
    estimatedRTT = (1.00 - alpha) * estimatedRTT + alpha * sampleRTT;
    return estimatedRTT;
}

double calcDevRTT()
{
    return devRTT = (1.00 - beeta) * devRTT + beeta * abs(sampleRTT - oldestimatedRTT);
}

double timeout()
{
    return estimatedRTT + 4.00 * devRTT;
}

void setup()
{
    cout << fixed << setprecision(2);
    print("Estimated RTT", calcEstimateRTT());
    print("Dev RTT", calcDevRTT());
    print("timeout", timeout());
}

int32_t main()
{
    cout << "Initial Estimated RTT: ";
    cin >> estimatedRTT;
    cout << "Initial Dev RTT: ";
    cin >> devRTT;

    copydevRTT = devRTT;
    oldestimatedRTT = estimatedRTT;

    string c;
    while (1)
    {
        cout << "\nNew sample? (y/n): ";
        cin >> c;

        if (c == "Y" or c == "y" or c == "YES" or c == "Yes" or c == "yes")
        {
            cout << "Enter sample: ";
            cin >> sampleRTT;
        }
        else
        {
            break;
        }
        setup();
    }
    return 0;
}
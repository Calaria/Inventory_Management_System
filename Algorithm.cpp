// Algorithm.cpp
#include "Algorithm.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


void prompt_add_product(int &id, string &name, string &category, double &price, int &quantity)
{
    cout << "Enter ID: ";
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a number for ID: ";
    }
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter product category: ";
    getline(cin, category);
    cout << "Enter product price: $ ";
    while (!(cin >> price))
    {
        cout << "Invalid input. Please enter a number for price: ";
    }
    cout << "Enter product quantity: ";
    while (!(cin >> quantity))
    {
        cout << "Invalid input. Please enter a number for quantity: ";
    }
}
int common_sequence_length(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c)
              { return tolower(c); });
    transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c)
              { return tolower(c); });
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

int largest_common_sequence(string s, vector<string> choices)
{
    int len = 0;
    int idx = -1;
    for (int i = 1; i < choices.size(); i++)
    {
        int l = common_sequence_length(s, choices[i]);
        if (l > len)
        {
            len = l;
            idx = i;
        }
    }
        if (len < 4)
        {
            return 0;
        }
    return idx;
}

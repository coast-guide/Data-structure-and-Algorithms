#include <bits/stdc++.h>
using namespace std;

void lcsTable(string &s, string &t, vector<vector<int>> &dp)
{

    for (int s_ind = s.size(); s_ind >= 0; s_ind--)
    {
        for (int t_ind = t.size(); t_ind >= 0; t_ind--)
        {
            if (s_ind == s.size() || t_ind == t.size())
                dp[s_ind][t_ind] = 0;

            else if (s[s_ind] == t[t_ind])
                dp[s_ind][t_ind] = 1 + dp[s_ind + 1][t_ind + 1];

            else
                dp[s_ind][t_ind] = max(dp[s_ind][t_ind + 1], dp[s_ind + 1][t_ind]);
        }
    }
}
void printLCS(string &s, string &t)
{
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
    lcsTable(s, t, dp);

    string lcs;

    int i = 0, j = 0;

    while (i < s.size() && j < t.size())
    {
        if (s[i] == t[j])
        {
            lcs.push_back(s[i]);
            i++;
            j++;
        }
        else if (dp[i][j + 1] > dp[i + 1][j])
            j++;
        else
            i++;
    }

    cout << lcs << endl;
}

int main()
{
    string s, t;
    cin >> s >> t;

    printLCS(s, t);

    return 0;
}
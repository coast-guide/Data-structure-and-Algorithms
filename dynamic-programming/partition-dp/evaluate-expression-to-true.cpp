// https://www.interviewbit.com/problems/evaluate-expression-to-true/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll countWays(ll l, ll r, bool needTrue, const string &s, vector<vector<vector<ll>>> &dp)
{
    const ll mod = 1e3 + 3;
    if (l > r)
        return 0;

    if (l == r)
        if (needTrue)
            return (s[l] == 'T');
        else
            return (s[l] == 'F');

    if (dp[l][r][needTrue] != -1)
        return dp[l][r][needTrue];

    ll count = 0;
    for (ll i = l + 1; i <= r - 1; i += 2)
    {
        ll LT = countWays(l, i - 1, true, s, dp);
        ll LF = countWays(l, i - 1, false, s, dp);
        ll RT = countWays(i + 1, r, true, s, dp);
        ll RF = countWays(i + 1, r, false, s, dp);

        if (s[i] == '&')
            if (needTrue)
                count = (count + (LT * RT) % mod) % mod;
            else
                count = (count + ((LT * RF) % mod + (LF * RF) % mod + (LF * RT) % mod)) % mod;

        else if (s[i] == '|')
            if (needTrue)
                count = (count + ((LT * RT) % mod + (LT * RF) % mod + (LF * RT) % mod)) % mod;
            else
                count = (count + (LF * RF) % mod) % mod;

        else if (s[i] == '^')
            if (needTrue)
                count = (count + ((LT * RF) % mod + (LF * RT) % mod)) % mod;
            else
                count = (count + ((LT * RT) % mod + (LF * RF) % mod)) % mod;
    }

    return dp[l][r][needTrue] = count;
}

int cnttrue(string A)
{
    const int N = A.size();
    vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(N + 1, vector<ll>(2, -1)));
    return countWays(0, N - 1, true, A, dp);
}

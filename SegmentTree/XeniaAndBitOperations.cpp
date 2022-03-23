// problem link: https://codeforces.com/contest/339/problem/D

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define mp make_pair
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define PI 3.1415926535897932384626433832795l
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll powmod(ll a, ll b);

// -------------------------<RNG>-------------------------
// RANDOM NUMBER GENERATOR
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.

void build(ll arr[], ll seg[], ll low, ll high, ll ind, bool isOr)
{

    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }

    ll mid = low + (high - low) / 2;

    build(arr, seg, low, mid, 2 * ind + 1, !isOr);
    build(arr, seg, mid + 1, high, 2 * ind + 2, !isOr);

    if (isOr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

void update(ll seg[], ll ind, ll low, ll high, ll i, ll val, bool isOr)
{
    if (low == high)
    {
        seg[ind] = val;
        return;
    }

    ll mid = low + (high - low) / 2;
    if (i <= mid)
        update(seg, 2 * ind + 1, low, mid, i, val, !isOr);
    else
        update(seg, 2 * ind + 2, mid + 1, high, i, val, !isOr);

    if (isOr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

void solve()
{
    ll n, m;
    cin >> n >> m;

    ll size = 1 << n;
    ll a[size], seg[4 * size];
    for (ll i = 0; i < size; i++)
        cin >> a[i];

    if (n % 2)
        build(a, seg, 0, size - 1, 0, true);
    else
        build(a, seg, 0, size - 1, 0, false);

    while (m--)
    {
        ll i, val;
        cin >> i >> val;
        i--;

        if (n % 2)
            update(seg, 0, 0, size - 1, i, val, true);
        else
            update(seg, 0, 0, size - 1, i, val, false);
        a[i] = val;

        cout << seg[0] << "\n";
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        // cout << "Case #" << t << ": ";
        solve();
    }
}

ll powmod(ll a, ll b)
{
    ll res = 1;
    a %= MOD;
    assert(b >= 0);
    for (; b; b >>= 1)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}

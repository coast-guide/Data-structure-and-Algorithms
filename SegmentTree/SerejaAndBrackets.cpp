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

struct node
{
    int open;
    int close;
    int full;
    node() { open = close = full = 0; }
};

node merge(node left, node right)
{
    node ans;

    ans.full = left.full + right.full + min(left.open, right.close);

    ans.open = left.open + right.open - min(left.open, right.close);

    ans.close = left.close + right.close - min(left.open, right.close);
    return ans;
}

void build(node seg[], string &s, ll low, ll high, ll ind)
{

    if (low == high)
    {
        if (s[low] == '(')
            seg[ind].open += 1;
        else
            seg[ind].close += 1;
        return;
    }

    ll mid = low + (high - low) / 2;
    build(seg, s, low, mid, 2 * ind + 1);
    build(seg, s, mid + 1, high, 2 * ind + 2);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
}

node query(node seg[], ll low, ll high, ll index, ll l, ll r)
{
    // no overlap
    if (r < low || l > high)
        return node();

    // complete overlap
    if (low >= l && high <= r)
        return seg[index];

    // partial overlap
    ll mid = low + (high - low) / 2;
    node left = query(seg, low, mid, 2 * index + 1, l, r);
    node right = query(seg, mid + 1, high, 2 * index + 2, l, r);

    return merge(left, right);
}

void solve()
{
    string s;
    cin >> s;

    ll q;
    cin >> q;

    ll n = s.size();
    node seg[4 * n];
    build(seg, s, 0, n - 1, 0);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(seg, 0, n - 1, 0, l, r).full * 2 << "\n";
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

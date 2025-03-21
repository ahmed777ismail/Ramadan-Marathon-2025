#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;
static const int MAXN = 1000000; // Max sum of n across all tests

// Precompute factorials, inverse factorials, and powers of 2 up to MAXN.
static vector<long long> fact(MAXN + 1), invfact(MAXN + 1), p2(MAXN + 1);

// Fast exponentiation to compute base^exp % MOD
long long modexp(long long base, long long exp) {
    long long result = 1 % MOD;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and inverses
void init() {
    // factorial[0] = 1
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    // invfact[MAXN] = (fact[MAXN])^(MOD-2) mod
    invfact[MAXN] = modexp(fact[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
    // powers of 2
    p2[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        p2[i] = (p2[i - 1] << 1) % MOD;
    }
}

// Compute nCr in O(1) using precomputed factorials
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init(); // precompute factorials, inverses, and 2^k

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int E = 0, O = 0; // count evens, odds
        for (int i = 0; i < n; i++) {
            long long val;
            cin >> val;
            if ((val % 2 + 2) % 2 == 0) {
                // even (handle negatives properly by adding 2 before %2)
                E++;
            }
            else {
                O++;
            }
        }
        // Build prefix sums of binomial(O, 0..k)
        vector<long long> prefix(O + 1, 0LL);
        prefix[0] = nCr(O, 0);
        for (int i = 1; i <= O; i++) {
            prefix[i] = (prefix[i - 1] + nCr(O, i)) % MOD;
        }

        // Now sum up subsets with x>y
        // x = number of chosen evens, y = number of chosen odds
        // if x>O => all y=0..O are valid => sum of binomial(O,y)=2^O
        // else sum_{y=0..x-1} binomial(O,y) = prefix[x-1]
        long long ans = 0;
        for (int x = 1; x <= E; x++) {
            long long waysE = nCr(E, x); // ways to choose x evens
            if (x > O) {
                // all y in [0..O] => 2^O
                long long part = waysE * p2[O] % MOD;
                ans = (ans + part) % MOD;
            }
            else {
                // sum_{y=0..x-1} binomial(O,y) = prefix[x-1]
                long long part = waysE * prefix[x - 1] % MOD;
                ans = (ans + part) % MOD;
            }
        }
        cout << ans % MOD << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

// Precompute factorials and inverse factorials up to MAXN.
// Adjust MAXN if your problem constraints on N are bigger or smaller.
const int MAXN = 100000;

// Arrays for factorials and inverse factorials
long long fact[MAXN + 1], invFact[MAXN + 1];

// Fast exponentiation (modular)
long long modExp(long long base, int exp, int m) {
    long long result = 1 % m;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % m;
        base = (base * base) % m;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and inverses
void initFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    // Fermat's little theorem for inverse of factorial
    invFact[MAXN] = modExp(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// n! / (a! b! c!) mod
// Provided that a+b+c = n
long long multinomial(int n, int a, int b, int c) {
    // if a+b+c != n or any negative, caller should skip
    long long res = fact[n];
    res = (res * invFact[a]) % MOD;
    res = (res * invFact[b]) % MOD;
    res = (res * invFact[c]) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute all factorials, inverse factorials
    initFactorials();

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;

        // Let d = K - 7N
        long long d = (long long)K - 1LL * 7 * N;

        // If d < 0 or d > 2N, answer = 0
        if (d < 0 || d > 2LL * N) {
            cout << 0 << "\n";
            continue;
        }

        long long ans = 0;
        // We'll iterate over c from 0.. up to min(N, d/2)
        // Because b = d - 2c >= 0 => c <= d/2
        // And c <= N, obviously
        long long maxC = min<long long>(N, d / 2);

        for (long long c = 0; c <= maxC; c++) {
            long long b = d - 2 * c; // must be >= 0 by construction
            // Then a = N - (b + c)
            long long a = N - (b + c);
            if (a < 0) continue; // no good
            // Now a,b,c are nonnegative. Check if they sum to N
            // a+b+c = N is forced by how we defined them.
            // So the count of sequences with exactly a zeros, b ones, c twos is:
            //   N! / (a! b! c!)
            ans = (ans + multinomial(N, (int)a, (int)b, (int)c)) % MOD;
        }

        cout << ans << "\n";
    }

    return 0;
}

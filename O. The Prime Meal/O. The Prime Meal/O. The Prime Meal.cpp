#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
vector<int> SPF(MAX + 1);

void precompute() {
    iota(SPF.begin(), SPF.end(), 0);
    for (int i = 2; i * i <= MAX; ++i) {
        if (SPF[i] == i) {
            for (int j = i * i; j <= MAX; j += i) {
                if (SPF[j] == j) {
                    SPF[j] = i;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        unordered_set<int> primes;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            while (x != 1) {
                int spf = SPF[x];
                primes.insert(spf);
                while (x % spf == 0) {
                    x /= spf;
                }
            }
        }
        cout << primes.size() << '\n';
    }
    return 0;
}
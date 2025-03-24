#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W;

    // We'll collect all sub-items here: (cost, value)
    vector<pair<int, int>> subItems;

    // Read the items and decompose each by powers of two
    for (int i = 0; i < n; i++) {
        long long v, w, k;
        cin >> v >> w >> k;

        // Binary splitting of usage limit k
        // Because k = 2^x - 1, we can repeatedly subtract powers of two.
        long long power = 1;
        while (power <= k) {
            subItems.push_back({ (int)(power * w), (int)(power * v) });
            k -= power;
            power <<= 1; // multiply by 2
        }
        // If there's a remainder (not in this problem since k=2^x-1,
        // but in general bounded-knapsack logic, you might do):
        // if(k > 0) {
        //   subItems.push_back({(int)(k * w), (int)(k * v)});
        //   k = 0;
        // }
    }

    // Now do a 0-1 knapsack on all subItems
    vector<long long> dp(W + 1, 0LL);

    for (auto& item : subItems) {
        int cost = item.first;
        int value = item.second;
        // Traverse backwards to avoid reusing this sub-item multiple times
        for (int cap = W; cap >= cost; cap--) {
            dp[cap] = max(dp[cap], dp[cap - cost] + value);
        }
    }

    // The answer is the maximum value we can achieve with capacity W
    cout << dp[W] << "\n";

    return 0;
}

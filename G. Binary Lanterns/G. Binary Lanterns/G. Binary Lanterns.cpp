#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        int current_flips = 0;
        vector<int> res;
        for (int i = n; i >= 1; --i) {
            int idx = i - 1;
            int a_val = a[idx] - '0';
            int b_val = b[idx] - '0';
            int current_val = a_val ^ current_flips;
            if (current_val != b_val) {
                res.push_back(i);
                current_flips ^= 1;
            }
        }
        cout << res.size() << '\n';
        if (!res.empty()) {
            for (int x : res) {
                cout << x << ' ';
            }
            cout << '\n';
        }
        else {
            cout << '\n';
        }
    }
}
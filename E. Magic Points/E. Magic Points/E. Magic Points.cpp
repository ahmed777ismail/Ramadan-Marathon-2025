#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        long long current_sum = 0;
        int resets = 0;
        long long max_sum = LLONG_MIN;
        long long min_sum = LLONG_MAX;

        for (int i = 0; i < n; ++i) {
            long long a;
            cin >> a;

            if (a == 0) {
                if (current_sum > 0) {
                    if (current_sum > max_sum) {
                        max_sum = current_sum;
                    }
                    if (current_sum < min_sum) {
                        min_sum = current_sum;
                    }
                    resets++;
                    current_sum = 0;
                }
            }
            else {
                current_sum += a;
            }
        }

        // Check the final sum after processing all elements
        if (current_sum > 0) {
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
            if (current_sum < min_sum) {
                min_sum = current_sum;
            }
        }

        if (max_sum == LLONG_MIN) {
            cout << "0 0 0\n";
        }
        else {
            cout << max_sum << ' ' << min_sum << ' ' << resets << '\n';
        }
    }

    return 0;
}
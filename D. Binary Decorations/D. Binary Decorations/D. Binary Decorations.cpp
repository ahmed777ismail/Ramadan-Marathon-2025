#include <iostream>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;

        bool possible = false;
        if (n % 2 == 0) {
            int required = n / 2;
            if (k == required) possible = true;
        }
        else {
            int max_k = (n + 1) / 2;
            int min_k = (n - 1) / 2;
            if (k == max_k || k == min_k) possible = true;
        }

        if (!possible) {
            cout << "NO" << endl;
            continue;
        }

        string s;
        char current;
        if (n % 2 == 0) {
            current = '0';
        }
        else {
            current = (k == (n + 1) / 2) ? '1' : '0';
        }

        for (int i = 0; i < n; ++i) {
            s += current;
            current = (current == '0') ? '1' : '0';
        }

        cout << "YES" << endl << s << endl;
    }
    return 0;
}
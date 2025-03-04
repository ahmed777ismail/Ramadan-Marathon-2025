#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isVowel(char ch) {
    // Convert to lowercase to handle both uppercase and lowercase vowels
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> vowelIndices;
        for (int i = 0; i < n; ++i) {
            if (isVowel(s[i])) {
                vowelIndices.push_back(i + 1); // 1-based index
            }
        }

        cout << vowelIndices.size() << endl;
        for (int index : vowelIndices) {
            cout << index << " ";
        }
        cout << endl;
    }

    return 0;
}
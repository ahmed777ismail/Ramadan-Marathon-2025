#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        // 1) Read number of tasks
        int n;
        cin >> n;
        vector<long long> difficulty(n), reward(n);

        // 2) Read tasks: difficulty & reward
        for (int i = 0; i < n; i++) {
            cin >> difficulty[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> reward[i];
        }

        // 3) Pair up tasks and sort by difficulty
        vector<pair<long long, long long>> tasks(n);
        for (int i = 0; i < n; i++) {
            tasks[i] = { difficulty[i], reward[i] };
        }
        sort(tasks.begin(), tasks.end(),
            [](auto& a, auto& b) {
                return a.first < b.first; // sort by difficulty ascending
            });

        // 4) Read volunteers
        int m;
        cin >> m;
        vector<long long> volunteers(m);
        for (int i = 0; i < m; i++) {
            cin >> volunteers[i];
        }
        // Sort volunteers by ability
        sort(volunteers.begin(), volunteers.end());

        // 5) Greedily assign volunteers to tasks
        long long totalReward = 0;
        priority_queue<long long> maxHeap; // store rewards of feasible tasks
        int i = 0; // pointer over tasks

        for (auto& ability : volunteers) {
            // Add all tasks with difficulty <= ability to the max-heap
            while (i < n && tasks[i].first <= ability) {
                maxHeap.push(tasks[i].second);
                i++;
            }
            // If we have any feasible tasks, pick the one with the highest reward
            if (!maxHeap.empty()) {
                totalReward += maxHeap.top();
                // DO NOT pop, because the same task can be reused
            }
        }

        // 6) Print the total maximum reward
        cout << totalReward << "\n";
    }

    return 0;
}

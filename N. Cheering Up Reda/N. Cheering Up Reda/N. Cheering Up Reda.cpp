#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // Multisets to store transformed coordinates
    multiset<ll> u_set, v_set;
    map<pair<ll, ll>, int> point_count;

    // Function to insert a point
    auto insert_point = [&](ll x, ll y) {
        ll u = x + y;
        ll v = x - y;
        u_set.insert(u);
        v_set.insert(v);
        point_count[{x, y}]++;
        };

    // Function to delete a point
    auto remove_point = [&](ll x, ll y) {
        ll u = x + y;
        ll v = x - y;
        if (point_count[{x, y}] > 0) {
            u_set.erase(u_set.find(u));
            v_set.erase(v_set.find(v));
            point_count[{x, y}]--;
        }
        };

    // Function to compute the max Manhattan distance
    auto get_max_distance = [&]() -> ll {
        ll max_u = *u_set.rbegin();
        ll min_u = *u_set.begin();
        ll max_v = *v_set.rbegin();
        ll min_v = *v_set.begin();
        return max(max_u - min_u, max_v - min_v);
        };

    // Read initial points
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        insert_point(x, y);
    }

    // Process queries
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {  // Insert contestant
            ll x, y;
            cin >> x >> y;
            insert_point(x, y);
        }
        else if (type == 2) {  // Remove contestant
            ll x, y;
            cin >> x >> y;
            remove_point(x, y);
        }
        else if (type == 3) {  // Compute max Manhattan distance
            cout << get_max_distance() << "\n";
        }
    }

    return 0;
}

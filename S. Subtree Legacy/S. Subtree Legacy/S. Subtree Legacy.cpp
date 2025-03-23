#include <bits/stdc++.h>
using namespace std;

/*
  We will:
    1) Read the tree, root it at node 1.
    2) Run a DFS to get tin[v], tout[v], and an Euler array euler[] of length N.
       - euler[tin[v]] = v
       - subtree of v => euler[tin[v]..tout[v]-1]
    3) Compress values. Let compVal[v] = compressed value of node v's original value.
    4) Build a *persistent* segment tree over the euler[] array of compressed values.
       - pseg[i] = root of the segment tree that includes the first i elements of euler[].
       - pseg[0] = empty tree
       - pseg[i] = update(pseg[i-1], compVal[euler[i-1]], +1)
    5) For query (V, K):
       - L = tin[V], R = tout[V]
       - subarray size = R - L
       - K-th largest => rank = (R - L) - K + 1 = R - L - K + 1
       - find the compressed value 'c' that is the 'rank'-th smallest in euler[L..R-1]
         by using pseg[R], pseg[L] in a persistent segtree "range query" + binary search
       - print the original value that corresponds to 'c'.
*/

// We'll store up to 4 * N * log(N) nodes in the segtree if needed:
static const int MAXN = 100000;

vector<int> adj[MAXN + 1];
int N, Q;
long long val[MAXN + 1];

// For Euler Tour:
int tin[MAXN + 1], tout[MAXN + 1];
int eulerV[MAXN + 1];      // eulerV[i] = node index at time i
int timer = 0;

// We'll store compressed values in compVal[node].
int compVal[MAXN + 1];
vector<long long> sortedVals; // distinct sorted values for compression

// For persistent segment tree:
static const int MAXNODE = 40'00000; // might need to adjust if memory is tight
int stLeft[MAXNODE], stRight[MAXNODE];  // child pointers
int freq[MAXNODE];                      // how many numbers in this node's segment
int root[MAXN + 1];                       // root[i] = root of segtree for first i elements
int segIdx = 0;                         // index of next free node in segtree

// We'll store the entire compressed range from 0..(C-1), where C is # of distinct values.
int C = 0; // size of compression

// Build a new empty tree:
int buildEmpty(int start, int end) {
    // We'll just return 0 to indicate "null" for empty in a persistent approach
    return 0;
}

// Clone the node 'prv' and update for value 'pos' by +1 frequency:
int update(int prv, int start, int end, int pos) {
    // create a new node
    int curr = ++segIdx;
    // copy data from prv
    stLeft[curr] = stLeft[prv];
    stRight[curr] = stRight[prv];
    freq[curr] = freq[prv] + 1;

    if (start < end) {
        int mid = (start + end) >> 1;
        if (pos <= mid) {
            stLeft[curr] = update(stLeft[curr], start, mid, pos);
        }
        else {
            stRight[curr] = update(stRight[curr], mid + 1, end, pos);
        }
    }
    return curr;
}

// getCount in [0..val] for version 'ver'
int queryCount(int ver, int start, int end, int val) {
    if (ver == 0 || val < start) {
        return 0;
    }
    if (val >= end) {
        // entire segment
        return freq[ver];
    }
    int mid = (start + end) >> 1;
    int leftCount = queryCount(stLeft[ver], start, mid, val);
    int rightCount = queryCount(stRight[ver], mid + 1, end, val);
    return leftCount + rightCount;
}

// We'll get how many elements <= X in [L,R-1] by
//   countVerR = queryCount(root[R], X)
//   countVerL = queryCount(root[L], X)
//   countInRange = countVerR - countVerL
// Then we do a binary search for the compressed value X that yields countInRange = rank.

void dfs(int u, int p) {
    tin[u] = timer;
    eulerV[timer] = u;
    timer++;
    for (int nxt : adj[u]) {
        if (nxt == p) continue;
        dfs(nxt, u);
    }
    tout[u] = timer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> val[i];
    }

    for (int i = 1; i <= N; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Root the tree at 1 (arbitrary).
    timer = 0;
    dfs(1, -1);

    // We'll compress the node values. Let's gather them in a vector.
    sortedVals.resize(N);
    for (int i = 0; i < N; i++) {
        // node in euler order:
        long long originalVal = val[eulerV[i]];
        sortedVals[i] = originalVal;
    }
    // Sort + unique
    sort(sortedVals.begin(), sortedVals.end());
    sortedVals.erase(unique(sortedVals.begin(), sortedVals.end()), sortedVals.end());
    C = (int)sortedVals.size();

    // Prepare compVal for each node (not strictly needed per node, but let's do it).
    // Actually we only need to compress the euler array positions. We'll do it on the fly.
    // We'll define a function to compress a single value:
    auto compress = [&](long long x) {
        // binary search in sortedVals
        int pos = int(std::lower_bound(sortedVals.begin(), sortedVals.end(), x) - sortedVals.begin());
        return pos; // 0-based
        };

    // Build persistent segment trees:
    // root[0] = empty
    // root[i] = update(root[i-1], compVal of eulerV[i-1], +1)
    segIdx = 0;
    // initially all 0
    for (int i = 0; i <= N; i++) {
        root[i] = 0;
    }

    for (int i = 1; i <= segIdx; i++) {
        stLeft[i] = stRight[i] = freq[i] = 0;
    }
    segIdx = 0; // re-init to use from scratch

    // Build version i from version i-1 by adding euler[i-1]'s value
    for (int i = 1; i <= N; i++) {
        int nodeIndex = eulerV[i - 1];
        int c = compress(val[nodeIndex]);
        // build version i
        root[i] = update(root[i - 1], 0, C - 1, c);
    }

    while (Q--) {
        int V, K;
        cin >> V >> K;
        // Subtree of V => [tin[V], tout[V]) in euler
        int L = tin[V];
        int R = tout[V];
        int length = R - L; // number of nodes in V's subtree

        // The K-th largest is the (length - K + 1)-th smallest
        int rank = length - K + 1;
        // We do a binary search over [0..C-1]
        int lo = 0, hi = C - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            // how many <= mid in [L,R)?
            int countR = queryCount(root[R], 0, C - 1, mid);
            int countL = queryCount(root[L], 0, C - 1, mid);
            int cnt = countR - countL;
            if (cnt >= rank) {
                // we have at least 'rank' elements <= mid
                // so we can go left to find a smaller 'mid'
                hi = mid;
            }
            else {
                // we need more elements, so go bigger
                lo = mid + 1;
            }
        }
        // lo is the compressed value for the rank-th smallest => K-th largest
        long long answerVal = sortedVals[lo];
        cout << answerVal << "\n";
    }

    return 0;
}

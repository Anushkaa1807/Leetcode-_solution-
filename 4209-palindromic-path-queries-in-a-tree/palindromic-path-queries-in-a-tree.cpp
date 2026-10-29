class Solution {
    int LOG;
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth, bit;
    vector<int> mask, rootMask;
    int timer = 0;

    void add(int idx, int val, int n) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] ^= val;
    }

    int get(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res ^= bit[idx];
        return res;
    }

    void rangeUpdate(int l, int r, int val, int n) {
        add(l, val, n);
        add(r + 1, val, n);
    }

    int getRootMask(int u) {
        return rootMask[u] ^ get(tin[u]);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j))
                u = up[j][u];
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        
        up.assign(LOG, vector<int>(n, 0));
        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        bit.assign(n + 2, 0);
        mask.resize(n);
        rootMask.assign(n, 0);

        for (int i = 0; i < n; i++)
            mask[i] = 1 << (s[i] - 'a');
        vector<int> parent(n, -1), nextIdx(n, 0);
        stack<int> st;

        parent[0] = 0;
        up[0][0] = 0;
        rootMask[0] = mask[0];
        tin[0] = ++timer;
        st.push(0);

        while (!st.empty()) {
            int u = st.top();

            if (nextIdx[u] < (int)adj[u].size()) {
                int v = adj[u][nextIdx[u]++];

                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                rootMask[v] = rootMask[u] ^ mask[v];

                tin[v] = ++timer;
                st.push(v);
            } else {
                tout[u] = timer;
                st.pop();
            }
        }
        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }

        vector<bool> answer;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newMask = 1 << (c - 'a');
                int delta = mask[u] ^ newMask;

                if (delta != 0) {
                    rangeUpdate(tin[u], tout[u], delta, n);
                    mask[u] = newMask;
                }
            } else {
                ss >> v;

                int w = lca(u, v);

                int pathMask =
                    getRootMask(u) ^
                    getRootMask(v) ^
                    mask[w];

                answer.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return answer;
    }
};

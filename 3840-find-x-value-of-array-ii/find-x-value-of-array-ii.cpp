class Solution {
public:
    struct Node {
        array<int, 5> cnt{};
        int prod = 1;
    };

    int n, k;
    vector<Node> seg;

    Node merge(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        for (int r = 0; r < k; r++) {
            res.cnt[r] = a.cnt[r];
        }

        for (int r = 0; r < k; r++) {
            int rem = (a.prod * r) % k;
            res.cnt[rem] += b.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r,
               const vector<int>& nums) {

        if (l == r) {
            int rem = nums[l] % k;

            seg[node].cnt[rem] = 1;
            seg[node].prod = rem;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        seg[node] = merge(seg[node * 2],
                          seg[node * 2 + 1]);
    }

    void update(int node, int l, int r,
                int idx, int value) {

        if (l == r) {
            int rem = value % k;

            seg[node].cnt.fill(0);
            seg[node].cnt[rem] = 1;
            seg[node].prod = rem;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }

        seg[node] = merge(seg[node * 2],
                          seg[node * 2 + 1]);
    }

    Node query(int node, int l, int r,
               int ql, int qr) {

        if (ql <= l && r <= qr) {
            return seg[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->n = nums.size();
        this->k = k;

        seg.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(
                1, 0, n - 1,
                start, n - 1
            );

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};
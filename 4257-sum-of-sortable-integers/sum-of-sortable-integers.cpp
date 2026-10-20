class Solution {
public:
    bool isRotation(vector<int>& nums, vector<int>& sorted,
                    int start, int k) {
        vector<int> pat(k), pi(k, 0);

        for (int i = 0; i < k; i++)
            pat[i] = sorted[start + i];

        // Build KMP prefix array
        for (int i = 1, j = 0; i < k; i++) {
            while (j > 0 && pat[i] != pat[j])
                j = pi[j - 1];

            if (pat[i] == pat[j])
                j++;

            pi[i] = j;
        }

        // Search pattern in the block repeated twice
        for (int i = 0, j = 0; i < 2 * k - 1; i++) {
            int val = nums[start + i % k];

            while (j > 0 && val != pat[j])
                j = pi[j - 1];

            if (val == pat[j])
                j++;

            if (j == k)
                return true;
        }

        return false;
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;

            for (int start = 0; start < n; start += k) {
                if (!isRotation(nums, sorted, start, k)) {
                    valid = false;
                    break;
                }
            }

            if (valid)
                ans += k;
        }

        return ans;
    }
};
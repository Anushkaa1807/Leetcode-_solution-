class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Match target from left to right
        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            // 1. Try to match target[i]
            if (freq[x] > 0) {
                freq[x]--;
                continue;
            }

            // 2. Same character is not available.
            // Try the smallest character greater than target[i].
            for (int c = x + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    freq[c]--;

                    // Put remaining characters in sorted order
                    for (int j = 0; j < 26; j++) {
                        while (freq[j] > 0) {
                            ans += char('a' + j);
                            freq[j]--;
                        }
                    }

                    return ans;
                }
            }

            // 3. Cannot make the answer greater here.
            // Backtrack.
            for (int j = i - 1; j >= 0; j--) {
                freq[target[j] - 'a']++;

                int cur = target[j] - 'a';

                for (int c = cur + 1; c < 26; c++) {
                    if (freq[c] > 0) {
                        string ans = target.substr(0, j);
                        ans += char('a' + c);

                        freq[c]--;

                        // Add remaining characters sorted
                        for (int k = 0; k < 26; k++) {
                            while (freq[k] > 0) {
                                ans += char('a' + k);
                                freq[k]--;
                            }
                        }

                        return ans;
                    }
                }
            }

            return "";
        }

        // We constructed target exactly.
        // Need a STRICTLY greater permutation.
        for (int i = n - 1; i >= 0; i--) {
            freq[target[i] - 'a']++;

            int cur = target[i] - 'a';

            for (int c = cur + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    freq[c]--;

                    for (int k = 0; k < 26; k++) {
                        while (freq[k] > 0) {
                            ans += char('a' + k);
                            freq[k]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};
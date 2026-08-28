class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int half = n / 2;
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }
        if (odd > 1)
            return "";
        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++)
            halfCnt[i] = cnt[i] / 2;
        auto makePalindrome = [&](const string& h) {
            string res = h;

            if (n % 2)
                res += mid;

            for (int i = half - 1; i >= 0; i--)
                res += h[i];

            return res;
        };
        string targetHalf = target.substr(0, half);

        vector<int> cur = halfCnt;
        string bestHalf = "";
        for (int i = 0; i < half; i++) {
            int x = targetHalf[i] - 'a';
            for (int c = x + 1; c < 26; c++) {
                if (cur[c] == 0)
                    continue;

                string candidate = targetHalf.substr(0, i);
                candidate += char('a' + c);

                cur[c]--;
                for (int k = 0; k < 26; k++) {
                    candidate += string(cur[k], char('a' + k));
                }

                if (bestHalf.empty() || candidate < bestHalf)
                    bestHalf = candidate;

                cur[c]++;
            }
            if (cur[x] == 0)
                break;

            cur[x]--;
        }
        bool validTargetHalf = true;
        vector<int> temp = halfCnt;

        for (char c : targetHalf) {
            if (--temp[c - 'a'] < 0) {
                validTargetHalf = false;
                break;
            }
        }
        if (validTargetHalf) {
            string candidate = makePalindrome(targetHalf);

            if (candidate > target)
                return candidate;
        }
        if (bestHalf.empty())
            return "";

        return makePalindrome(bestHalf);
    }
};
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;
        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }
        string ans;
        int i = 0;

        while (i < s.length()) {
            if (s[i] == '(') {
                int j = i + 1;
                while (s[j] != ')') {
                    j++;
                }
                string key = s.substr(i + 1, j - i - 1);

                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += '?';
                }
                i = j + 1;
            } 
            else {
                ans += s[i];
                i++;
            }
        }
        return ans;
    }
};
#include <string>

using namespace std;


class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1)
            return word;
        // sliding window, lexicographic max
        const auto n = word.size();
        const auto window_len = n - numFriends + 1;
        // can probably make some ad hoc / custom KMP-style thing for this
        // but the bounds are low so...
        const string_view w = word;
        string ans = "";
        for (auto i = 0; i < n; ++i) {
            if (w.substr(i, window_len) > ans)
                ans = word.substr(i, window_len);
        }
        return ans;
    }
};

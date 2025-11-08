#include <bits/stdc++.h>

#include <algorithm>
using namespace std;

struct checker {
    int n;
    vector<vector<int>> occ;
    const string *s, *t;

    // returns (feasible?, chosen o)
    pair<bool, vector<int>> check(int L) {
        vector<int> o(n, -1);
        int prev = 0;
        if ((*s)[0] != (*t)[0])
            return {false, {}};
        o[0] = 0;
        prev = 0;

        for (int i = 1; i < n; ++i) {
            int c = (*t)[i] - 'a';
            int low = max(prev, i - L);
            // find first occurrence >= low
            const auto &v = occ[c];
            auto it = std::ranges::lower_bound(v, low);
            if (it == v.end() || *it > i)
                return {false, {}};
            o[i] = *it;
            prev = o[i];
        }
        return {true, o};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T))
        return 0;
    while (T--) {
        int n;
        long long kmax;
        string s, t;
        cin >> n >> kmax;
        cin >> s >> t;

        if (s[0] != t[0]) {
            cout << -1 << '\n';
            continue;
        }

        // build occurrences
        vector<vector<int>> occ(26);
        for (int i = 0; i < n; ++i)
            occ[s[i] - 'a'].push_back(i);

        bool ok = true;
        {
            vector<int> last(26, -1);
            for (int i = 0; i < n; ++i) {
                last[s[i] - 'a'] = i;
                if (last[t[i] - 'a'] == -1) {
                    ok = false;
                    break;
                }
            }
        }
        if (!ok) {
            cout << -1 << '\n';
            continue;
        }

        // binary search minimal L
        checker F{.n = n, .occ = occ, .s = &s, .t = &t};
        int lo = 0, hi = n - 1, best = n;
        vector<int> best_o;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            auto [feas, o] = F.check(mid);
            if (feas) {
                best = mid;
                best_o = move(o);
                hi = mid - 1;
            } else
                lo = mid + 1;
        }
        if (best > (int) kmax) {
            cout << -1 << '\n';
            continue;
        }

        cout << best << '\n';
        vector<int> c(n);
        for (int i = 0; i < n; ++i)
            c[i] = i - best_o[i];

        string cur = s;
        for (int r = 1; r <= best; ++r) {
            string nxt = cur;
            for (int i = 1; i < n; ++i) {
                if (r <= c[i])
                    nxt[i] = cur[i - 1];
                else
                    nxt[i] = cur[i];
            }
            cout << nxt << '\n';
            cur = move(nxt);
        }
    }
    return 0;
}

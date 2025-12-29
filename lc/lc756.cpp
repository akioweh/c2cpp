#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    bool pyramidTransition(string bottom, const vector<string> &allowed) {

        auto a_map = array<vector<char>, 6 * 6>();
        for (const auto &s : allowed) {
            const auto l = s[0] - 'A';
            const auto r = s[1] - 'A';
            a_map[l * 6 + r].push_back(s[2]);
        }

        const auto opts = [&](const char l, const char r) { return a_map[(l - 'A') * 6 + (r - 'A')]; };

        auto cache = unordered_map<string, bool>();

        const function<bool(const string &)> possible = [&](const string &base) -> bool {
            if (base.size() == 1)
                return true;

            if (const auto it = cache.find(base); it != cache.end())
                return it->second;

            const auto next_opts = views::pairwise(base) | views::transform([&](const auto &tup) {
                                       return opts(get<0>(tup), get<1>(tup)) | ranges::to<vector<char>>();
                                   }) |
                    ranges::to<vector>();

            const auto no_rn = next_opts | views::transform([](const auto &v) { return v.size(); });
            const auto tot = accumulate(no_rn.begin(), no_rn.end(), 1, multiplies{});
            auto rad = vector<int>(next_opts.size());
            auto c = 1;
            for (auto i = next_opts.size(); i--;) {
                rad[i] = c;
                c *= next_opts[i].size();
            }

            const auto permutations = views::iota(0, tot) | views::transform([&](const auto idx) {
                                          string _r;
                                          _r.reserve(next_opts.size());
                                          for (auto i = 0; i < next_opts.size(); ++i)
                                              _r.push_back(next_opts[i][idx / rad[i] % next_opts[i].size()]);
                                          return _r;
                                      });

            const auto res = ranges::any_of(permutations, possible);
            cache[base] = res;
            return res;
        };

        return possible(bottom);
    }
};


int main() {
    Solution sol;

    const auto bottom = "AFFFFA";
    const auto allowed = vector<string>{
            "ADA", "ADC", "ADB", "AEA", "AEC", "AEB", "AFA", "AFC", "AFB", "CDA", "CDC", "CDB", "CEA", "CEC",
            "CEB", "CFA", "CFC", "CFB", "BDA", "BDC", "BDB", "BEA", "BEC", "BEB", "BFA", "BFC", "BFB", "DAA",
            "DAC", "DAB", "DCA", "DCC", "DCB", "DBA", "DBC", "DBB", "EAA", "EAC", "EAB", "ECA", "ECC", "ECB",
            "EBA", "EBC", "EBB", "FAA", "FAC", "FAB", "FCA", "FCC", "FCB", "FBA", "FBC", "FBB", "DDA", "DDC",
            "DDB", "DEA", "DEC", "DEB", "DFA", "DFC", "DFB", "EDA", "EDC", "EDB", "EEA", "EEC", "EEB", "EFA",
            "EFC", "EFB", "FDA", "FDC", "FDB", "FEA", "FEC", "FEB", "FFA", "FFC", "FFB", "DDD", "DDE", "DDF",
            "DED", "DEE", "DEF", "DFD", "DFE", "DFF", "EDD", "EDE", "EDF", "EED", "EEE", "EEF", "EFD", "EFE",
            "EFF", "FDD", "FDE", "FDF", "FED", "FEE", "FEF", "FFD", "FFE", "FFF"};

    cout << boolalpha << sol.pyramidTransition(bottom, allowed) << endl;

    return 0;
}

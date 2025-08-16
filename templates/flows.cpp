#include <deque>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

using ull = unsigned long long;
using ll = long long;


ll push_relabel(const vector<vector<int>> &graph, const vector<vector<int>> &capacity, const int s, const int t) {
    const auto N = static_cast<int>(graph.size());
    auto flow = vector(N, vector(N, 0ll));
    auto excess = vector(N, 0LL);
    auto height = vector(N, 0);
    auto arc = vector(N, 0); // current position in adj list
    auto H = vector((2 * N) + 1, deque<int>()); // active vertices, bucketed by height
    auto max_h = 0; // top of H

    // u must be active and v admissible
    const auto push = [&](const int u, const int v) {
        const auto delt = min(excess[u], static_cast<ll>(capacity[u][v]) - flow[u][v]);
        if (delt == 0)
            return;
        if (v != s && v != t && excess[v] == 0) { // if target was not already active
            H[height[v]].push_back(v); // add to active vertices H bucket
            max_h = max(max_h, height[v]);
        }
        flow[u][v] += delt;
        flow[v][u] -= delt;
        excess[u] -= delt;
        excess[v] += delt;
    };

    // u must be active, without admissible neighbors
    const auto relabel = [&](const int u) {
        auto min_h = numeric_limits<int>::max() - 1;
        for (const auto v : graph[u]) {
            if (static_cast<ll>(capacity[u][v]) - flow[u][v] > 0)
                min_h = min(min_h, height[v]);
        }
        height[u] = min_h + 1;
    };

    // deactivate vertex by pushing away all excess (u must be active)
    const auto discharge = [&](const int u) {
        while (excess[u] != 0) {
            if (static_cast<ull>(arc[u]) == graph[u].size()) { // ran out of admissible neighbors
                relabel(u);
                arc[u] = 0;
                continue;
            }
            const auto v = graph[u][arc[u]++];
            if (static_cast<ll>(capacity[u][v]) - flow[u][v] == 0 || height[u] != height[v] + 1)
                continue; // not admissible
            push(u, v);
        }
    };

    // selects the next active vertex. vertex should then be deactivated or re-inserted into H
    const auto next_active = [&] {
        while (max_h >= 0 && H[max_h].empty())
            --max_h;
        if (max_h == -1)
            return -1;
        const auto res = H[max_h].back();
        H[max_h].pop_back();
        return res;
    };

    // initialize pre-flow
    height[s] = N;
    excess[s] = numeric_limits<ll>::max();
    for (const auto v : graph[s])
        push(s, v);

    int cur;
    while ((cur = next_active()) != -1)
        discharge(cur);

    return excess[t];
}


ll push_relabel_bfs(const vector<vector<int>> &graph, const vector<vector<int>> &capacity, const int s, const int t) {
    const auto N = static_cast<int>(graph.size());
    auto flow = vector(N, vector(N, 0LL));
    auto excess = vector(N, 0LL);
    auto height = vector(N, 0);
    auto arc = vector(N, 0); // current position in adj list
    auto H = vector((2 * N) + 1, deque<int>()); // active vertices, bucketed by height
    auto max_h = 0; // top of H

    // u must be active and v admissible
    const auto push = [&](const int u, const int v) {
        const auto delt = min(excess[u], static_cast<ll>(capacity[u][v]) - flow[u][v]);
        if (delt == 0)
            return;
        if (v != s && v != t && excess[v] == 0) { // if target was not already active
            H[height[v]].push_back(v); // add to active vertices H bucket
            max_h = max(max_h, height[v]);
        }
        flow[u][v] += delt;
        flow[v][u] -= delt;
        excess[u] -= delt;
        excess[v] += delt;
    };

    // u must be active, without admissible neighbors
    const auto relabel = [&](const int u) {
        auto min_h = numeric_limits<int>::max() - 1;
        for (const auto v : graph[u]) {
            if (static_cast<ll>(capacity[u][v]) - flow[u][v] > 0)
                min_h = min(min_h, height[v]);
        }
        height[u] = min_h + 1;
    };

    // deactivate vertex by pushing away all excess (u must be active)
    const auto discharge = [&](const int u) {
        while (excess[u] != 0) {
            if (static_cast<ull>(arc[u]) == graph[u].size()) { // ran out of admissible neighbors
                relabel(u);
                arc[u] = 0;
                continue;
            }
            const auto v = graph[u][arc[u]++];
            if (static_cast<ll>(capacity[u][v]) - flow[u][v] == 0 || height[u] != height[v] + 1)
                continue; // not admissible
            push(u, v);
        }
    };

    // selects the next active vertex. vertex should then be deactivated or re-inserted into H
    const auto next_active = [&] {
        while (max_h >= 0 && H[max_h].empty())
            --max_h;
        if (max_h == -1)
            return -1;
        const auto res = H[max_h].back();
        H[max_h].pop_back();
        return res;
    };

    const auto relabel_all = [&] {
        ranges::fill(height, N);
        height[t] = 0;
        for (auto &s : H)
            s.clear();

        auto q = queue<int>({t});
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            max_h = height[u];
            for (const auto v : graph[u]) {
                if (height[v] != N || v == s || static_cast<ll>(capacity[v][u]) - flow[v][u] <= 0)
                    continue;
                q.push(v);
                height[v] = height[u] + 1;
                if (excess[v] > 0)
                    H[height[v]].push_back(v);
            }
        }
    };

    // initialize pre-flow
    height[s] = N;
    excess[s] = numeric_limits<ll>::max();
    // relabel_all();
    for (const auto v : graph[s])
        push(s, v);

    int cur;
    int cnt = 0;
    while ((cur = next_active()) != -1) {
        discharge(cur);
        if (++cnt == 4 * N) {
            relabel_all();
            cnt = 0;
        }
    }

    return excess[t];
}

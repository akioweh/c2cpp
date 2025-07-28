#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;


std::pair<int, int> diameter_(const vector<vector<int>> &graph, const int u, const int prev) {
    if (graph[u].size() == 1)
        return {0, 0};
    auto temp = graph[u]
                | views::filter([&](const int v) { return v != prev; })
                | views::transform([&](const int v) { return diameter_(graph, v, u); });
    auto heights = temp | views::elements<0>;
    auto subdiameters = temp | views::elements<1>;

    // find largest two heights
    int h1 = -1, h2 = -1;
    if (heights.size == 1) {
        h1 = *heights.begin();
    } else {
        array<int, 2> tmp{};
        ranges::partial_sort_copy(heights, tmp, greater{});
        h1 = tmp[0];
        h2 = tmp[1];
    }

    return {h1, max(ranges::max(subdiameters), h1 + h2 + 2)};
}


int diameter(const vector<vector<int>> &graph, const int root) {
    return diameter_(graph, root, -1).second;
}

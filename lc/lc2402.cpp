#include <bits/stdc++.h>
#include <cassert>

using namespace std;

using ll = long long;


class Solution {
public:
    int mostBooked(int n, vector<vector<int>> &meetings) {
        auto delayed_meetings = deque<int>(); // duration
        const auto rn_n = views::iota(0, n);
        auto available_rooms = priority_queue<int, vector<int>, greater<int>>(rn_n.begin(), rn_n.end());
        auto room_available = vector(n, true);
        const auto rn_m =
                meetings | views::transform([](const auto &v) { return make_pair(v[0], make_pair(1, v[1])); });
        using event_t = pair<ll, pair<int, ll>>; // time, (type, data)
        auto events = priority_queue<event_t, vector<event_t>, greater<event_t>>(rn_m.begin(), rn_m.end());
        auto res = vector(n, 0);

        const auto book_room = [&](const int room, const ll end) {
            assert(room_available[room]);
            room_available[room] = false;
            events.emplace(end, make_pair(0, room));
            ++res[room];
        };

        const auto get_room = [&]() {
            while (!available_rooms.empty()) {
                const auto room = available_rooms.top();
                available_rooms.pop();
                if (room_available[room])
                    return room;
            }
            return -1;
        };

        while (!events.empty()) {
            const auto [t, e] = events.top();
            events.pop();
            const auto [typ, d] = e;
            if (typ == 0) {
                room_available[d] = true;
                available_rooms.push(d);
                if (!delayed_meetings.empty()) {
                    const auto end = t + delayed_meetings.front();
                    delayed_meetings.pop_front();
                    const auto room = get_room();
                    assert(room != -1);
                    book_room(room, end);
                }
            } else {
                const auto room = get_room();
                if (room != -1) {
                    book_room(room, d);
                } else {
                    delayed_meetings.push_back(d - t);
                }
            }
        }

        const auto most = *ranges::max_element(res);
        return ranges::distance(res.begin(), ranges::find(res, most));
    }
};

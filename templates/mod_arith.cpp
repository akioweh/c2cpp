#include <cassert>
#include <iostream>

using namespace std;

using ll = long long;


template<auto MOD_>
    requires(integral<decltype(MOD_)> && MOD_ > 0)
struct Mint {
    using T = decltype(MOD_);
    static constexpr T MOD = MOD_;

    int v;

    constexpr Mint() noexcept = default;  // v = 0
    constexpr Mint(const ll x) noexcept : v(norm(x)) {}


    static constexpr int norm(ll x) noexcept {
        x %= MOD;
        if (x < 0) x += MOD;
        return static_cast<int>(x);
    }


    constexpr Mint &operator+=(const Mint rhs) noexcept {
        v += rhs.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }


    constexpr Mint &operator-=(const Mint rhs) noexcept {
        v -= rhs.v;
        if (v < 0) v += MOD;
        return *this;
    }


    constexpr Mint &operator*=(const Mint rhs) noexcept {
        v = static_cast<int>(static_cast<ll>(v) * rhs.v % MOD);
        return *this;
    }


    constexpr Mint &operator/=(const Mint rhs) noexcept {
        return *this *= rhs.inv();
    }


    constexpr Mint operator-() const noexcept { return Mint(MOD - v); }
    constexpr Mint &operator++() noexcept { return *this += 1; }
    constexpr Mint &operator--() noexcept { return *this -= 1; }


    constexpr Mint operator++(int) noexcept {
        Mint tmp = *this;
        ++*this;
        return tmp;
    }


    constexpr Mint operator--(int) noexcept {
        Mint tmp = *this;
        --*this;
        return tmp;
    }


    friend constexpr Mint pow(Mint base, ll e) noexcept {
        if (e == -1) return inv(base);
        assert(e >= 0);
        Mint result(1);
        while (e > 0) {
            if (e % 2) result *= base;
            base *= base;
            e /= 2;
        }
        return result;
    }


    friend constexpr Mint inv(Mint n) noexcept {
        assert(n != 0);
        return pow(n, MOD - 2);
    }


    friend constexpr Mint operator+(Mint a, Mint b) noexcept { return a += b; }
    friend constexpr Mint operator-(Mint a, Mint b) noexcept { return a -= b; }
    friend constexpr Mint operator*(Mint a, Mint b) noexcept { return a *= b; }
    friend constexpr Mint operator/(Mint a, Mint b) noexcept { return a /= b; }

    friend constexpr auto operator<=>(const Mint &lhs, const Mint &rhs) noexcept = default;
};


// I/O operators outside the class
template<auto M>
ostream &operator<<(ostream &os, Mint<M> x) {
    return os << x.v;
}


template<auto M>
istream &operator>>(istream &is, Mint<M> &x) {
    ll t;
    is >> t;
    x = Mint<M>(t);
    return is;
}


// CTAD (Class Template Argument Deduction) guide
template<int M>
Mint(int) -> Mint<M>;


// usage example
int main() {
    constexpr int P = 1'000'000'007;
    Mint<P> a = 2;  // uses Mint(int) CTAD
    Mint<P> b = 5LL;
    auto c = 3 * a * b + 42;
    cout << "c = " << c << "\n";       // c = 52
    cout << "inv(c) = " << c.inv() << "\n";
    cout << "c^100 = " << pow(c, 100) << "\n";
}

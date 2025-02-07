#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll long long int
#define ld long double

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define MOD (1e9+7)
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define print(x) for(auto element:x) cout << element << " ";
#define endl "\n"

uint64_t modmul(const uint64_t a, const uint64_t b, const uint64_t M) {
    const int64_t ret = a * b - M * static_cast<int64_t>(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= static_cast<int64_t>(M));
}

uint64_t modpow(uint64_t a, uint64_t b, uint64_t M) {
    uint64_t ret = 1;

    for (; b; a = modmul(a, a, M), b /= 2) {
        if (b & 1) ret = modmul(ret, a, M);
    }
    return ret;
}

bool isPrime(const uint64_t n) {
    if (n < 2 || n % 6 % 4 != 1) {
        return (n | 1) == 3;
    }
    const uint64_t A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;

    for (const uint64_t a: A) {
        uint64_t p = modpow(a % n, d, n), i = s;

        while (p != 1 && p != n - 1 && a % n && i--) {
            p = modmul(p, p, n);
        }

        if (p != n - 1 && i != s) {
            return false;
        }
    }
    return true;
}

uint64_t pollard_rho(uint64_t n) {
    auto f = [n](const uint64_t x) { return modmul(x, x, n) + 1; };
    uint64_t x = 0, y = 0, t = 30, prd = 2, i = 1, q;

    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i, y = f(x);
        }
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) {
            prd = q;
        }
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

vector<uint64_t> factor(uint64_t n) {
    if (n == 1) {
        return {};
    }

    if (isPrime(n)) {
        return {n};
    }
    uint64_t x = pollard_rho(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

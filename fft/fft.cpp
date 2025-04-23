#include <bits/stdc++.h>
using namespace std;

static const uint32_t MOD = 998244353;
static const uint32_t ROOT = 3;

uint32_t fastpow(uint32_t a, uint32_t e) {
    uint64_t res = 1, base = a;
    while (e) {
        if (e & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        e >>= 1;
    }
    return (uint32_t) res;
}

void prepare(vector<uint32_t>& rev, vector<uint32_t>& roots, size_t n) {
    size_t logn = __builtin_ctz(n);
    rev.assign(n, 0);
    for (size_t i = 0; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logn - 1));
    }
    roots.assign(n, 1);
    uint32_t root = fastpow(ROOT, (MOD - 1) / n);
    for (size_t i = 1; i < n; ++i) {
        roots[i] = uint64_t(roots[i - 1]) * root % MOD;
    }
}

void ntt(vector<uint32_t>& a, const vector<uint32_t>& rev, const vector<uint32_t>& roots, bool invert) {
    size_t n = a.size();
    for (size_t i = 0; i < n; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (size_t len = 1; len < n; len <<= 1) {
        for (size_t i = 0; i < n; i += 2 * len) {
            for (size_t j = 0; j < len; ++j) {
                uint32_t u = a[i + j];
                uint32_t v = uint64_t(a[i + j + len]) * roots[n / (2 * len) * j] % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len] = u >= v ? u - v : u + MOD - v;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        uint32_t inv_n = fastpow(n, MOD - 2);
        for (size_t i = 0; i < n; ++i) {
            a[i] = uint64_t(a[i]) * inv_n % MOD;
        }
    }
}

vector<uint32_t> conv(const vector<uint32_t>& A, const vector<uint32_t>& B) {
    size_t n = 1;
    while (n < A.size() + B.size() - 1) n <<= 1;
    vector<uint32_t> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n);
    fb.resize(n);

    vector<uint32_t> rev, roots;
    prepare(rev, roots, n);

    ntt(fa, rev, roots, false);
    ntt(fb, rev, roots, false);
    for (size_t i = 0; i < n; ++i) {
        fa[i] = uint64_t(fa[i]) * fb[i] % MOD;
    }
    ntt(fa, rev, roots, true);

    fa.resize(A.size() + B.size() - 1);
    return fa;
}

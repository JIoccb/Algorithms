#include <bits/stdc++.h>
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

long long euler(long long n) {
    long long result = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

vector<long long> factorize(long long n) {
    vector<long long> result;
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            result.push_back(i);
            n /= i;
        }
    }
    if (n > 1) result.push_back(n);
    return result;
}

__int128 fastpow(__int128 base, __int128 exp, __int128 mod) {
    __int128 result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = result * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

bool is_primitive_root(long long g, long long M, long long phi_m, const vector<long long> &factors) {
    for (long long factor: factors) {
        if (fastpow(g, phi_m / factor, M) == 1) return false;
    }
    return true;
}

bool has_primitive_root(long long M) {
    if (M == 2) return true;
    if (M == 4) return true;
    if (M % 2 == 0) M /= 2;
    long long count = 0;
    for (long long p = 2; p * p <= M; p++) {
        if (M % p == 0) {
            count++;
            while (M % p == 0) M /= p;
        }
    }
    if (M > 1) count++;
    return count == 1;
}

long long find_primitive_root(long long M) {
    if (!has_primitive_root(M)) return -1;
    long long phi_M = euler(M);
    vector<long long> factors = factorize(phi_M);
    for (long long g = 1; g < M; g++) {
        if (gcd(g, M) == 1 && is_primitive_root(g, M, phi_M, factors)) {
            return g;
        }
    }
    return -1;
}

long long count_primitive_roots(long long p) {
    long long phi_p = p - 1;
    vector<long long> factors = factorize(phi_p);
    long long count = 0;
    for (long long g = 1; g < p; g++) {
        if (is_primitive_root(g, p, phi_p, factors)) count++;
    }
    return count;
}

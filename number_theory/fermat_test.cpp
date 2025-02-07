#include <bits/stdc++.h>
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

__int128 random(__int128 L, __int128 R) {
    return uniform_int_distribution<long long>(L, R)(rng);
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

bool isPrime(__int128 n) {
    if (n <= 1) return false;
    for (__int128 i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

bool is_carmichael(__int128 n) {
    for (__int128 i = 2; i * i * i <= n; i++) {
        if (n % i == 0) {
            return isPrime(i);
        }
    }
    return false;
}

bool fermat(__int128 n, int iterations = 100) {
    if (n == 2) return true;
    if (n <= 1) return false;
    if (is_carmichael(n)) return false;

    for (int i = 0; i < iterations; i++) {
        __int128 a = random(2, n - 1);
        if (fastpow(a, n - 1, n) != 1) return false;
    }
    return true;
}


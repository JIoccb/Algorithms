#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

tuple<int, vector<int>> continued_fraction_sqrt(int N) {
    int m = 0, d = 1, a0 = sqrt(N);
    if (a0 * a0 == N) return {a0, {}};  // Полный квадрат

    vector<int> period;
    int a = a0;
    do {
        m = d * a - m;
        d = (N - m * m) / d;
        a = (a0 + m) / d;
        period.push_back(a);
    } while (a != 2 * a0);

    return {a0, period};
}

vector<pair<ll, ll>> find_pell_solutions(int N, int limit) {
    auto [a0, period] = continued_fraction_sqrt(N);
    if (period.empty()) return {};  // Нет решений

    vector<pair<ll, ll>> solutions;
    ll p0 = 1, q0 = 0, p1 = a0, q1 = 1;
    if (p1 * p1 - N * q1 * q1 == 1) solutions.emplace_back(p1, q1);

    for (int i = 0; solutions.size() < limit; i++) {
        int a = period[i % period.size()];
        ll p2 = a * p1 + p0;
        ll q2 = a * q1 + q0;
        if (p2 > 1e9) break;
        if (p2 * p2 - N * q2 * q2 == 1) {
            solutions.emplace_back(p2, q2);
        }
        p0 = p1; q0 = q1;
        p1 = p2; q1 = q2;
    }
    return solutions;
}


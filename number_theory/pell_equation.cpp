#include <bits/stdc++.h>

using namespace std;

#define ll long long;

pair<ll,ll> pell_fundamental(int N) {
    ll a0 = floor(sqrt(N));
    if (a0 * a0 == N) {
        return {1, 0};
    }
    ll m = 0, d = 1, a = a0;
    vector<ll> period;
    do {
        m = d * a - m;
        d = (N - m*m) / d;
        a = (a0 + m) / d;
        period.push_back(a);
    } while (a != 2*a0);
    int L = period.size();
    
    ll p_nm2 = 0, p_nm1 = 1, p_i;
    ll q_nm2 = 1, q_nm1 = 0, q_i;
    vector<ll> A;
    A.push_back(a0);
    A.insert(A.end(), period.begin(), period.end());
    if (L % 2 == 1) {
        A.insert(A.end(), period.begin(), period.end());
    }

    int M = A.size();
    for (int i = 0; i < M; i++) {
        ll ai = A[i];
        p_i = ai * p_nm1 + p_nm2;
        q_i = ai * q_nm1 + q_nm2;
        if (p_i*p_i - static_cast<ll>(N)*q_i*q_i == 1) {
            return {p_i, q_i};
        }
        p_nm2 = p_nm1; p_nm1 = p_i;
        q_nm2 = q_nm1; q_nm1 = q_i;
    }
    return {-1,-1};
}
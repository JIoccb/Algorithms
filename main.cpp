#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define ll long long
#define ld long double
#define ull unsigned long long
#define u32 uint32_t

//#define DEBUG
//#define TIMER

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define minf LONG_LONG_MIN
#define MOD 1000000007
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define print(x) for(auto element:x) cout << element << " ";
#define endl "\n"


void solution() {
}

int main() {
#ifdef TIMER
    auto _clock_start = chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solution();
    }
#ifdef TIMER
    cerr << "Executed in " << chrono::duration_cast<chrono::milliseconds>(
        chrono::high_resolution_clock::now()
        - _clock_start).count() << "ms." << endl;
#endif
}

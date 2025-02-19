#include <bits/stdc++.h>
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define ll long long
#define ld long double

bool isPrime(ll n) {
    if (n <= 1) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
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

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b) {
        a = exchange(b, a % b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

vector<ll> factorize(ll n) {
    vector<ll> factors;
    for (ll d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            factors.push_back(d);
            n /= d;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    ll x1, y1;
    const ll g = extended_gcd(b % a, a, x1, y1);
    x = y1 - b / a * x1;
    y = x1;
    return g;
}

ll count_divisors(ll num) {
    ll count = 0;
    for (ll i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            count++;
            if (i != num / i) count++;
        }
    }
    return count;
}

ll euler(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

unordered_map<long, long> factorize(__int128 n) {
    unordered_map<long, long> factors;
    for (long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) factors[n]++;
    return factors;
}

bool is_palindrome(vector<ll> &arr) {
    ll n = arr.size();
    for (ll i = 0; i < n / 2; i++) {
        if (arr[i] != arr[n - 1 - i]) return false;
    }
    return true;
}

ll find(vector<ll> &a) {
    ll n = a.size();
    ll gcd_value = 0;
    for (ll i = 0; i < n / 2; i++) {
        gcd_value = gcd(gcd_value, abs(a[i] - a[n - 1 - i]));
    }
    return gcd_value;
}

ll mul(ll x, ll y, ll mod) {
    __int128 x128 = x;
    __int128 y128 = y;
    return x128 * y128 % mod;
}

ll discrete_log(ll P, ll A, ll B) {
    ll m = ceil(sqrt(P));
    unordered_map<ll, ll> baby;

    ll cur = 1;
    for (ll j = 0; j < m; j++) {
        baby[cur] = j;
        cur = (cur * A) % P;
    }

    ll Am = fastpow(A, P - 1 - m, P);
    cur = B;

    for (ll i = 0; i <= m; i++) {
        if (baby.count(cur)) {
            return i * m + baby[cur];
        }
        cur = cur * Am % P;
    }
    return -1;
}

vector<ll> divisors(ll n, ll &count) {
    vector<ll> result;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            result.push_back(i);
            count++;
            if (i != n / i) {
                result.push_back(n / i);
                count++;
            }
        }
    }
    return result;
}

bool is_square(ll n) {
    ll sq = floor(sqrt(n));
    return sq * sq == n;
}

ll sum_of_squares(ll n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

ll fibonacci(ll n) {
    long double five = sqrtl(5);
    return static_cast<long long>(1 / five * (pow((1 + five) / 2, n) - pow((1 - five) / 2, n)));
}

/*void knights() {
    ll n;
    cin >> n;
    bitset<100000> r;
    int start = 0;
    bool inn = false;
    for (int i = 0; i < n; i++) {
        bool t;
        cin >> t;
        if (!inn && t) {
            start = i;
            inn = true;
        }
        r[i] = t;
    }
    if (!inn) {
        cout << "NO" << endl;
        return;
    }
    ll sas = 0;
    vector<ll> divs = divisors(n, sas);
    for (ll d: divs) {
        int count = 1;
        for (ll j = start + d; j != start; j = (j + d) % n) {
            if (!r[j]) {
                count = 0;
                break;
            }
            count++;
        }
        if (count >= 3) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}*/

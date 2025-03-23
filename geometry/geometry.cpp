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


struct Point {
    ll x, y;

    [[nodiscard]] ld polar_angle() const {
        ld result = atan2l(y, x);
        if (result < 0) {
            result += 2 * PI;
        }
        return result;
    }

    friend ostream &operator<<(ostream &os, const Point &a) {
        os << a.x << " " << a.y;
        return os;
    }
};

struct Vector {
    ll x, y;
    ll id = -1;


    Vector(ll x, ll y) : x(x), y(y) {
    }

    Vector(const Point &a, const Point &b) : x(a.x - b.x), y(a.y - b.y) {
    }

    Vector friend operator+(const Vector &a, const Vector &b) {
        return {a.x + b.x, a.y + b.y};
    }

    Vector &operator+=(const Vector &a) {
        x += a.x;
        return *this;
    }

    Vector friend operator-(const Vector &a, const Vector &b) {
        return {a.x - b.x, a.y - b.y};
    }

    Vector &operator-=(const Vector &a) {
        x -= a.x;
        return *this;
    }

    ll friend operator*(const Vector &a, const Vector &b) {
        return a.x * b.x + a.y * b.y;
    }

    ll friend operator^(const Vector &a, const Vector &b) {
        return a.x * b.y - a.y * b.x;
    }

    static ld abs(const Vector &a) {
        return sqrtl(a.x * a.x + a.y * a.y);
    }

    static ld find_angle_between(const Vector &a, const Vector &b) {
        ld result = atan2l(a ^ b, a * b);
        if (result < 0) {
            result += 2 * PI;
        }
        if (result > PI) {
            result = 2 * PI - result;
        }
        return result;
    }

    [[nodiscard]] ld angle() const {
        ld result = atan2l(y, x);
        if (result < 0) {
            result += 2 * PI;
        }
        return result;
    }


    friend ostream &operator<<(ostream &os, const Vector &a) {
        os << a.x << " " << a.y;
        return os;
    }
};


struct Polygon {
    vector<Point> points;

    explicit Polygon(const vector<Point> &points) : points(points) {
    }

    [[nodiscard]] ld area() const {
        const ll n = points.size();
        ld area = 0;
        for (ll index = 0; index < n; index++) {
            Point p1 = index ? points[index - 1] : points.back();
            Point p2 = points[index];

            area += (p1.y + p2.y) * (p1.x - p2.x);
        }

        return abs(area) / 2;
    }
};

struct Line {
    ll A, B, C;

    Line(ll a, ll b, ll c) : A(a), B(b), C(c) {
    }

    Line(const Point &p1, const Point &p2) {
        A = p2.y - p1.y;
        B = p1.x - p2.x;
        C = -(Vector(p2.y - p1.y, p1.x - p2.x) * Vector(p1.x, p1.y));
    }

    static pair<ld,ld> find_intersection(const Line &l1, const Line &l2) {
        ll det = l1.A * l2.B - l2.A * l1.B;;
        if (det == 0) {
            return {LLONG_MAX, LLONG_MAX};
        }
        ll detx = l1.B * l2.C - l2.B * l1.C;
        ll dety = l2.A * l1.C - l1.A * l2.C;

        return {static_cast<ld>(detx) / det, static_cast<ld>(dety) / det};
    }

    static ld find_distance_to_point(const Line &l, const Point &p) {
        ld distance = abs(l.A * p.x + l.B * p.y + l.C) / sqrt(l.A * l.A + l.B * l.B);
        return distance;
    }

    friend ostream &operator<<(ostream &os, const Line &a) {
        os << a.A << " " << a.B << " " << a.C;
        return os;
    }
};
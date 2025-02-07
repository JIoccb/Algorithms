#include <vector>
#include <string>

using namespace std;

vector<int> prefix_function(const string& s) {
    const int n = s.length();
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}

vector<int> kmp_search(const string& a, const string& b) {
    const int n = a.length();
    const int m = b.length();
    if (m == 0) return {};

    const vector<int>& p = prefix_function(b);
    vector<int> positions;
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && a[i] != b[j]) {
            j = p[j - 1];
        }
        if (a[i] == b[j]) {
            j++;
        }
        if (j == m) {
            positions.push_back(i - m + 2);
            j = p[j - 1];
        }
    }

    return positions;
}

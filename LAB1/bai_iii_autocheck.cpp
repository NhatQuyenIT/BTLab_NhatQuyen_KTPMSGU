#include <bits/stdc++.h>
using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1;
    }
    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;
    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);
    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

static const double EPS = 1e-9;

bool almost_equal(double a, double b, double eps = EPS) {
    return fabs(a - b) <= eps;
}

void normalize_zero(double &v) {
    if (fabs(v) < EPS) v = 0.0; // -0 -> 0
}

bool equal_root_multiset(vector<double> a, vector<double> b) {
    if (a.size() != b.size()) return false;
    for (auto &v : a) normalize_zero(v);
    for (auto &v : b) normalize_zero(v);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (size_t i = 0; i < a.size(); ++i) {
        if (!almost_equal(a[i], b[i])) return false;
    }
    return true;
}

struct Case {
    const char* name;
    double a,b,c;
    int expected_n;               // -1, 0, 2, 4
    vector<double> expected_roots; // size = expected_n if expected_n > 0
};

int main() {
    vector<Case> cases = {
        // Nhóm 0 — suy biến tổng quát
        {"0.1: a=b=c=0 (∞ nghiệm)",                  0, 0, 0,  -1, {}},
        {"0.2: a=b=0,c!=0 (vô nghiệm)",              0, 0, 5,   0,  {}},

        // Nhóm 1 — a=0, b!=0 -> bx^2 + c = 0
        {"1.1: a=0,b=1,c=1 (x^2=-1)",                0, 1, 1,   0,  {}},
        {"1.2: a=0,b=2,c=0 (x=0 kép)",               0, 2, 0,   2,  {0, 0}},
        {"1.3: a=0,b=1,c=-4 (x=±2)",                 0, 1,-4,   2,  { 2, -2}},

        // Nhóm 2 — a!=0, Δ<0
        {"2.1: y^2+1=0 (Δ<0)",                        1, 0, 1,   0,  {}},

        // Nhóm 3 — a!=0, Δ=0
        {"3.1: y=-1 (Δ=0,y<0)",                       1, 2, 1,   0,  {}}, // (x^2+1)^2=0
        {"3.2: y=0 (Δ=0,y=0)",                        1, 0, 0,   2,  {0, 0}},
        {"3.3: y=1 (Δ=0,y=1 -> x=±1)",                1,-2, 1,   2,  { 1, -1}},

        // Nhóm 4 — a!=0, Δ>0
        {"4.1: y=1,-2 -> x=±1",                       1, 1,-2,   2,  { 1, -1}},
        {"4.2: y=4,1 -> x=±2,±1",                     1,-5, 4,   4,  { 2,-2, 1,-1}},
        {"4.3: y=-2,-3 (không y>=0)",                 1, 5, 6,   0,  {}},
        // Test đếm trùng 0 theo code hiện tại (y1=1, y2=0 -> 1,-1,0,0)
        {"4.4: y=1,0 -> code hiện tại trả 1,-1,0,0",  1,-1, 0,   4,  { 1,-1, 0,0}},

        // Nhóm 5 — thêm biến thể
        {"5.1: scale (y=4,1)",                        2,-10, 8,  4,  { 2,-2, 1,-1}},
        {"5.2: y=1,0 -> 1,-1,0,0",                    3, -3, 0,  4,  { 1,-1, 0,0}},
        {"5.3: y=2 (Δ=0) -> x=±√2",                   1, -4, 4,  2,  { sqrt(2.0), -sqrt(2.0)}},
    };

    int passed = 0, failed = 0;
    for (const auto& tc : cases) {
        double out[4] = {NAN,NAN,NAN,NAN};
        int n = solveQuartic(tc.a, tc.b, tc.c, out);

        bool ok = (n == tc.expected_n);
        vector<double> got;
        if (n > 0) for (int i = 0; i < n; ++i) got.push_back(out[i]);

        if (ok && n > 0) ok = equal_root_multiset(got, tc.expected_roots);

        if (ok) {
            cout << "[PASS] " << tc.name << "\n";
            ++passed;
        } else {
            cout << "[FAIL] " << tc.name << "\n";
            cout << "  Input: a=" << tc.a << " b=" << tc.b << " c=" << tc.c << "\n";
            cout << "  Expected n=" << tc.expected_n << ", roots=";
            for (auto v : tc.expected_roots) cout << v << " ";
            cout << "\n  Got      n=" << n << ", roots=";
            for (int i=0;i<n;++i) cout << out[i] << " ";
            cout << "\n";
            ++failed;
        }
    }

    cout << "\nSummary: " << passed << " passed, " << failed << " failed.\n";
    return failed == 0 ? 0 : 1;
}

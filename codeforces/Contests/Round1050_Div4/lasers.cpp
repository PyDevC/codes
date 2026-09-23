#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int m, n, x, y;
        cin >> m >> n >> x >> y;

        int arrM[m], arrN[n];
        for(int i{}; i < m; ++i) {
            cin >> arrM[i];
        }
        for(int i{}; i < n; ++i) {
            cin >> arrN[i];
        }

        cout << m + n << endl;

    }
    return 0;
}

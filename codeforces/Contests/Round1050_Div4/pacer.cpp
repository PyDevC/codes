#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int score = 0;
        bool state = 0;
        int prev = 0;
        for(int i{}; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            score += (a - prev);
            state = ((a - prev) % 2 == 0)? state : !state;

            if (b != state) {
                --score;
            }
            state = b;

            prev = a;
        }

        score += (m - prev);

        cout << score << endl;
    }
    return 0;
}

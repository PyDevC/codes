#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> arr(n, 0);
        long long score = 0;
        int idx = 0;
        for(int i{}; i < n; ++i) {
            cin >> arr[idx];
            if(arr[idx] % 2 == 0) {
                score += arr[idx];
                arr[idx] = 0;
            } else {
                ++idx;
            }
        }

        std::sort(arr.begin(), arr.end());

        if(arr[n - 1] == 0) { 
            cout << 0 << endl;
        } else {
            int limit = (idx + 1) / 2;
            for(int i{}; i < limit; ++i) {
                score += arr[n - i - 1];
            }

            cout << score << endl;
        }

    }

    return 0;
}

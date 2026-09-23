#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--){
        int x, n;
        cin >> x >> n; 
        int answer = (n % 2)? x : 0 ;
        std::cout << answer << std::endl;
    }

    return 0;
}

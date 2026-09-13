#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> players(n, -1);
    int i{};
    while(i < n) {
        std::cin >> players[i];
        i++;
    }

    int contestant{players[k - 1]};

    // Solution
    std::cout << std::count_if(players.begin(), players.end(), [&](int i){ return i >= contestant && i > 0; }) << std::endl;
    return 0;
}

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    int attempt{};
    while(t--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        // Solution in here only
        if ((x + y + z) > 1) {
            attempt++;
        }
    }

    std::cout << attempt << std::endl;

    return 0;
}

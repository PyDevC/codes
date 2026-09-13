#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int m, n;
    std::cin >> m >> n;
    std::cout << (m * n) / 2 << std::endl;

    return 0;
}

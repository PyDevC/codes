#include <iostream>

void watermelon(int weight) {
    if(weight % 2 != 0 || weight == 2) {
        std::cout << "NO" << std::endl;
        return;
    }

    std::cout << "YES" << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int weight;
    std::cin >> weight;

    watermelon(weight);

    return 0;
}

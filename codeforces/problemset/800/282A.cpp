#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;

    int x{};
    char o[4];
    while(t--) {
        std::cin >> o;
        switch(o[0]) {
            case 'X': {
                if (o[1] == '+') {
                    x++;
                } else {
                    x--;
                }
            } break;

            case '+': {
                ++x;
            } break;
            case '-': {
                --x;
            } break;
            default:
            break;
        };
    }

    std::cout << x << std::endl;
    return 0;
}

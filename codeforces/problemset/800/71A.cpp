#include <iostream>

void processWords(std::string &word) {
    if (word.length() <= 10) {
        std::cout << word << std::endl;
        return;
    }

    std::cout << word[0] << word.length() - 2 << word[word.length() - 1] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;

    while(t--) {
        std::string word;
        std::cin >> word;
        processWords(word);
    }

    return 0;
}

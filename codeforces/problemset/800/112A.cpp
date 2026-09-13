#include <iostream>

int caseInsensitiveCompare(std::string &str1, std::string &str2) {
    auto it1 = str1.begin();
    auto it2 = str2.begin();

    while(it1 != str1.end() || it2 != str2.end()) {
        auto c1 = std::tolower(static_cast<unsigned char>(*it1));
        auto c2 = std::tolower(static_cast<unsigned char>(*it2));

        if (c1 > c2) return 1;
        if (c1 < c2) return -1;
        it1++;
        it2++;
    }

    if(str1.size() > str2.size()) return 1;
    if(str1.size() < str2.size()) return -1;

    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string str1{};
    std::string str2{};

    std::cin >> str1;
    std::cin >> str2;

    std::cout << caseInsensitiveCompare(str1, str2) << std::endl;
    return 0;
}


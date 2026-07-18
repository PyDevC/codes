#include <iostream>

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
             return false;
        }   else if (x < 10) {
            return true;
        }

        int original{x};
        long reverse{};

        // compute the reverse of number
        while (x > 0) {
            reverse = reverse * 10;
            int remainder = x % 10;
            x = x / 10;
            reverse = reverse + remainder;
        }

        return reverse == original;
    }
};

int main() {
    Solution sol;
    std::cout << sol.isPalindrome(100) << " ";
    std::cout << sol.isPalindrome(1001) << " ";
    std::cout << sol.isPalindrome(10000001) << " ";
    std::cout << sol.isPalindrome(1000000) << " ";
    std::cout << sol.isPalindrome(1203234) << " ";
    std::cout << sol.isPalindrome(11233211) << " ";
    std::cout << sol.isPalindrome(1234567899) << "\n";
    return 0;
}

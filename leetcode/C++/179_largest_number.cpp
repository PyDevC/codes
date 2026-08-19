#include <bits/stdc++.h>
#include <string>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string result{};
        vector<std::string> numStr{};
        cout << "Created" << endl;
        for(auto num : nums) {
            numStr.push_back(to_string(num));
        }

        sort(numStr.begin(), numStr.end(), [](auto a, auto b){
            return a + b > b + a;
        });

        if(numStr[0] == "0") {
            return numStr[0];
        }

        for(auto s : numStr) {
            result+=s;
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,9,999,939};
    cout << sol.largestNumber(nums);
}

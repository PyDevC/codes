#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson() { return {"Cherno", 24}; }

int main(void) { 
    std::tuple<std::string, int> person = CreatePerson();
    std::string& Name = std::get<0>(person);
    int age = std::get<1>(person);
    std::cout << Name << " " << age << "\n";

    std::string name;
    std::tie(name, age) = CreatePerson();
    std::cout << name << " " << age << "\n";

    auto[newName, newAge] = CreatePerson();
    std::cout << newName << " " << newAge << "\n";
    return 0; 
}

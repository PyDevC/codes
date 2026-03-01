// Print Hello World n times

#include <iostream>

void helloworld(int n){
    std::cout << "Hello World.\n";
    if(n <= 1)
        return;
    return helloworld(n - 1);
}

int main(void){
    helloworld(10);
    return 0;
}

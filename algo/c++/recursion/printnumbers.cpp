// Print Hello World n times

#include <iostream>

void helloworld(int n, int base){
    std::cout << base - n << std::endl;
    if(n <= 1)
        return;
    return helloworld(n - 1, base);
}

int main(void){
    helloworld(10, 10);
    return 0;
}

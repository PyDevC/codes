#include <iostream>

void reverse(int arr[], int size, int n){
    if(n >= (size / 2)){
        return;
    }
    int temp;
    temp = arr[n];
    arr[n] = arr[size - 1 - n];
    arr[size - 1 - n] = temp;

    return reverse(arr, size, n + 1);
}

int main(void){
    int arr[5] = {1, 2, 3, 4, 5};
    int (&ref_arr)[5] = arr;
    reverse(ref_arr, 5, 0);
    for (int e : ref_arr){
        std::cout << e << std::endl;
    }
    return 0;
}

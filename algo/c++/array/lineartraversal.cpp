#include <iostream>

int * insert_at_end(){}

using namespace std;
int main(void){
    int size = 20;
    int arr[size];
    for (int i = 0; i < size; i++){
        cout << i << endl;
        arr[i] = i;
    }
    cout << "We have our Array Ready" << endl;

    for (int i = 0; i < size; i++){
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    return 0;
}

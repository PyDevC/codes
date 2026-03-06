#include <array>
#include <iostream>

int main(void){
    // Declare an array of fixed size
    std::array<int, 3> sample;
    // There are various containers
    // Container
    // ReversibleContainer: one which can be reversed
    // ContiguousContainer: one which stores memory in a contiguous memory location
    // partially satisfies SequenceContainer: one which stores objects of same type in linear arrangement

    // Calling front() and back() methods on empty array
    // std::cout << sample.back();

    // template array<T, n> where T is a complete type and n is size of array
    std::cout << sizeof(sample) << std::endl; // returns std::size_t * n

    // pointer to element of template array 
    int* ptr = &sample[0];
    std::cout << *ptr << std::endl;
    *ptr =  10;
    std::cout << *ptr << std::endl;
    std::cout << sample[0] << std::endl;

    // method at() is just [] operator with bounds check
    std::cout << sample.at(0) << std::endl;
    // method [] (yes it is a function) just does reference to element
    std::cout << sample[0] << std::endl;

    // Modify all the elements in array
    sample = {1, 2 , 3};
    
    // method front() just returns the reference to first element
    std::cout << sample.front() << std::endl;

    // method back() just returns the reference to last element
    std::cout << sample.back() << std::endl;

    // Gives you pointer to the starting index of array it essentially makes it c like array
    std::cout << sample.data() << std::endl;

    // method gives you begenning of iterator
    std::cout << sample.begin() << std::endl; // normal iterator
    std::cout << sample.cbegin() << std::endl; // constant iterator

    // Behaviours of cbegin()
    // since it's a constant iterator it can't be referenced
    // Trying itetration with normal itetraor
    for (auto i = sample.begin(); i != sample.end(); i++){
        std::cout << *i << std::endl;
    }

    // Trying itetration with const_iterator
    for (std::array<int, 3>::const_iterator i = sample.cbegin(); i != sample.cend(); i++){
        std::cout << *i << std::endl;
    }

    // method end() gives you ending of iterator
    std::cout << sample.end() << std::endl; // normal iterator
    std::cout << sample.cend() << std::endl; // constant iterator
    
    // method rbegin() is just reverse iteration same goes for rend()
    // method empty checks if array is empty or not
    std::cout << sample.empty() << std::endl; // It just checks if size() == 0

    // method size() returns the size of the array that was used when it was first declared
    std::cout << sample.size() << std::endl; // it literally returns the _Nm from the array struct which is used to define array

    // method max_size() returns the maximum number of possible elements in array
    std::cout << sample.max_size() << std::endl; // Since in Array the number of elements is always fixed we can say that max_size is same as size

    // method fill() it fills the container with specific element
    sample.fill(10);
    for (auto i = sample.begin(); i != sample.end(); i++){
        std::cout << *i << std::endl;
    }

    // method swap() does not work as you think, it just swaps all the elements in one array with another array including all the properties associated with it
    std::array<int, 3> other = {1, 2, 3};
    sample.swap(other); // In case of arrays, it can only be swapped with the array of same number of elements
    // Iterate over sample
    for (auto i = sample.begin(); i != sample.end(); i++){
        std::cout << *i << std::endl;
    }

    // Iterate over other
    for (auto i = other.begin(); i != other.end(); i++){
        std::cout << *i << std::endl;
    }

    // Non-member functions in arrays, these are just comparision operators
    std::cout << (sample == other) << std::endl;
    std::cout << (sample != other) << std::endl; // removed in c++20
    std::cout << (sample < other) << std::endl; // removed in c++20
    std::cout << (sample <= other) << std::endl; // removed in c++20
    std::cout << (sample > other) << std::endl; // removed in c++20
    std::cout << (sample >= other) << std::endl; // removed in c++20
    // std::cout << (sample <=> other) << std::endl; // This is something different, called spaceship operator and you should not use it in production because it only works in c++ 20
}

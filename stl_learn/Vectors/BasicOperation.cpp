#include <iostream>
#include <vector>

void printvec(std::vector<int> &vec) {
  std::cout << "Print Vector [";
  for (int e : vec) {
    std::cout << e << ", ";
  }
  std::cout << "]\n";
}

int main() {

  // Create a vector with no predefined size
  std::vector<int> vec_no_size;

  // Insert elements to vector
  vec_no_size.push_back(10);
  vec_no_size.push_back(10);
  vec_no_size.push_back(10);
  vec_no_size.push_back(10);
  vec_no_size.push_back(10);
  vec_no_size.push_back(10);

  // Query the allocated size of the vector
  std::cout << vec_no_size.capacity() << std::endl;
  printvec(vec_no_size);

  // return the extra memory to the system when you know that state of vector
  // will not change
  vec_no_size.shrink_to_fit();
  std::cout << vec_no_size.capacity() << std::endl;
  printvec(vec_no_size);

  // eliminate the number of reallocations in the vector
  std::vector<int> vec_no_realloc = {1, 2, 3, 4};
  vec_no_realloc.reserve(10);
  std::cout << vec_no_realloc.capacity() << std::endl;
  printvec(vec_no_realloc);
  // Since the vector is reallocated with size 10 then after we add new elements
  // the capacity does not change
  vec_no_realloc.push_back(10); // Now 5 elements
  std::cout << vec_no_realloc.capacity() << std::endl;
  printvec(vec_no_realloc);

  // swap elements of two different vectors
  std::cout << "Before" << std::endl;
  std::cout << "vec_no_realloc: ";
  printvec(vec_no_realloc);
  std::cout << "vec_no_size: ";
  printvec(vec_no_size);

  vec_no_size.swap(vec_no_realloc);

  std::cout << "After" << std::endl;
  std::cout << "vec_no_realloc: ";
  printvec(vec_no_realloc);
  std::cout << "vec_no_size: ";
  printvec(vec_no_size);

  // clear
  vec_no_size.clear();
  std::cout << vec_no_size.capacity()
            << std::endl; // No change in capacity just the vector is clear

  // Insert element
  vec_no_size.insert(vec_no_size.begin(), 5);
  vec_no_size.insert(vec_no_size.begin() + 1, 5);
  vec_no_size.insert(vec_no_size.begin() + 2, 5);
  vec_no_size.insert(vec_no_size.begin() + 3, 5);
  printvec(vec_no_size);

  return 0;
}

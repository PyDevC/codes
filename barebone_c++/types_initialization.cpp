#include <iostream>

int main() {

  int a; // default initialization
         // Here no initializer is provided so a has no specific value.

  std::cout << "default initialization: a is " << a << "\n";

  int b = 5; // copy initialization
             // rvalue is copied into the variable, in modern C++ it is
             // considered less efficient than other initializations for complex
             // data types. C++17 fixed a huge chunk of issues in this
             // initialization so it doesn not make that much of a different for
             // simple types but can make for special usecase. You can use copy
             // initialization when you implicitly want to copy the values, like
             // returning values form a function or passing arguments by value
             // to a function in such cases it copies the values.

  std::cout << "copy initialization: b = 5 so -> " << b << "\n";

  int c(6); // direct initialization
            // These were initially introduced to make efficient assignments for
            // complex objects (some class types). Look into C++ standard spec
            // to find out which one is better for which std. Just like copy
            // initialization this one is also not favored in modern C++. It is
            // replaced by direct list initialization which has some quirks so
            // direct initialization is still used in certain usecases.
            // Direct initialization is also used when type casting values to
            // another type.

  std::cout << "direct initialization: c(6) so -> " << c << "\n";

  // direct list initialization
  // This is the modern way of initialization of objects (it is also
  // called list initialization, uniform initialization, or brace
  // initialization). Prior to C++11, some types require using copy list
  // initialization and some requires for direct list initialization.
  // List initialization was introduced to provide the initialization syntax
  // that works in all cases and provides uniformness in assignment.
  // List initialization can also be used to initialize list of values rather
  // than one single values. You can use both direc list initialization or copy
  // list initialization for this case.
  int d{7};

  std::cout << "direct list initialization: d{6} so -> " << d << "\n";

  int e = {7}; // copy list initialization, here we copy the values from
               // list initialization to the variable. It is mainly used to
               // initialize list of objects.

  std::cout << "direct list initialization: e = {7} so -> " << e << "\n";

  // List Initialization disallows for type narrowing conversions.
  // When we assign the values from a bigger data type to a smaller one, we
  // loose some data and this is called narrow conversion or narrow type casting
  // in case of typecasting.
  // So it does not allows this narrow conversion.
  // int integer {4.5}; // You will see compilation error from your compiler
  // "Type 'double' cannot be narrowed to 'int' in initializer list"
  // But other initializations allows this
  int integer1(4.5);  // This will work but might generate warning
  int integer2 = 7.3; // This will work but might generate warning

  std::cout << "direct initialization disallow narrowing case: integer1 -> "
            << integer1 << "\n";
  std::cout << "copy initialization disallow narrowing case: integer2 -> "
            << integer2 << "\n";

  // You can do narrow conversion even if first time the
  // list initializations was performed and second time the
  // copy initialization was performed.
  int integer{4};
  integer = 7.8; // See it does not raise any error but does raise warning
                 // The above case is perfectly valid

  int f{};  // value initialization
            // This kind of initialization is to initialize values to their
            // default forms. In case of integers it will be zero and so.
            // zero initialization, the cases when it's zero then we call this
            // zero initialization else we will call it value initialization.
  char g{}; // here the value will not be zero, this will get assigned to /0
            // null character.

  std::cout << "value initialization: f{} so -> " << f << "\n";
  std::cout << "value initialization: g{} so -> " << g << "\n";

  // aggregate initialization
  // These look similar to list initialization but here we can assign
  // different values to different elements of the struct or class.
  // This is not just limited to this one type of initialization but it can be
  // performed in different ways.
  // Will explore them in future.
  struct s1 {
    int a;
    int b;
  };

  struct s1 n = {1, 2};

  std::cout << "aggregate initialization: n = {1, 2} so -> { a = " << n.a
            << ", " << n.b << " }\n";

  int &ref = f; // reference initialization
  // This is just creating a reference to a object. Will explore in future.
  // Here we have ref as reference to f.

  std::cout << "reference initialization: &ref = f so -> " << ref << "\n";

  static int st; // static initialization
  // initialization in static scope with static keyword
  // we have just make sure we have their values defined before use. idk if this
  // is requirement or not.

  return 0;
}

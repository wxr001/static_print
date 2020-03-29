# static_print
This project is a **C++14** header-only library that helps you debugging the TMP codes by printing out the type name in warning messages.

Compared with traditional stop-the-world methods like `no type named ...`, this library don't stop the compiling process. It just gives you a "harmless" warning message.

## Usage

wrap the type with static_print_t<...>: 
```c++
static_print_t<YOUR_TYPE_HERE>
```
## Example
Old code:
```c++
template <typename T>
struct helper: 
        // type to print out here
        helper<typename T::type>
{};
template <>
struct helper<int>
{
        using type = int;
};
```
New: 
```c++
template <typename T>
struct helper: 
        // type to print out here
        helper<static_print_t<typename T::type>>
{};
template <>
struct helper<int>
{
        using type = int;
};
```
### Output from Compiler: 
* GCC 
```bash
In file included from test.cpp:2:
static_print.hpp: In instantiation of ‘struct static_print<identity<int> >’:
test.cpp:4:8:   required from ‘struct helper<identity<identity<int> > >’
test.cpp:19:54:   required from here
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = identity<int>]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = identity<int>]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = identity<int>]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
static_print.hpp: In instantiation of ‘struct static_print<int>’:
test.cpp:4:8:   recursively required from ‘struct helper<identity<int> >’
test.cpp:4:8:   required from ‘struct helper<identity<identity<int> > >’
test.cpp:19:54:   required from here
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = int]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = int]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
static_print.hpp:47:28: warning: ‘static T static_print<T>::test() [with T = int]’ is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
   47 |  using type = decltype(test());
      |                        ~~~~^~
static_print.hpp:46:3: note: declared here
   46 |   test();
      |   ^~~~
```
* Clang
```bash
In file included from test.cpp:2:
./static_print.hpp:47:24: warning: 'test' is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
        using type = decltype(test());
                              ^
./static_print.hpp:44:4: note: 'test' has been explicitly marked deprecated here
        [[deprecated(
          ^
./static_print.hpp:47:24: warning: 'test' is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
        using type = decltype(test());
                              ^
./static_print.hpp:51:1: note: in instantiation of template class 'static_print<identity<int> >' requested here
using static_print_t = typename static_print<T>::type;
^
test.cpp:6:16: note: in instantiation of template type alias 'static_print_t' requested here
        helper<static_print_t<typename T::type>>
               ^
test.cpp:19:23: note: in instantiation of template class 'helper<identity<identity<int> > >' requested here
using type = typename helper<identity<identity<int>>>::type;
                      ^
./static_print.hpp:44:4: note: 'test' has been explicitly marked deprecated here
        [[deprecated(
          ^
./static_print.hpp:47:24: warning: 'test' is deprecated: This warning is used for debugging only! Just Ignore It when building [-Wdeprecated-declarations]
        using type = decltype(test());
                              ^
./static_print.hpp:51:1: note: in instantiation of template class 'static_print<int>' requested here
using static_print_t = typename static_print<T>::type;
^
test.cpp:6:16: note: in instantiation of template type alias 'static_print_t' requested here
        helper<static_print_t<typename T::type>>
               ^
test.cpp:6:9: note: in instantiation of template class 'helper<identity<int> >' requested here
        helper<static_print_t<typename T::type>>
        ^
test.cpp:19:23: note: in instantiation of template class 'helper<identity<identity<int> > >' requested here
using type = typename helper<identity<identity<int>>>::type;
                      ^
./static_print.hpp:44:4: note: 'test' has been explicitly marked deprecated here
        [[deprecated(
          ^
3 warnings generated.
```
## License
BSD 3-Clause License

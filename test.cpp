#include <type_traits>
#include "static_print.hpp"
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
template<typename T>
struct identity
{
    using type = T;
};
int main() {
using type = typename helper<identity<identity<int>>>::type;
static_assert(std::is_same_v<type, int>);
}

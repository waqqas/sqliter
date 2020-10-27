#ifndef SQLITER_HANDLER_HELPER_H
#define SQLITER_HANDLER_HELPER_H

#include <cstddef>
#include <tuple>  // std::tuple_element

namespace sqliter {
namespace asio {
template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{
};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
  enum
  {
    arity = sizeof...(Args)
  };
  // arity is the number of arguments.

  typedef ReturnType result_type;

  template <size_t i>
  struct arg
  {
    typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    // the i-th argument is equivalent to the i-th tuple element of a tuple
    // composed of those arguments.
  };
};
}  // namespace asio
}  // namespace sqliter
#endif
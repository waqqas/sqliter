
#ifndef SQLITER_QUERY_RESULT_H
#define SQLITER_QUERY_RESULT_H

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>

namespace sqliter {
namespace asio {

template <typename... T>
class query_result
{
public:
  using result_data_type = std::tuple<T...>;
  using query_data_type  = std::list<result_data_type>;

private:
  template <std::size_t... N>
  static auto make_tuple(std::index_sequence<N...>, char **data)
  {
    return std::make_tuple(get_data<N>(data[N])...);
  }

  template <std::size_t N>
  using element_type = typename std::tuple_element<N, result_data_type>::type;

  template <std::size_t N>
  static typename std::enable_if<std::is_arithmetic<element_type<N>>::value, element_type<N>>::type
  get_data(char *data)
  {
    std::stringstream st(data);
    element_type<N>   value;
    st >> value;

    return value;
  }

  template <std::size_t N>
  static
      typename std::enable_if<std::is_same<element_type<N>, std::string>::value, std::string>::type
      get_data(char *data)
  {
    return std::string(data);
  }

public:
  static auto make_tuple_from_data(char **data)
  {
    return make_tuple(std::make_index_sequence<std::tuple_size<result_data_type>::value>(), data);
  }

  query_data_type data;
};
}  // namespace asio
}  // namespace sqliter
#endif
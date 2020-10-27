
#ifndef BOOST_QUERY_RESULT_H
#define BOOST_QUERY_RESULT_H

#include <iostream>
#include <list>
#include <sstream>
#include <tuple>

namespace waqqas {
namespace asio {

template <typename... T>
class query_result
{
public:
  using result_data_type = std::tuple<T...>;
  using query_data_type  = std::list<result_data_type>;

private:
  template <std::size_t... I>
  static auto make_tuple(std::index_sequence<I...>, char **data)
  {
    return std::make_tuple(get_data<I>(data)...);
  }

  template <std::size_t N>
  using element_type = typename std::tuple_element<N, result_data_type>::type;

  template <std::size_t N>
  static element_type<N> get_data(char **data)
  {
    std::stringstream st(data[N]);
    element_type<N>   value;
    st >> value;

    return value;
  }

public:
  static auto make_tuple_from_data(char **data)
  {
    return make_tuple(std::make_index_sequence<std::tuple_size<result_data_type>::value>(), data);
  }

  query_data_type data;
};
}  // namespace asio
}  // namespace waqqas
#endif